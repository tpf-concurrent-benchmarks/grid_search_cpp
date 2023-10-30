#ifndef WORKERGRIDSEARCH_CONSTANTS_H
#define WORKERGRIDSEARCH_CONSTANTS_H

#include <string>

namespace Constants
{
const std::string EXCHANGE_NAME = "topic_grid_search";
const std::string WORK_QUEUE_NAME = "work";
const std::string RESULTS_QUEUE_NAME = "results";
const std::string WORK_ROUTING_KEY = "work";
const std::string RESULTS_ROUTING_KEY = "results";
const std::string STOP_MESSAGE = "stop";
const std::string END_WORK_MESSAGE = "end";
} // namespace Constants

#endif // WORKERGRIDSEARCH_CONSTANTS_H
