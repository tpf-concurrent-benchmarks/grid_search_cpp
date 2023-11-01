#ifndef MASTERGRIDSEARCH_PARTITION_H
#define MASTERGRIDSEARCH_PARTITION_H

#include "interval.h"
#include <array>
#include <string>
#include <vector>

class Partition
{
  public:
    Partition(std::vector<Interval> &&intervals, size_t n_intervals, int max_chunk_size);
    bool available() const;
    std::vector<Interval> next();
    void split(int max_chunk_size);
    std::vector<int> calc_partitions_per_interval(int min_batches);

  private:
    size_t n_partitions_;
    size_t current_partition_ = 0;
    size_t n_intervals;
    int iterations;
    std::vector<Interval> intervals;
    std::vector<int> partitions_per_interval;
    std::vector<std::vector<Interval>> splited_intervals;
    std::vector<int> current_index;
    
    int calc_amount_of_missing_partitions(int min_batches, std::vector<int> &partitions_per_interval);
    int calc_partitions_amount(std::vector<int> &partitions_per_interval);
    std::vector<std::vector<Interval>> cartesian_product(std::vector<std::vector<Interval>> &splited_intervals,
                                                         std::vector<int> &partitions_per_interval);
    int full_calculation_size();
};

#include "partition.cpp"

#endif // MASTERGRIDSEARCH_PARTITION_H
