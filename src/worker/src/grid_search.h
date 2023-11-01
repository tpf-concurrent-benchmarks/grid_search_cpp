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
    int search(std::function<int(std::array<int, Size> &, int)> callback);
    std::string get_id();

  private:
    Params<Size> params_;
};

#include "grid_search.cpp"

#endif // GRID_SEARCH_H