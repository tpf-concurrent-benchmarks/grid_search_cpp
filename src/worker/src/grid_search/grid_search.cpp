#include "grid_search.h"
#include <string>

template <std::size_t Size> void GridSearch<Size>::search(std::function<float(std::array<float, Size> &)> callback)
{
    std::array<float, Size> &current = params_.get_current();
    float res = callback(current);
    initAccumulation(res, current);
    params_.next();
    for (int i = 1; i < params_.get_total_iterations(); i++)
    {
        current = params_.get_current();
        res = callback(current);
        accumulate(res, current);
        params_.next();
    }
}

template <std::size_t Size> std::string GridSearch<Size>::getId()
{
    return params_.get_id();
}

template <std::size_t Size> void GridSearch<Size>::initAccumulation(float res, std::array<float, Size> &current)
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
    }
    else if (res < min)
    {
        min = res;
        min_input = current;
    }
    total += res;
}

template <std::size_t Size> float GridSearch<Size>::getMax()
{
    return max;
}

template <std::size_t Size> float GridSearch<Size>::getMin()
{
    return min;
}

template <std::size_t Size> float GridSearch<Size>::getTotal()
{
    return total;
}

template <std::size_t Size> int GridSearch<Size>::getTotalInputs()
{
    return total_inputs;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::getMaxInput()
{
    return max_input;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::getMinInput()
{
    return min_input;
}
