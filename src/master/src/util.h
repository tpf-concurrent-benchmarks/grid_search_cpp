#ifndef MASTERGRIDSEARCH_UTIL_H
#define MASTERGRIDSEARCH_UTIL_H
#include <cmath>

float round_float(float num, int decimal_places) {
    float multiplier = pow(10, decimal_places);
    return round(num * multiplier) / multiplier;
}

#endif //MASTERGRIDSEARCH_UTIL_H