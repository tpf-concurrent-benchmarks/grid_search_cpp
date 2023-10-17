#include "param.h"

int Param::next() {
    int value = start_ + index_ * step_;
    index_++;
    return value;
}

int Param::length() {
    return ((end_ - start_) / step_) + 1;
}

void Param::reset() {
    index_ = 0;
}