#ifndef GRID_SEARCH_H
#define GRID_SEARCH_H

#include "params.h"
#include <functional>
#include <string>
#include <vector>

template <std::size_t Size> class GridSearch
{
  public:
    GridSearch(Params<Size> &&params, std::string _accum_type) : params_(std::move(params)), accum_type(_accum_type)
    {
    }
    void search(std::function<float(std::array<float, Size> &)> callback);
    float getMax();
    float getMin();
    float getTotal();
    int getTotalInputs();
    std::array<float, Size> getMaxInput();
    std::array<float, Size> getMinInput();
    float getResult();
    std::array<float, Size> getInput();

  private:
    Params<Size> params_;
    float max;
    float min;
    float total;
    float result;
    int total_inputs;
    std::string accum_type;
    std::array<float, Size> max_input;
    std::array<float, Size> min_input;
    std::array<float, Size> input;
    void initAccumulation(float res, std::array<float, Size> &current);
    void accumulate(float res, std::array<float, Size> &current);
};

#include "grid_search.cpp"

#endif // GRID_SEARCH_H