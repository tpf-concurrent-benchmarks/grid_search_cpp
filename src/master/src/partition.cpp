#include "partition.h"
#include <cmath>
#include <numeric>

Partition::Partition(std::vector<Interval> &&intervals, size_t n_intervals, int max_chunk_size)
    : intervals(std::move(intervals)), n_intervals(n_intervals)
{
    split(max_chunk_size);
}

bool Partition::available() const
{
    return current_partition_ < n_partitions_;
}

std::vector<Interval> Partition::next()
{
    std::vector<Interval> _partition;
    for (int j = 0; j < n_intervals; j++)
    {
        _partition.push_back(splited_intervals[j][current_index[j]]);
    };
    for (int j = 0; j < n_intervals; j++)
    {
        if (current_index[j] + 1 < partitions_per_interval[j])
        {
            current_index[j]++;
            break;
        }
        else
        {
            current_index[j] = 0;
        }
    }
    current_partition_++;
    return _partition;
}

std::vector<int> Partition::calc_partitions_per_interval(int min_batches)
{
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
    return ceil(((float)min_batches) / ((float)calc_partitions_amount(partitions_per_interval)));
}

int Partition::calc_partitions_amount(std::vector<int> &partitions_per_interval)
{
    return std::reduce(partitions_per_interval.begin(), partitions_per_interval.end(), 1, std::multiplies<int>());
}

void Partition::split(int max_chunk_size)
{
    int min_batches = floor(full_calculation_size() / max_chunk_size) + 1;

    partitions_per_interval = calc_partitions_per_interval(min_batches);
    n_partitions_ = calc_partitions_amount(partitions_per_interval);
    for (int i = 0; i < n_intervals; i++)
    {
        splited_intervals.push_back(intervals[i].split(partitions_per_interval[i]));
    }
    iterations = calc_partitions_amount(partitions_per_interval);
    current_index = std::vector<int>(n_intervals, 0);
}

std::vector<std::vector<Interval>> Partition::cartesian_product(std::vector<std::vector<Interval>> &splited_intervals,
                                                                std::vector<int> &partitions_per_interval)
{
    int iterations = calc_partitions_amount(partitions_per_interval);
    std::vector<std::vector<Interval>> result;
    std::vector<int> current_index(n_intervals, 0);
    for (int i = 0; i < iterations; i++)
    {
        std::vector<Interval> temp;
        for (int j = 0; j < n_intervals; j++)
        {
            temp.push_back(splited_intervals[j][current_index[j]]);
        };
        result.push_back(temp);
        for (int j = 0; j < n_intervals; j++)
        {
            if (current_index[j] + 1 < partitions_per_interval[j])
            {
                current_index[j]++;
                break;
            }
            else
            {
                current_index[j] = 0;
            }
        }
    }
    return result;
}

int Partition::full_calculation_size()
{
    int result = 1;
    for (int i = 0; i < n_intervals; i++)
    {
        result *= intervals[i].interval_size();
    }
    return result;
}