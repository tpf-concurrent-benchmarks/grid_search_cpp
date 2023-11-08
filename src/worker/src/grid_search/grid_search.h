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
    int getTotalInputs();
    float getResult();
    std::array<float, Size> getInput();

  private:
    Params<Size> params_;
    float result;
    int total_inputs;
    std::string accum_type;
    std::array<float, Size> input;
};

#include "grid_search.cpp"

#endif // GRID_SEARCH_H