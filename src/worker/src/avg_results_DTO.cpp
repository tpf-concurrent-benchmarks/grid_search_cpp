#include "avg_results_DTO.h"

AvgResultsDTO::AvgResultsDTO(float value, size_t parametersAmount) : value_(value), parametersAmount_(parametersAmount)
{
}

nlohmann::json AvgResultsDTO::toJson()
{
    return {{"value", value_}, {"paramsAmount", parametersAmount_}};
}
