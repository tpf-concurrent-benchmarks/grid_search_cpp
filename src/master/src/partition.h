#ifndef MASTERGRIDSEARCH_PARTITION_H
#define MASTERGRIDSEARCH_PARTITION_H

#include <array>
#include <string>
#include <vector>
#include "interval.h"

class Partition
{
  public:
    Partition(std::vector<Interval> &&intervals, size_t n_intervals);
    bool available() const;
    std::array<std::array<int, 3>, 3> next();
    std::vector<std::vector<Interval>> split(int max_chunk_size);
    std::vector<int> calc_partitions_per_interval(int min_batches);

  private:
    size_t n_partitions_;
    size_t current_partition_ = 0;
    size_t n_intervals;
    std::vector<Interval> intervals;
    // Example partitions
    std::array<std::array<int, 3>, 3> partitions = {{{0, 10, 1}, {0, 10, 1}, {0, 10, 1}}};
    int calc_amount_of_missing_partitions(int min_batches, std::vector<int>& partitions_per_interval);
    int calc_partitions_amount(std::vector<int>& partitions_per_interval);
    std::vector<std::vector<Interval>> cartesian_product(
      std::vector<std::vector<Interval>>& splited_intervals,
      std::vector<int>& partitions_per_interval
    );
    int full_calculation_size();
};

#include "partition.cpp"

#endif // MASTERGRIDSEARCH_PARTITION_H
