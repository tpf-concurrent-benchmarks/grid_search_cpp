#include "Protocol.h"

const std::string QUEUE_NAME = "work";
const std::string EXCHANGE_NAME = "topic_exchange";
const std::string ROUTING_KEY = "example.topic";

Protocol::Protocol(const std::string &brokerAddress, size_t n_workers = 1) : n_workers_(n_workers)
{
    loop_ = uv_default_loop();
    handler_ = new AMQP::LibUvHandler(loop_);
    connection_ = new AMQP::TcpConnection(handler_, AMQP::Address(brokerAddress));
    channel_ = new AMQP::TcpChannel(connection_);
    channel_->declareExchange(EXCHANGE_NAME, AMQP::topic);
    channel_->declareQueue(QUEUE_NAME)
        .onSuccess([](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel_->bindQueue(EXCHANGE_NAME, QUEUE_NAME, ROUTING_KEY);
}

void Protocol::send_data(std::string exchangeName, std::string routingKey, json data)
{
    channel_->publish(exchangeName, routingKey, data.dump());
}

void Protocol::send_data(std::string exchangeName, std::string routingKey, std::string data)
{
    channel_->publish(exchangeName, routingKey, data);
}

void Protocol::install_consumer()
{
    channel_->consume(QUEUE_NAME)
        .onReceived([this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
            std::cout << "Message received: " << message.body() << std::endl;
            const std::basic_string_view<char> &body = std::string_view(message.body(), message.bodySize());
            std::string body_string(body.begin(), body.end());
            if (body_string == "end")
            {
                n_workers_--;
                channel_->ack(deliveryTag);
                if (n_workers_ == 0)
                {
                    messageProcessor_.save_results();
                    clean();
                }
            }
            else
            {
                messageProcessor_.process_message(body_string);
                channel_->ack(deliveryTag);
            }
        });
}

void Protocol::clean()
{
    channel_->close();
    connection_->close();
    uv_stop(loop_);
    delete channel_;
    delete connection_;
    delete handler_;
}
