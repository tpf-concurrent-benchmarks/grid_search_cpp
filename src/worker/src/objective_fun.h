#ifndef WORKERGRIDSEARCH_OBJECTIVE_FUN_H
#define WORKERGRIDSEARCH_OBJECTIVE_FUN_H

#include <cmath>

float objectiveFun(std::array<float, 3> &values)
{
    float a = values[0];
    float b = values[1];
    float c = values[2];    
    return (1.0 / 4000.0) * (a * a + b * b + c * c) - cos(a) * cos(b) * cos(c);
}

#endif // WORKERGRIDSEARCH_OBJECTIVE_FUN_H
