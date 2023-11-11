#include "params.h"
#include <cmath>
#include <iostream>

template <std::size_t Size>
Params<Size>::Params(std::array<float, Size> &&start, std::array<float, Size> &&end, std::array<float, Size> &&step)
    : start_(std::move(start)), end_(std::move(end)), step_(std::move(step))
{
    current_ = start_;
    total_iterations = 1;
    for (int i = 0; i < Size; ++i)
    {
        int cum_param = floor((end_[i] - start_[i]) / step_[i]);
        if (cum_param == 0)
        {
            cum_param = 1;
        }
        total_iterations *= cum_param;
    }
}

template <std::size_t Size> std::array<float, Size> &Params<Size>::get_current()
{
    return current_;
}

template <std::size_t Size> void Params<Size>::next()
{
    for (int i = Size - 1; i >= 0; --i)
    {
        if (current_[i] + step_[i] < end_[i])
        {
            current_[i] += step_[i];
            break;
        }
        else
        {
            current_[i] = start_[i];
        }
    }
}

template <std::size_t Size> long Params<Size>::get_total_iterations()
{
    return total_iterations;
}
