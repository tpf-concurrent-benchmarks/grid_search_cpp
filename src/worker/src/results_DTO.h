#ifndef WORKERGRIDSEARCH_RESULTS_DTO_H
#define WORKERGRIDSEARCH_RESULTS_DTO_H

#include "nlohmann/json.hpp"

class ResultsDTO
{
  public:
    virtual nlohmann::json toJson();
};

#include "results_DTO.cpp"

#endif // WORKERGRIDSEARCH_RESULTS_DTO_H
