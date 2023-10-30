#include "interval.h"
#include <math.h>

Interval::Interval(float start, float end, float step) : start(start), end(end), step(step)
{
    size = ceil((end - start) / step);
}

std::vector<Interval> Interval::split(int n_partitions)
{
    if (size % n_partitions == 0)
    {
        return split_evenly(n_partitions);
    }
    int max_elems_per_interval = ceil(size / n_partitions);
    int n_sub_intervals_full = floor((size - n_partitions) / (max_elems_per_interval - 1));
    float sub_start;
    float sub_end;
    std::vector<Interval> intervals;
    for (int i = 0; i < n_sub_intervals_full; i++)
    {
        sub_start = start + (i * max_elems_per_interval * step);
        sub_end = start + (sub_start + (max_elems_per_interval * step));
        intervals.push_back(Interval(sub_start, sub_end, step));
    }
    intervals.push_back(Interval(sub_end, end, step));
    return intervals;
}

std::vector<Interval> Interval::split_evenly(int n_partitions)
{
    std::vector<Interval> intervals;
    float sub_start;
    float sub_end;
    float interval_size = size / n_partitions;
    for (int i = 0; i < n_partitions; i++)
    {
        sub_start = start + (floor(i * size / n_partitions) * step);
        sub_end = start + (floor((i + 1) * size / n_partitions) * step);
        intervals.push_back(Interval(sub_start, sub_end, step));
    };
    return intervals;
}
