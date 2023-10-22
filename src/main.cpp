#include <iostream>
#include <nlohmann/json.hpp>
#include <amqpcpp.h>
#include <amqpcpp/linux_tcp.h>
#include "params.h"
#include "grid_search.h"
#include <amqpcpp/libuv.h>
#include <uv.h>

const std::string brokerAddress = "amqp://guest:guest@localhost:5672/";
const std::string exchangeName = "topic_exchange";
const std::string routingKey = "example.topic";

int max_sum(std::array<int, 2>& current, int res) {
    int sum = current[0] + current[1];
    if (sum > res) {
        return sum;
    } else {
        return res;
    }
}

int main() {
    using json = nlohmann::json;
    json example = {
            {"happy", true},
            {"pi", 3.141},
    };
    std::cout << example << std::endl;

    uv_loop_t *loop = uv_default_loop();

    AMQP::LibUvHandler handler(loop);
    AMQP::TcpConnection connection(&handler, AMQP::Address(brokerAddress));
    AMQP::TcpChannel channel(&connection);


    channel.declareExchange(exchangeName, AMQP::topic);
    channel.declareQueue("queue-name").onSuccess(
            [&channel](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
                std::cout << "Queue " << name << " is ready" << std::endl;
            });
    channel.bindQueue(exchangeName, "queue-name", routingKey);

    channel.publish(exchangeName, routingKey, example.dump());
    std::cout << "Message sent: " << example.dump() << std::endl;

    channel.consume("queue-name").onReceived(
            [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
                std::cout << "Message received: " << message.body() << std::endl;
                // TODO: This line will break the program, since the json module reads the null character at the end
                json receivedMessage = json::parse(message.body());
                std::cout << "Received message: " << receivedMessage.dump() << std::endl;
                channel.ack(deliveryTag);
            });

    // calculates every combination of the two parameters and prints it
    std::array<int, 2> start = {0, 0};
    std::array<int, 2> end = {5, 4};
    std::array<int, 2> step = {1, 1};
    Params<2> params(start, end, step);
    std::cout << params.get_total_iterations() << std::endl;
    GridSearch<2> grid_search(params);
    std::cout << grid_search.search(max_sum) << std::endl;

    uv_run(loop, UV_RUN_DEFAULT);

    channel.close();
    connection.close();

    return 0;
}
