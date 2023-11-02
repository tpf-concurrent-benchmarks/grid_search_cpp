#ifndef PARAMS_H
#define PARAMS_H

#include <array>
#include <cstddef>
#include <string>

template <std::size_t Size> class Params
{
  public:
    Params(std::array<float, Size> &&start, std::array<float, Size> &&end, std::array<float, Size> &&step, std::string &&id);
    std::array<float, Size> &get_current();
    void next();
    int get_total_iterations();
    std::string get_id();

  private:
    std::array<float, Size> start_;
    std::array<float, Size> end_;
    std::array<float, Size> step_;
    std::array<float, Size> current_;
    int total_iterations;
    std::string id_;
};

#include "params.cpp"

#endif // PARAMS_H
