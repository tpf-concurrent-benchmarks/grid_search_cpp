#include "grid_search.h"
#include <string>
#include <iostream>

//TODO borrar
#include <functional>
#include <array>
#include <string>
#include <cstddef>

template<std::size_t Size>
class Accumulator {
public:
    using Callback = std::function<void(float, std::array<float, Size> &)>;

    Accumulator(std::string accum_type);

    void accumulate(float res, std::array<float, Size> &current);

    float get_result();
    std::array<float, Size> get_input();

private:
    Callback callback_;
    float true_result;
    std::array<float, Size> true_input;
    void max(float res, std::array<float, Size> &current);
    void min(float res, std::array<float, Size> &current);
    void avg(float res, std::array<float, Size> &current);
};

#include <array>
#include <string>
#include <limits>

template <std::size_t Size> Accumulator<Size>::Accumulator(std::string accum_type)
{
    if (accum_type == "MAX")
    {
        callback_ = [this](float res, std::array<float, Size>& current) { this->max(res, current); };
        true_result = std::numeric_limits<float>::lowest();
    }
    else if (accum_type == "MIN")
    {
        callback_ = [this](float res, std::array<float, Size>& current) { this->min(res, current); };
        true_result = std::numeric_limits<float>::max();
    }
    else
    {
        callback_ = [this](float res, std::array<float, Size>& current) { this->avg(res, current); };
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
    std::cout << "res: " << res << std::endl;
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
//hasta aca

template <std::size_t Size> void GridSearch<Size>::search(std::function<float(std::array<float, Size> &)> callback)
{
    Accumulator<Size> accumulator(accum_type);
    float res;
    std::cout << "total iterations: " << params_.get_total_iterations() << std::endl;
    for (int i = 0; i < params_.get_total_iterations(); i++)
    {
        std::array<float, Size> &current = params_.get_current();
        res = callback(current);
        accumulator.accumulate(res, current);
        params_.next();
    }
    result = accumulator.get_result();
    input = accumulator.get_input();
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

template <std::size_t Size> float GridSearch<Size>::getResult()
{
    return result;
}

template <std::size_t Size> std::array<float, Size> GridSearch<Size>::getInput()
{
    return input;
}