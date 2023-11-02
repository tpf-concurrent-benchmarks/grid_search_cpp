#ifndef WORKERGRIDSEARCH_MAX_RESULTS_DTO_H
#define WORKERGRIDSEARCH_MAX_RESULTS_DTO_H

#include "nlohmann/json.hpp"
#include "results_DTO.h"

class MaxResultsDTO : public ResultsDTO
{

  public:
    MaxResultsDTO(float value, const std::array<float, 3> &parameters);
    nlohmann::json toJson() override;

  private:
    float value_;
    std::array<float, 3> parameters_;
};

#include "max_results_DTO.cpp"

#endif // WORKERGRIDSEARCH_MAX_RESULTS_DTO_H
