#include "Protocol.h"

const std::string QUEUE_NAME = "work";
const std::string EXCHANGE_NAME = "topic_exchange";
const std::string ROUTING_KEY = "example.topic";

Protocol::Protocol(AMQP::TcpChannel *channel) : channel_(channel), messageProcessor_(1)
{

    channel->declareExchange(EXCHANGE_NAME, AMQP::topic);
    channel->declareQueue(QUEUE_NAME)
        .onSuccess([](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel->bindQueue(EXCHANGE_NAME, QUEUE_NAME, ROUTING_KEY);
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
            messageProcessor_.process_message(body_string);
            channel_->ack(deliveryTag);
        });
}
std::string Protocol::get_results()
{
    return messageProcessor_.get_results();
}
