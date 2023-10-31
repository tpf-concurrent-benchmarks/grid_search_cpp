#ifndef WORKERGRIDSEARCH_OBJECTIVE_FUN_H
#define WORKERGRIDSEARCH_OBJECTIVE_FUN_H

#include <cmath>

double objectiveFun(const double a, const double b, const double c) {
    return (1.0 / 4000.0) * (a * a + b * b + c * c) - cos(a) * cos(b) * cos(c);
}


#endif //WORKERGRIDSEARCH_OBJECTIVE_FUN_H
