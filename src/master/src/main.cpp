#include "config_reader.h"
#include "constants.h"
#include "interval.h"
#include "partition.h"
#include "protocol.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    json data = getDataFromJson();
    std::cout << data.dump(4) << std::endl;

    int n_workers = 1;

    Protocol protocol(brokerAddress, n_workers);

    std::vector<Interval> intervals{Interval(0, 12, 3), Interval(-8, 4, 2), Interval(3, 12, 3)};
    Partition partition(std::move(intervals), intervals.size(), 7);

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
