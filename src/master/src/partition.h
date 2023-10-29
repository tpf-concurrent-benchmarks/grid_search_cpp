#ifndef MASTERGRIDSEARCH_PARTITION_H
#define MASTERGRIDSEARCH_PARTITION_H

#include <array>
#include <string>

class Partition
{
  public:
    Partition(size_t n_partitions);
    bool available() const;
    std::array<int, 3> next();

  private:
    size_t n_partitions_;
    size_t current_partition_ = 0;
    // Example partitions
    std::array<std::array<int, 3>, 3> partitions = {{{0, 10, 1}, {0, 10, 1}, {0, 10, 1}}};
};

#endif // MASTERGRIDSEARCH_PARTITION_H
