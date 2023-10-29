#include "partition.h"

Partition::Partition(size_t n_partitions) : n_partitions_(n_partitions){};

bool Partition::available() const
{
    return current_partition_ < n_partitions_;
}

std::array<std::array<int, 3>, 3> Partition::next()
{
    current_partition_++;
    return partitions;
}
