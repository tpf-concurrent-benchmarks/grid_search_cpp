#ifndef MASTERGRIDSEARCH_INTERVAL_H
#define MASTERGRIDSEARCH_INTERVAL_H
#include <vector>

class Interval 
{
    public:
        Interval(float start, float end, float step);
        std::vector<Interval> split(int n_partitions);
        void print();
        int interval_size();

    private:
        float start;
        float end;
        float step;
        int size;
        std::vector<Interval> split_evenly(int n_partitions);
};

#include "interval.cpp"

#endif //MASTERGRIDSEARCH_INTERVAL_H