#ifndef MASTERGRIDSEARCH_INTERVAL_H
#define MASTERGRIDSEARCH_INTERVAL_H

#include <array>
#include <vector>

//This class defines one interval for one parameter of the grid search algorithm
//The interval is defined by its start point, end point and step, all of them are floats
class Interval
{
  public:
    Interval(float start, float end, float step);
    std::vector<Interval> split(size_t n_partitions);
    std::array<float, 3> getInterval();
    void print();
    size_t intervalSize();
    void setPrecision(size_t precision);

  private:
    float start_;
    float end_;
    float step_;
    size_t size_;
    size_t precision_ = 10;
    std::vector<Interval> split_evenly(size_t n_partitions);
};

#include "interval.cpp"

#endif // MASTERGRIDSEARCH_INTERVAL_H