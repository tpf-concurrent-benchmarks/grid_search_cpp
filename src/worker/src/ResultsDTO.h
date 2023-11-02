#ifndef WORKERGRIDSEARCH_RESULTSDTO_H
#define WORKERGRIDSEARCH_RESULTSDTO_H

#include <array>

class ResultsDTO {

public:
    ResultsDTO(float value, const std::array<float, 3>& parameters);
    float getValue() const;
    std::array<float, 3> getParameters() const;

private:
    float value_;
    std::array<float, 3> parameters_;
};

#include "ResultsDTO.cpp"


#endif //WORKERGRIDSEARCH_RESULTSDTO_H
