
#include "accumulator.h"
#include <array>
#include <string>
#include <limits>

template <std::size_t Size> Accumulator<Size>::Accumulator(std::string accum_type)
{
    if (accum_type == "MAX")
    {
        callback_ = Accumulator::max;
        true_result = std::numeric_limits<float>::max();
    }
    else if (accum_type == "MIN")
    {
        callback_ = Accumulator::min;
        true_result = std::numeric_limits<float>::min();
    }
    else
    {
        callback_ = Accumulator::avg;
        true_result = 0;
    }
}

template<std::size_t Size>
void Accumulator<Size>::accumulate(float res, std::array<float, Size>& current) {
    callback_(res, current);
}

template <std::size_t Size>
float Accumulator<Size>::get_result() {
    return true_result;
}

template<std::size_t Size>
std::array<float, Size> Accumulator<Size>::get_input() {
    return true_input;
}

template<std::size_t Size>
void Accumulator<Size>::max(float res, std::array<float, Size> &current) {
    if (res > true_result){
        true_result = res;
        true_input = current;
    };
}

template<std::size_t Size>
void Accumulator<Size>::min(float res, std::array<float, Size> &current) {
    if (res < true_result){
        true_result = res;
        true_input = current;
    };
}

template<std::size_t Size>
void Accumulator<Size>::avg(float res, std::array<float, Size> &current) {
    true_result += res;
}

