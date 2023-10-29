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
    size_t n_params = 1;

    Protocol protocol(brokerAddress, n_workers);
    Partition partition(n_params);
    while (partition.available())
    {
        std::cout << "Sending partition" << std::endl;
        auto partition_data = partition.next();
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::ROUTING_KEY_WORK, partition_data);
    }

    for (int i = 0; i < n_workers; i++)
    {
        std::cout << "Sending stop" << std::endl;
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::ROUTING_KEY_WORK, std::string("stop"));
    }

    protocol.installConsumer();

    return 0;
}
