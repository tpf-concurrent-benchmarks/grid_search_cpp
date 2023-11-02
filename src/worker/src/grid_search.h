#ifndef GRID_SEARCH_H
#define GRID_SEARCH_H

#include "params.h"
#include <functional>
#include <string>
#include <vector>

template <std::size_t Size> class GridSearch
{
  public:
    GridSearch(Params<Size> &&params) : params_(std::move(params))
    {
    }
    void search(std::function<float(std::array<float, Size> &)> callback);
    std::string get_id();
    float get_max();
    float get_min();
    float get_total();
    int get_total_inputs(); 
    std::array<float, Size> get_max_input();
    std::array<float, Size> get_min_input();


  private:
    Params<Size> params_;
    float max;
    float min;
    float total;
    int total_inputs;
    std::array<float, Size> max_input;
    std::array<float, Size> min_input;
    void init_accumulation(float res, std::array<float, Size> &current);
    void accumulate(float res, std::array<float, Size> &current);
};

#include "grid_search.cpp"

#endif // GRID_SEARCH_H