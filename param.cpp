#include "param.h"

int Param::next() {
    int value = start_ + index_ * step_;
    index_++;
    return value;
}

int Param::length() {
    return length_;
}

void Param::reset() {
    index_ = 0;
}

bool Param::is_last() {
    return index_ < length_;
}