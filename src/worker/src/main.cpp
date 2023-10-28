#include "config_reader.h"
#include "grid_search.h"
#include "json_parsing.h"
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

int max_sum(std::array<int, 3> &current, int res)
{
    int sum = current[0] + current[1] + current[2];
    if (sum > res)
    {
        return sum;
    }
    else
    {
        return res;
    }
}

int main()
{

    std::string brokerAddress = getBrokerAddress();

    uv_loop_t *loop = uv_default_loop();

    AMQP::LibUvHandler handler(loop);
    AMQP::TcpConnection connection(&handler, AMQP::Address(brokerAddress));
    AMQP::TcpChannel channel(&connection);

    channel.consume("work").onReceived(
        [&channel](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {
            const basic_string_view<char> &body = std::string_view(message.body(), message.bodySize());
            // json receivedMessage = json::parse(body);
            // std::cout << "Received message: " << receivedMessage.dump() << std::endl;
            std::cout << "Received message: " << body << std::endl;
            channel.ack(deliveryTag);
        });

    // calculates every combination of the two parameters and prints it
    json example2 = {"1234", {1, 6, 1}, {1, 5, 1}, {0, 1, 1}};
    Params params_from_json = json_to_params<3>(example2);
    std::cout << example2.dump() << std::endl;

    std::cout << params_from_json.get_total_iterations() << std::endl;
    GridSearch<3> grid_search(std::move(params_from_json));
    std::cout << grid_search.search(max_sum) << std::endl;
    std::cout << grid_search.get_id() << std::endl;

    uv_run(loop, UV_RUN_DEFAULT);

    channel.close();
    connection.close();

    return 0;
}
