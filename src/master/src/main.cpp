#include "config_reader.h"
#include "constants.h"
#include "interval.h"
#include "partition.h"
#include "protocol.h"
#include <nlohmann/json.hpp>
#include "json_parsing.h"

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    json data = getDataFromJson();
    std::cout << data.dump() << std::endl;
    std::vector<Interval> intervals = jsonToIntervals(data["data"]);

    // TODO n_workers should be the same as the number of workers in docker compose
    int n_workers = 1;
    // TODO the aggregation should be passed as a parameter, stored in data["agg"]
    const std::string aggregation = data["agg"];
    MessageProcessor messageProcessor(aggregation);
    Protocol protocol(brokerAddress, messageProcessor, n_workers);

    // Dummy value for testing
    Partition partition(std::move(intervals), intervals.size(), 7);

    while (partition.available())
    {
        auto partition_data = partition.next();
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::WORK_ROUTING_KEY, partition_data, aggregation);
    }

    for (int i = 0; i < n_workers; i++)
    {
        protocol.sendData(Constants::EXCHANGE_NAME, Constants::WORK_ROUTING_KEY, Constants::STOP_MESSAGE);
    }

    protocol.installConsumer();

    return 0;
}
