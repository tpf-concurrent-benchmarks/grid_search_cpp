#include "config_reader.h"
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

    std::string brokerAddress = getBrokerAddress();

    uv_loop_t *loop = uv_default_loop();

    AMQP::LibUvHandler handler(loop);
    AMQP::TcpConnection connection(&handler, AMQP::Address(brokerAddress));
    AMQP::TcpChannel channel(&connection);

    channel.declareExchange(exchangeName, AMQP::topic);
    const char *queueName = "work";
    channel.declareQueue(queueName).onSuccess(
        [&channel](const std::string &name, uint32_t messagecount, uint32_t consumercount) {
            std::cout << "Queue " << name << " is ready" << std::endl;
        });

    channel.bindQueue(exchangeName, queueName, routingKey);
    channel.publish(exchangeName, routingKey, "Hello from master");

    uv_run(loop, UV_RUN_DEFAULT);

    channel.close();
    connection.close();

    return 0;
}
