#ifndef WORKERGRIDSEARCH_OBJECTIVE_FUN_H
#define WORKERGRIDSEARCH_OBJECTIVE_FUN_H

#include <array>
#include <cmath>

float objectiveFun(std::array<float, 3> &values)
{
    float a = values[0];
    float b = values[1];
    float c = values[2];
    return (1.0 / 4000.0) * (a * a + b * b + c * c) - cos(a) * cos(b) * cos(c);
}

float maxSum(std::array<float, 3> &current, float res)
{
    float sum = current[0] + current[1] + current[2];
    if (sum > res)
    {
        return sum;
    }
    else
    {
        return res;
    }
}

#endif // WORKERGRIDSEARCH_OBJECTIVE_FUN_H