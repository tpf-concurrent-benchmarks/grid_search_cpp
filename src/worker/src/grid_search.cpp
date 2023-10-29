#include <string>
#include "grid_search.h"

template <std::size_t Size> int GridSearch<Size>::search(std::function<int(std::array<int, Size> &, int)> callback)
{
    int res = 0;
    for (int i = 0; i < params_.get_total_iterations(); i++)
    {
        std::array<int, Size> current = params_.get_current();
        res = callback(current, res);
        params_.next();
    }
    return res;
}

template <std::size_t Size> std::string GridSearch<Size>::get_id()
{
    return params_.get_id();
}
