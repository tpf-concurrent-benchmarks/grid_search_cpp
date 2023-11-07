#ifndef WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
#define WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H

#include "../grid_search/grid_search.h"
#include "../results_dto/results_DTO.h"
#include "nlohmann/json.hpp"
#include <StatsdClient.hpp>
#include <cstdint>
#include <string>

using json = nlohmann::json;

class MessageProcessor
{

  public:
    MessageProcessor(std::string ID);
    ResultsDTO *processMessage(json message);

  private:
    Statsd::StatsdClient statClient;
    ResultsDTO *aggregate(GridSearch<3> &grid_search, std::string &aggregation);
};

#include "message_processor.cpp"

#endif // WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
