#include "config_reader.h"
#include "constants.h"
#include "partition.h"
#include "protocol.h"
#include <nlohmann/json.hpp>
#include "interval.h"

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    int n_workers = 1;
    size_t n_partitions = 1;

    Protocol protocol(brokerAddress, n_workers);

    std::vector<Interval> intervals{Interval(0, 12, 3), Interval(-8, 4, 2), Interval(3, 12, 3)};
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

    std::vector<std::vector<Interval>> splited_intervals = partition.split(7);
    std::cout << "amount of partitions:" << splited_intervals.size() << std::endl;
    for (auto interval : splited_intervals) {
        std::cout << "partition:" << std::endl;
        for (auto interval2 : interval) {
            interval2.print();
        }
    }
    return 0;
}
