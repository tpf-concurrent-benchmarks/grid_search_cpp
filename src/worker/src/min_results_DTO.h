#ifndef WORKERGRIDSEARCH_MIN_RESULTS_DTO_H
#define WORKERGRIDSEARCH_MIN_RESULTS_DTO_H

#include "results_DTO.h"

class MinResultsDTO : public ResultsDTO
{

  public:
    MinResultsDTO(float value, const std::array<float, 3> &parameters);
    nlohmann::json toJson() override;

  private:
    float value_;
    std::array<float, 3> parameters_;
};

#endif // WORKERGRIDSEARCH_MIN_RESULTS_DTO_H
