#include "protocol.h"
#include "constants.h"

Protocol::Protocol(const std::string &brokerAddress)
{
    loop_ = uv_default_loop();
    handler_ = new AMQP::LibUvHandler(loop_);
    connection_ = new AMQP::TcpConnection(handler_, AMQP::Address(brokerAddress));
    channel_ = new AMQP::TcpChannel(connection_);
}

void Protocol::sendData(const std::string& exchangeName, const std::string& routingKey, json data)
{
    json message = {
        {"data", data},
    };
    channel_->publish(exchangeName, routingKey, message.dump());
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
            if (body_string == Constants::STOP_MESSAGE)
            {
                channel_->ack(deliveryTag);
                sendData(Constants::EXCHANGE_NAME, Constants::RESULTS_ROUTING_KEY, Constants::END_WORK_MESSAGE);
                clean();
            }
            else
            {
                json jsonMessage = json::parse(body_string);
                messageProcessor_.processMessage(jsonMessage["data"]);
                channel_->ack(deliveryTag);
            }
        });
    uv_run(loop_, UV_RUN_DEFAULT);
}

void Protocol::clean()
{
    channel_->close();
    connection_->close();
    uv_stop(loop_);
    uv_loop_close(loop_);
    delete channel_;
    delete connection_;
    delete handler_;
}
