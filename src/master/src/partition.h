#ifndef MASTERGRIDSEARCH_PARTITION_H
#define MASTERGRIDSEARCH_PARTITION_H

#include "interval.h"
#include <array>
#include <string>
#include <vector>

class Partition
{
  public:
    Partition(std::vector<Interval> &&intervals, size_t n_intervals);
    bool available() const;
    std::array<std::array<int, 3>, 3> next();
    std::vector<int> calc_partitions_per_interval(int max_chunk_size);

  private:
    // Dummy values for testing
    size_t n_partitions_ = 1;
    size_t current_partition_ = 0;
    std::array<std::array<int, 3>, 3> partitions = {{{0, 10, 1}, {0, 10, 1}, {0, 10, 1}}};
    size_t n_intervals;
    std::vector<Interval> intervals;
    int calc_amount_of_missing_partitions(int min_batches, std::vector<int> &partitions_per_interval);
    int calc_partitions_amount(std::vector<int> &partitions_per_interval);
    int interval_size(Interval &interval);
};

#include "partition.cpp"

#endif // MASTERGRIDSEARCH_PARTITION_H
