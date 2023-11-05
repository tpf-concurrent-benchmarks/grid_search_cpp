#include "config_reader/config_reader.h"
#include "interval/interval.h"
#include "interval/partition.h"
#include "manager/manager.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"
#include "utils/json_parsing.h"
#include <constants.h>
#include <nlohmann/json.hpp>
#include <StatsdClient.hpp>

using json = nlohmann::json;

int main()
{
    Statsd::StatsdClient statClient{"localhost", 8125, "myPrefix"};
        // Increment the metric "coco"
    statClient.increment("coco");

    // Decrement the metric "kiki"
    statClient.decrement("kiki");

    // Adjusts "toto" by +3
    statClient.count("toto", 2, 0.1f);

    // Record a gauge "titi" to 3.2 with tags
    statClient.gauge("titi", 3.2, 0.1f, {"foo", "bar"});

    // Record a timing of 2ms for "myTiming"
    statClient.timing("myTiming", 2, 0.1f);

    // Record a count of unique occurences of "tutu"
    statClient.set("tutu", 4, 2.0f);

    exit(0);

    json data = getDataFromJson("../resources/example-max.json");
    std::vector<Interval> intervals = intervalsFromJson(data["data"]);
    const std::string aggregation = data["agg"];

    MessageProcessor messageProcessor(aggregation);

    // TODO: These ports should be from the docker compose --> env variable
    Protocol protocol("5557", "5558");

    // TODO n_workers should be the same as the number of workers (replicas) in docker compose
    Manager manager(1, &protocol, &messageProcessor);

    manager.run(Partition(std::move(intervals), intervals.size(), data["maxItemsPerBatch"]), aggregation);
    protocol.close();

    return 0;
}
