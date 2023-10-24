#include "params.h"

template <std::size_t Size>
Params<Size>::Params(std::array<int, Size>&& start, std::array<int, Size>&& end, std::array<int, Size>&& step)
    : start_(std::move(start)), end_(std::move(end)), step_(std::move(step))
{
    current_ = start_;
    total_iterations = 1;
    for (int i = 0; i < Size; ++i)
    {
        total_iterations *= ((end_[i] - start_[i]) / step_[i]) + 1;
    }
}

template <std::size_t Size> std::array<int, Size> &Params<Size>::get_current()
{
    return current_;
}

template <std::size_t Size> void Params<Size>::next()
{
    for (int i = Size - 1; i >= 0; --i)
    {
        if (current_[i] + step_[i] <= end_[i])
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

template <std::size_t Size> int Params<Size>::get_total_iterations()
{
    return total_iterations;
}