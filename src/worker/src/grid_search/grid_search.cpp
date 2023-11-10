#include "grid_search.h"
#include <string>
#include "accumulator.h"
#include <iostream>

template <std::size_t Size> void GridSearch<Size>::search(std::function<float(std::array<float, Size> &)> callback)
{
    Accumulator<Size> accumulator(accum_type);
    float res;
    std::cout << "total iterations" << params_.get_total_iterations() << std::endl;

    for (double i = 0; i < params_.get_total_iterations(); i++)
    {
        std::array<float, Size> &current = params_.get_current();
        res = callback(current);
        accumulator.accumulate(res, current);
        params_.next();
    }
    result = accumulator.get_result();
    std::cout << "result" << result << std::endl;
    input = accumulator.get_input();
}

template <std::size_t Size> int GridSearch<Size>::getTotalInputs()
{
    return total_inputs;
}

template <std::size_t Size> float GridSearch<Size>::getResult()
{
    return result;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::getInput()
{
    return input;
}