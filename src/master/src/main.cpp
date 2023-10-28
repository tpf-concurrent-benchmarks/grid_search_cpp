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
    int n_workers = 1;
    size_t n_params = 2;

    Protocol protocol(brokerAddress, n_workers);
    Partition partition(n_params);
    while (partition.available())
    {
        // Get next partition
        std::array<int, 3> partition_data = partition.next();
        protocol.send_data(exchangeName, routingKey, partition_data);
    }

    protocol.install_consumer();

    return 0;
}
