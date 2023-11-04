#ifndef MASTERGRIDSEARCH_UTILS_H
#define MASTERGRIDSEARCH_UTILS_H
#include <cmath>

float roundFloat(float num, int decimal_places)
{
    float multiplier = pow(10, decimal_places);
    return round(num * multiplier) / multiplier;
}

#endif // MASTERGRIDSEARCH_UTILS_H