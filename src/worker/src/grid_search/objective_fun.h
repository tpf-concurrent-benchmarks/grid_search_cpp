#ifndef WORKERGRIDSEARCH_OBJECTIVE_FUN_H
#define WORKERGRIDSEARCH_OBJECTIVE_FUN_H

#include <array>
#include <cmath>

float griewankFun(std::array<float, 3> &parameters)
{
    float a = parameters[0];
    float b = parameters[1];
    float c = parameters[2];
    return (1.0 / 4000.0) * (a * a + b * b + c * c) - cos(a) * cos(b / sqrt(2)) * cos(c / sqrt(3)) + 1;
}

#endif // WORKERGRIDSEARCH_OBJECTIVE_FUN_H
