#include "config_reader.h"
#include "constants.h"
#include "interval.h"
#include "json_parsing.h"
#include "partition.h"
#include "protocol.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string brokerAddress = getBrokerAddress();
    json data = getDataFromJson();
    std::cout << data.dump() << std::endl;
    std::vector<Interval> intervals = jsonToIntervals(data["data"]);

    const std::string aggregation = data["agg"];
    MessageProcessor messageProcessor(aggregation);

    // TODO n_workers should be the same as the number of workers in docker compose
    size_t n_workers = 1;
    size_t workersReady = 0;

    Protocol protocol(messageProcessor, n_workers);

    while (workersReady != n_workers)
    {
        std::string message = protocol.receive();
        if (message == "ready")
        {
            workersReady++;
        }
    }

    Partition partition(std::move(intervals), intervals.size(), data["maxItemsPerBatch"]);

    while (partition.available())
    {
        auto partition_data = partition.next();
        protocol.send(partition_data, aggregation);
    }

    for (size_t i = 0; i < n_workers; i++)
    {
        protocol.send(Constants::STOP_MESSAGE);
    }

    while (n_workers != 0)
    {
        std::string message = protocol.receive();
        if (message == Constants::END_WORK_MESSAGE)
        {
            n_workers--;
        }
        else
        {
            messageProcessor.processMessage(json::parse(message));
        }
    }

    return 0;
}
