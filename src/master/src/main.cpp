#include "config_reader.h"
#include "constants.h"
#include "partition.h"
#include "protocol.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    int n_workers = 1;
    size_t n_partitions = 1;

    Protocol protocol(brokerAddress, n_workers);

    std::vector<std::array<float, 3>> intervals{{0, 12, 3}, {-8, 4, 2}, {3, 12, 3}};
    Partition partition(std::move(intervals), intervals.size());

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

    //test partition creator

    std::vector<int> partitions_per_interval = partition.calc_partitions_per_interval(2);
    std::cout << "partis" << std::endl;
    for (int i = 0; i < partitions_per_interval.size(); i++)
    {
        std::cout << partitions_per_interval[i] << std::endl;
    }
    return 0;
}
