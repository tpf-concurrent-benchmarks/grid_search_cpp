#include "grid_search.h"
#include <string>

template <std::size_t Size> void GridSearch<Size>::search(std::function<float(std::array<float, Size> &)> callback)
{
    std::array<float, Size> &current = params_.get_current();
    float res = callback(current);
    init_accumulation(res, current);
    params_.next();
    for (int i = 1; i < params_.get_total_iterations(); i++)
    {
        current = params_.get_current();
        res = callback(current);
        accumulate(res, current);
        params_.next();
    }
}

template <std::size_t Size> std::string GridSearch<Size>::get_id()
{
    return params_.get_id();
}

template <std::size_t Size> void GridSearch<Size>::init_accumulation(float res, std::array<float, Size> &current)
{
    max = res;
    min = res;
    total = res;
    max_input = current;
    min_input = current;
    total_inputs = params_.get_total_iterations();
}

template <std::size_t Size> void GridSearch<Size>::accumulate(float res, std::array<float, Size> &current)
{
    if (res > max)
    {
        max = res;
        max_input = current;
    } else if (res < min)
    {
        min = res;
        min_input = current;
    }
    total += res;
}

template <std::size_t Size> float GridSearch<Size>::get_max()
{
    return max;
}

template <std::size_t Size> float GridSearch<Size>::get_min()
{
    return min;
}

template <std::size_t Size> float GridSearch<Size>::get_total()
{
    return total;
}

template <std::size_t Size> int GridSearch<Size>::get_total_inputs()
{
    return total_inputs;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::get_max_input()
{
    return max_input;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::get_min_input()
{
    return min_input;
}
