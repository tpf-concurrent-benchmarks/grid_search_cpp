#include "partition.h"
#include <iostream>
#include <math.h>
#include <numeric>

Partition::Partition(std::vector<Interval> &&intervals, size_t n_intervals)
    : intervals(std::move(intervals)), n_intervals(n_intervals)
{
    // TODO: remove this
    std::cout << n_intervals << std::endl;
}

bool Partition::available() const
{
    return current_partition_ < n_partitions_;
}

std::array<std::array<int, 3>, 3> Partition::next()
{
    current_partition_++;
    return partitions;
}

std::vector<int> Partition::calc_partitions_per_interval(int max_chunk_size)
{
    int min_batches = floor(n_intervals / max_chunk_size) + 1;
    std::cout << min_batches << std::endl;
    std::vector<int> partitions_per_interval(n_intervals, 1);
    int missing_partitions;
    int elements;
    for (int i = 0; i < n_intervals; i++)
    {
        missing_partitions = calc_amount_of_missing_partitions(min_batches, partitions_per_interval);

        elements = intervals[i].interval_size();
        if (elements > missing_partitions)
        {
            partitions_per_interval[i] *= missing_partitions;
        }
        else
        {
            partitions_per_interval[i] *= elements;
        }
    };
    return partitions_per_interval;
}

int Partition::calc_amount_of_missing_partitions(int min_batches, std::vector<int> &partitions_per_interval)
{
    return ceil(min_batches / calc_partitions_amount(partitions_per_interval));
}

int Partition::calc_partitions_amount(std::vector<int> &partitions_per_interval)
{
    return std::reduce(partitions_per_interval.begin(), partitions_per_interval.end(), 1, std::multiplies<int>());
}
