#include "protocol.h"
#include "constants.h"

Protocol::Protocol(const std::string &brokerAddress, size_t n_workers = 1) : n_workers_(n_workers)
{
    loop_ = uv_default_loop();
    handler_ = new AMQP::LibUvHandler(loop_);
    connection_ = new AMQP::TcpConnection(handler_, AMQP::Address(brokerAddress));
    channel_ = new AMQP::TcpChannel(connection_);
    channel_->declareExchange(Constants::EXCHANGE_NAME, AMQP::topic);
    channel_->declareQueue(Constants::WORK_QUEUE_NAME)
        .onSuccess([](const std::string &name, uint32_t messageCount, uint32_t consumerCount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel_->declareQueue(Constants::RESULTS_QUEUE_NAME)
            .onSuccess([](const std::string &name, uint32_t messageCount, uint32_t ConsumerCOunt) {
                std::cout << "Queue " << name << " is ready" << std::endl;
            });
    channel_->bindQueue(Constants::EXCHANGE_NAME, Constants::WORK_QUEUE_NAME, Constants::ROUTING_KEY);
    channel_->bindQueue(Constants::EXCHANGE_NAME, Constants::RESULTS_QUEUE_NAME, Constants::ROUTING_KEY);
}

void Protocol::sendData(const std::string& exchangeName, const std::string& routingKey, json data)
{
    channel_->publish(exchangeName, routingKey, data.dump());
}

void Protocol::sendData(const std::string& exchangeName, const std::string& routingKey, std::string data)
{
    channel_->publish(exchangeName, routingKey, data);
}

void Protocol::installConsumer()
{
    channel_->consume(Constants::RESULTS_QUEUE_NAME)
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
                    messageProcessor_.saveResults();
                    clean();
                }
            }
            else
            {
                messageProcessor_.processMessage(body_string);
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
