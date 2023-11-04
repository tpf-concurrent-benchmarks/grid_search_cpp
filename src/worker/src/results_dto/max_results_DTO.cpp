#include "max_results_DTO.h"

MaxResultsDTO::MaxResultsDTO(float value, const std::array<float, 3> &parameters)
    : value_(value), parameters_(parameters)
{
}

nlohmann::json MaxResultsDTO::toJson()
{
    return {{"value", value_}, {"parameters", parameters_}};
}
