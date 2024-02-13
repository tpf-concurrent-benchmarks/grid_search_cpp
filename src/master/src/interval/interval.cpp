#include "interval.h"
#include "../utils/utils.h"
#include <algorithm>
#include <iostream>

Interval::Interval(float start, float end, float step) : start_(start), end_(end), step_(step)
{
    size_ = ceil((end - start) / step);
}

std::vector<Interval> Interval::split(size_t n_partitions)
{
    if (n_partitions <= 0)
    {
        return {};
    }
    if (size_ % n_partitions == 0)
    {
        return split_evenly(n_partitions);
    }
    int max_elems_per_interval = ceil((float)size_ / (float)n_partitions);
    int n_sub_intervals_full = floor(((float)(size_ - n_partitions)) / ((float)(max_elems_per_interval - 1)));
    float sub_start;
    float sub_end;
    std::vector<Interval> intervals;
    for (int i = 0; i < n_sub_intervals_full; i++)
    {
        sub_start = roundFloat(start_ + (i * max_elems_per_interval * step_), precision_);
        sub_end = roundFloat(std::min(end_, (sub_start + (max_elems_per_interval * step_))), precision_);
        intervals.emplace_back(sub_start, sub_end, step_);
    }
    Interval interval_reminder = Interval(sub_end, end_, step_);
    std::vector<Interval> sub_intervals_reminder = interval_reminder.split(n_partitions - n_sub_intervals_full);
    intervals.insert(intervals.end(), sub_intervals_reminder.begin(), sub_intervals_reminder.end());
    return intervals;
}

//this method is invoked when the number of partitions is a divisor of the size of the interval
std::vector<Interval> Interval::split_evenly(size_t n_partitions)
{
    std::vector<Interval> intervals;
    float sub_start;
    float sub_end;
    for (float i = 0; i < n_partitions; i++)
    {
        sub_start = roundFloat(start_ + (floor(i * ((float)size_) / ((float)n_partitions)) * step_), precision_);
        sub_end = roundFloat(start_ + (floor((i + 1) * ((float)size_) / ((float)n_partitions)) * step_), precision_);
        intervals.emplace_back(sub_start, sub_end, step_);
    };
    return intervals;
}

void Interval::print()
{
    std::cout << "start: " << start_ << ", end: " << end_ << ", step: " << step_ << std::endl;
}

size_t Interval::intervalSize()
{
    return size_;
}

std::array<float, 3> Interval::getInterval()
{
    return {start_, end_, step_};
}

//a precision can be set for the float operations, this aids in not having floating point errors
//that affect the rounding operations when the foating values are whole numbers
void Interval::setPrecision(size_t precision)
{
    precision_ = precision;
}