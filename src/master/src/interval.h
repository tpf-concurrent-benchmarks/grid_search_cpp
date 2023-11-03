#ifndef MASTERGRIDSEARCH_INTERVAL_H
#define MASTERGRIDSEARCH_INTERVAL_H
#include <array>
#include <vector>

class Interval
{
  public:
    Interval(float start, float end, float step);
    std::vector<Interval> split(int n_partitions);
    std::array<float, 3> get_interval();
    void print();
    int interval_size();
    void setPrecision(int _precision);

  private:
    float start;
    float end;
    float step;
    int size;
    int precision = 10;
    std::vector<Interval> split_evenly(int n_partitions);
};

#include "interval.cpp"

#endif // MASTERGRIDSEARCH_INTERVAL_H