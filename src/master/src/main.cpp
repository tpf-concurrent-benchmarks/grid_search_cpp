#include "config_reader.h"
#include "constants.h"
#include "interval.h"
#include "json_parsing.h"
#include "partition.h"
#include "protocol.h"
#include "message_processor.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool allWorkersReady(size_t *n_workers, size_t *workersReady)
{
    return *workersReady == *n_workers;
}

bool allWorkersHaveFinished(size_t *n_workers)
{
    return *n_workers == 0;
}

int main()
{
    json data = getDataFromJson();
    std::cout << data.dump() << std::endl;
    std::vector<Interval> intervals = jsonToIntervals(data["data"]);

    const std::string aggregation = data["agg"];
    MessageProcessor messageProcessor(aggregation);

    // TODO n_workers should be the same as the number of workers in docker compose
    size_t n_workers = 1;
    size_t workersReady = 0;

    Protocol protocol;

    while (!allWorkersReady(&n_workers, &workersReady))
    {
        std::string message = protocol.receive();
        if (message == Constants::READY_MESSAGE)
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

    while (!allWorkersHaveFinished(&n_workers))
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

    messageProcessor.saveResults();

    return 0;
}
