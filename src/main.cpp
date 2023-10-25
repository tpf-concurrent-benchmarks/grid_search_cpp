#include "config_reader.h"
#include "grid_search.h"
#include "params.h"
#include <amqpcpp.h>
#include <amqpcpp/libuv.h>
#include <amqpcpp/linux_tcp.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <uv.h>

const std::string exchangeName = "topic_exchange";
const std::string routingKey = "example.topic";

using json = nlohmann::json;

int max_sum(std::array<int, 2> &current, int res)
{
    int sum = current[0] + current[1];
    if (sum > res)
    {
        return sum;
    }
    else
    {
        return res;
    }
}

template <std::size_t len> Params<len> json_to_params(const json &json_params)
{
    std::string id = json_params[0];
    std::array<int, len> start;
    std::array<int, len> end;
    std::array<int, len> step;
    for (int i = 1; i < len + 1; i++)
    {
        start[i - 1] = json_params[i][0];
        end[i - 1] = json_params[i][1];
        step[i - 1] = json_params[i][2];
    }
    return Params<len>(std::move(start), std::move(end), std::move(step));
}

int main()
{
    json example = {
        {"happy", true},
        {"pi", 3.141},
    };

    std::string brokerAddress = getBrokerAddress();

    uv_loop_t *loop = uv_default_loop();

    AMQP::LibUvHandler handler(loop);
    AMQP::TcpConnection connection(&handler, AMQP::Address(brokerAddress));
    AMQP::TcpChannel channel(&connection);

    channel.declareExchange(exchangeName, AMQP::topic);
    channel.declareQueue("queue-name")
        .onSuccess([&channel](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });
    channel.bindQueue(exchangeName, "queue-name", routingKey);

    channel.publish(exchangeName, routingKey, example.dump());
    std::cout << "Message sent: " << example.dump() << std::endl;

    channel.consume("queue-name")
        .onReceived([&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
            const basic_string_view<char> &body = std::string_view(message.body(), message.bodySize());
            json receivedMessage = json::parse(body);
            std::cout << "Received message: " << receivedMessage.dump() << std::endl;
            channel.ack(deliveryTag);
        });

    // calculates every combination of the two parameters and prints it
    json example2 = {"1234", {1, 6, 2}, {1, 5, 1}};
    Params params_from_json = json_to_params<2>(example2);
    std::cout << example2.dump() << std::endl;

    std::cout << params_from_json.get_total_iterations() << std::endl;
    GridSearch<2> grid_search(std::move(params_from_json));
    std::cout << grid_search.search(max_sum) << std::endl;

    uv_run(loop, UV_RUN_DEFAULT);

    channel.close();
    connection.close();

    return 0;
}
