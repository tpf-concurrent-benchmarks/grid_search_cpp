#ifndef WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
#define WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H

#include "../results_dto/results_DTO.h"
#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>
#include <StatsdClient.hpp>
#include "../grid_search/grid_search.h"

using json = nlohmann::json;

class MessageProcessor
{

  public:
    MessageProcessor();
    ResultsDTO *processMessage(json message);

  private:
    Statsd::StatsdClient statClient;
    ResultsDTO *aggregate(GridSearch<3> &grid_search, std::string &aggregation);
};

#include "message_processor.cpp"

#endif // WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
