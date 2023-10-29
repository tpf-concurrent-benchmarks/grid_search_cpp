#include "partition.h"
#include "protocol.h"
#include "config_reader.h"
#include <nlohmann/json.hpp>
#include "constants.h"

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    int n_workers = 1;
    size_t n_partitions = 1;

    Protocol protocol(brokerAddress, n_workers);
    Partition partition(n_partitions);
    while (partition.available())
    {
        auto partition_data = partition.next();
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::WORK_ROUTING_KEY, partition_data);
    }

    for (int i = 0; i < n_workers; i++)
    {
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::WORK_ROUTING_KEY, Constants::STOP_MESSAGE);
    }

    protocol.installConsumer();

    return 0;
}
