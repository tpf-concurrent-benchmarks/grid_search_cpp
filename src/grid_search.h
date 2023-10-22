#ifndef GRID_SEARCH_H
#define GRID_SEARCH_H

#include "params.h"
#include <functional>
#include <vector>

template <std::size_t Size> class GridSearch
{
  public:
    GridSearch(Params<Size> &params) : params_(params)
    {
    }
    int search(std::function<int(std::array<int, Size> &, int)> callback);

  private:
    Params<Size> &params_;
};

#include "grid_search.cpp"

#endif // GRID_SEARCH_H