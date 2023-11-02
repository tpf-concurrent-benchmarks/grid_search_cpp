#include "protocol.h"

#include "constants.h"
#include <utility>

Protocol::Protocol(const std::string &brokerAddress, MessageProcessor messageProcessor, size_t n_workers = 1)
    : n_workers_(n_workers), messageProcessor_(std::move(messageProcessor))
{
    loop_ = uv_default_loop();
    handler_ = new AMQP::LibUvHandler(loop_);
    connection_ = new AMQP::TcpConnection(handler_, AMQP::Address(brokerAddress));
    channel_ = new AMQP::TcpChannel(connection_);
    channel_->declareExchange(Constants::EXCHANGE_NAME, AMQP::topic)
        .onSuccess([]() { std::cout << "Exchange " << Constants::EXCHANGE_NAME << " is ready" << std::endl; })
        .onError([](const char *message) { std::cout << "Exchange declare error: " << message << std::endl; });
    channel_->declareQueue(Constants::WORK_QUEUE_NAME)
        .onSuccess([](const std::string &name, uint32_t messageCount, uint32_t consumerCount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel_->declareQueue(Constants::RESULTS_QUEUE_NAME)
        .onSuccess([](const std::string &name, uint32_t messageCount, uint32_t consumerCount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel_->bindQueue(Constants::EXCHANGE_NAME, Constants::WORK_QUEUE_NAME, Constants::WORK_ROUTING_KEY);
    channel_->bindQueue(Constants::EXCHANGE_NAME, Constants::RESULTS_QUEUE_NAME, Constants::RESULTS_ROUTING_KEY);
}

void Protocol::sendData(const std::string &exchangeName, const std::string &routingKey, std::string data)
{
    channel_->publish(exchangeName, routingKey, data);
}

void Protocol::installConsumer()
{
    channel_->consume(Constants::RESULTS_QUEUE_NAME)
        .onReceived([this](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
            const std::basic_string_view<char> &body = std::string_view(message.body(), message.bodySize());
            std::string body_string(body.begin(), body.end());
            if (body_string == Constants::END_WORK_MESSAGE)
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
                messageProcessor_.processMessage(json::parse(body_string));
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

void Protocol::sendData(const string &exchangeName, const string &routingKey, std::vector<Interval> intervals,
                        const string &aggregation)
{
    json intervalList = json::array();
    for (auto interval : intervals)
    {
        intervalList.push_back(interval.get_interval());
    }
    json message = {
        {"data", intervalList},
        {"agg", aggregation},
    };
    channel_->publish(exchangeName, routingKey, message.dump());
}
