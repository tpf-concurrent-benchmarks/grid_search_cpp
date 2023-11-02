#include "ResultsDTO.h"

ResultsDTO::ResultsDTO(float value, const std::array<float, 3> &parameters) : value_(value), parameters_(parameters) {

}

float ResultsDTO::getValue() const {
    return value_;
}

std::array<float, 3> ResultsDTO::getParameters() const {
    return parameters_;
}
