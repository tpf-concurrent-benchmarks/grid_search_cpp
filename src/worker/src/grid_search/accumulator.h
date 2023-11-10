#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <array>
#include <cstddef>
#include <functional>
#include <string>

template <std::size_t Size> class Accumulator
{
  public:
    using Callback = std::function<void(float, std::array<float, Size> &)>;

    Accumulator(std::string accum_type);

    void accumulate(float res, std::array<float, Size> &current);

    float get_result();
    std::array<float, Size> get_input();

  private:
    Callback callback_;
    float true_result;
    std::array<float, Size> true_input;
    void max(float res, std::array<float, Size> &current);
    void min(float res, std::array<float, Size> &current);
    void avg(float res, std::array<float, Size> &current);
};

#include "accumulator.cpp"

#endif // ACCUMULATOR_H