#ifndef MASTERGRIDSEARCH_CONSTANTS_H
#define MASTERGRIDSEARCH_CONSTANTS_H

#include <string>

namespace Constants {
    const std::string EXCHANGE_NAME = "topic_grid_search";
    const std::string WORK_QUEUE_NAME = "work";
    const std::string RESULTS_QUEUE_NAME = "results";
    const std::string ROUTING_KEY_WORK = "work";
    const std::string ROUTING_KEY_RESULTS = "results";
}

#endif //MASTERGRIDSEARCH_CONSTANTS_H
