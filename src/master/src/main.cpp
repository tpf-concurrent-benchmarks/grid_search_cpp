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
    size_t n_params = 2;

    Protocol protocol(brokerAddress, n_workers);

    std::vector<std::array<float, 3>> intervals{{0, 12, 3}, {-8, 4, 2}, {3, 12, 3}};
    Partition partition(std::move(intervals), intervals.size());

    while (partition.available())
    {
        std::array<std::array<int, 3>, 3> partition_data = partition.next();
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::ROUTING_KEY, partition_data);
    }

    for (int i = 0; i < n_workers; i++)
    {
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::ROUTING_KEY, std::string("stop"));
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
