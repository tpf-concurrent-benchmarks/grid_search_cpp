#ifndef PARAMS_H
#define PARAMS_H

#include <array>
#include <cstddef>

template <std::size_t Size> class Params
{
  public:
    Params(std::array<int, Size> &&start, std::array<int, Size> &&end, std::array<int, Size> &&step, std::string &&id);
    std::array<int, Size> &get_current();
    void next();
    int get_total_iterations();
    std::string get_id();

  private:
    std::array<int, Size> start_;
    std::array<int, Size> end_;
    std::array<int, Size> step_;
    std::array<int, Size> current_;
    int total_iterations;
    std::string id_;
};

#include "params.cpp"

#endif // PARAMS_H
