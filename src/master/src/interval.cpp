#include "interval.h"
#include "utils.h"
#include <algorithm>
#include <iostream>

Interval::Interval(float start, float end, float step) : start(start), end(end), step(step)
{
    size = ceil((end - start) / step);
}

std::vector<Interval> Interval::split(int n_partitions)
{
    if (n_partitions <= 0)
    {
        return std::vector<Interval>();
    }
    if (size % n_partitions == 0)
    {
        return split_evenly(n_partitions);
    }
    int max_elems_per_interval = ceil((float)size / (float)n_partitions);
    int n_sub_intervals_full = floor(((float)(size - n_partitions)) / ((float)(max_elems_per_interval - 1)));
    float sub_start;
    float sub_end;
    std::vector<Interval> intervals;
    for (int i = 0; i < n_sub_intervals_full; i++)
    {
        sub_start = roundFloat(start + (i * max_elems_per_interval * step), precision);
        sub_end = roundFloat(std::min(end, (sub_start + (max_elems_per_interval * step))), precision);
        intervals.push_back(Interval(sub_start, sub_end, step));
    }
    Interval interval_reminder = Interval(sub_end, end, step);
    std::vector<Interval> sub_intervals_reminder = interval_reminder.split(n_partitions - n_sub_intervals_full);
    intervals.insert(intervals.end(), sub_intervals_reminder.begin(), sub_intervals_reminder.end());
    return intervals;
}

std::vector<Interval> Interval::split_evenly(int n_partitions)
{
    std::vector<Interval> intervals;
    float sub_start;
    float sub_end;
    float interval_size = size / n_partitions;
    for (float i = 0; i < n_partitions; i++)
    {
        sub_start = roundFloat(start + (floor(i * ((float) size) / ((float) n_partitions)) * step), precision);
        sub_end = roundFloat(start + (floor((i + 1) * ((float) size) / ((float) n_partitions)) * step), precision);
        intervals.push_back(Interval(sub_start, sub_end, step));
    };
    return intervals;
}

void Interval::print()
{
    std::cout << "start: " << start << ", end: " << end << ", step: " << step << std::endl;
}

int Interval::interval_size()
{
    return size;
}

std::array<float, 3> Interval::get_interval()
{
    return {start, end, step};
}

void Interval::setPrecision(int _precision)
{
    precision = _precision;
}