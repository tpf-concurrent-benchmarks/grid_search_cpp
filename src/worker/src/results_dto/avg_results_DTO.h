#ifndef WORKERGRIDSEARCH_AVG_RESULTS_DTO_H
#define WORKERGRIDSEARCH_AVG_RESULTS_DTO_H

#include "results_DTO.h"

class AvgResultsDTO : public ResultsDTO
{
  public:
    AvgResultsDTO(float value, size_t parametersAmount);
    nlohmann::json toJson() override;

  private:
    float value_;
    size_t parametersAmount_;
};

#include "avg_results_DTO.cpp"

#endif // WORKERGRIDSEARCH_AVG_RESULTS_DTO_H
