#ifndef PARAMS_H
#define PARAMS_H

#include <array>
#include <cstddef>

template <std::size_t Size> class Params
{
  public:
    Params(std::array<int, Size> &&start, std::array<int, Size> &&end, std::array<int, Size> &&step);
    std::array<int, Size> &get_current();
    void next();
    int get_total_iterations();

  private:
    std::array<int, Size> start_;
    std::array<int, Size> end_;
    std::array<int, Size> step_;
    std::array<int, Size> current_;
    int total_iterations;
};

// This fixes the linker error, since Params<2> params(start, end, step) on main.cpp doesn't know what the template
// class is https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
#include "params.cpp"

#endif // PARAMS_H
