#ifndef PARAMS_H
#define PARAMS_H

#include <array>
#include <cstddef>
#include <string>

//This class stores the parameters of the grid search and
// dinamically generates the inputs needed for the algorithm
template <std::size_t Size> class Params
{
  public:
    Params(std::array<float, Size> &&start, std::array<float, Size> &&end, std::array<float, Size> &&step);
    std::array<float, Size> &get_current();
    void next();
    long get_total_iterations();

  private:
    std::array<float, Size> start_;
    std::array<float, Size> end_;
    std::array<float, Size> step_;
    std::array<float, Size> current_;
    long total_iterations;
};

#include "params.cpp"

#endif // PARAMS_H
