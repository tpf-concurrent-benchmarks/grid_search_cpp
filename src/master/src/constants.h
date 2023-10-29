#ifndef MASTERGRIDSEARCH_CONSTANTS_H
#define MASTERGRIDSEARCH_CONSTANTS_H

#include <string>

namespace Constants {
    const std::string EXCHANGE_NAME = "topic_grid_search";
    const std::string ROUTING_KEY = "test.topic";
    const std::string WORK_QUEUE_NAME = "work";
    const std::string RESULTS_QUEUE_NAME = "results";
}

#endif //MASTERGRIDSEARCH_CONSTANTS_H
