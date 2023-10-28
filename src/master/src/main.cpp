#include "Partition.h"
#include "Protocol.h"
#include "config_reader.h"
#include <nlohmann/json.hpp>

const std::string exchangeName = "topic_exchange";
const std::string routingKey = "example.topic";

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    int n_workers = 1;
    size_t n_params = 2;

    Protocol protocol(brokerAddress, n_workers);
    Partition partition(n_params);
    while (partition.available())
    {
        std::array<int, 3> partition_data = partition.next();
        protocol.send_data(exchangeName, routingKey, partition_data);
    }

    for (int i = 0; i < n_workers; i++)
    {
        protocol.send_data(exchangeName, routingKey, std::string("stop"));
    }

    protocol.install_consumer();

    return 0;
}
