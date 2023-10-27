#include "Partition.h"
#include "Protocol.h"
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

    auto *handler = new AMQP::LibUvHandler(loop);
    auto *connection = new AMQP::TcpConnection(handler, AMQP::Address(brokerAddress));
    auto *channel = new AMQP::TcpChannel(connection);

    uv_run(loop, UV_RUN_DEFAULT);

    Protocol protocol(channel);
    Partition partition();
    while (partition.available())
    {
        std::string partition_data = partition.next();
        protocol.send_data("topic_exchange", "example.topic", partition_data);
    }

    // TODO: send end of data message N amounts of times, where N is the number of workers
    // TODO: also, create a cond_var to wait for all workers to finish. Pass it to Protocol so MessageProcessor can notify it
    protocol.install_consumer();
    std::string results = protocol.get_results();

    uv_stop(loop);

    channel->close();
    connection->close();

    return 0;
}
