#include "config_reader/config_reader.h"
#include "cpp-statsd-client/StatsdClient.hpp"
#include "interval/interval.h"
#include "interval/partition.h"
#include "manager/manager.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"
#include "utils/json_parsing.h"
#include <chrono>
#include <constants.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string graphiteHost = getGraphiteHost();
    uint16_t graphitePort = getGraphitePort();
    Statsd::StatsdClient statClient{graphiteHost, graphitePort, "manager"};
    chrono::milliseconds start_time_ms =
        chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

    json data = getDataFromJson("../resources/data.json");
    std::vector<Interval> intervals = intervalsFromJson(data["data"]);
    const std::string aggregation = data["agg"];

    MessageProcessor messageProcessor(aggregation);

    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();
    Protocol protocol(pushPort, pullPort);

    size_t n_workers = getNWorkers();
    Manager manager(n_workers, &protocol, &messageProcessor);

    manager.run(Partition(std::move(intervals), intervals.size(), data["maxItemsPerBatch"]), aggregation);

    // send the total processing time
    chrono::milliseconds end_time_ms =
        chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    chrono::milliseconds completion_time = end_time_ms - start_time_ms;
    statClient.gauge("completion_time", completion_time.count(), 1, {});
    std::cout << "sent completion_time" << std::endl;

    protocol.close();

    return 0;
}
