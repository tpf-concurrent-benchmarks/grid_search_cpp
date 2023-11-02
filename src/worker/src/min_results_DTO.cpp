#include "min_results_DTO.h"

MinResultsDTO::MinResultsDTO(float value, const std::array<float, 3> &parameters)
    : value_(value), parameters_(parameters)
{
}

nlohmann::json MinResultsDTO::toJson()
{
    return {{"value", value_}, {"parameters", parameters_}};
}
