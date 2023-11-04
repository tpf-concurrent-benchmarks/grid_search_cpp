#include "config_reader/config_reader.h"
#include "interval/interval.h"
#include "interval/partition.h"
#include "manager/manager.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"
#include "utils/json_parsing.h"
#include <constants.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    json data = getDataFromJson("../resources/example-max.json");
    std::vector<Interval> intervals = intervalsFromJson(data["data"]);
    const std::string aggregation = data["agg"];

    MessageProcessor messageProcessor(aggregation);

    // TODO: These ports should be from the docker compose --> env variable
    Protocol protocol("5557", "5558");

    // TODO n_workers should be the same as the number of workers (replicas) in docker compose
    Manager manager(1, &protocol, &messageProcessor);

    manager.run(Partition(std::move(intervals), intervals.size(), data["maxItemsPerBatch"]), aggregation);

    return 0;
}
