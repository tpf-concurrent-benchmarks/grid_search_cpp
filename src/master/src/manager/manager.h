#ifndef MASTERGRIDSEARCH_MANAGER_H
#define MASTERGRIDSEARCH_MANAGER_H

#include "../interval/partition.h"
#include "../message_processor/message_processor.h"
#include "../protocol/protocol.h"
#include "nlohmann/json.hpp"
#include <cstddef>
#include <set>
#include <string>

using json = nlohmann::json;

//Manager is the main class of the master node, it is responsible for partitioning the dataset
//and sending the partitions to the workers, as well as receiving the results and saving them
//it also handles the syncronization of all this tasks.
class Manager
{

  public:
    Manager(size_t n_workers, Protocol *protocol, MessageProcessor *messageProcessor);
    void run(Partition partition, const std::string &aggregation);

  private:
    size_t nWorkers_;
    Protocol *protocol_;
    MessageProcessor *messageProcessor_;
    bool allWorkersHaveFinished();
};

#include "manager.cpp"

#endif // MASTERGRIDSEARCH_MANAGER_H
