#ifndef WORKERGRIDSEARCH_OBJECTIVE_FUN_H
#define WORKERGRIDSEARCH_OBJECTIVE_FUN_H

#include <cmath>
#include <array>

double objectiveFun(const double a, const double b, const double c)
{
    return (1.0 / 4000.0) * (a * a + b * b + c * c) - cos(a) * cos(b) * cos(c);
}

int maxSum(std::array<int, 3> &current, int res)
{
    int sum = current[0] + current[1] + current[2];
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
