#ifndef MASTERGRIDSEARCH_MANAGER_H
#define MASTERGRIDSEARCH_MANAGER_H

#include "../interval/partition.h"
#include "../message_processor/message_processor.h"
#include "../protocol/protocol.h"
#include "nlohmann/json.hpp"
#include <cstddef>
#include <string>

using json = nlohmann::json;

class Manager
{

  public:
    Manager(size_t nWorkers, Protocol *protocol, MessageProcessor *messageProcessor);
    void run(Partition partition, const std::string &aggregation);

  private:
    size_t nWorkers_;
    size_t workersReady_ = 0;
    Protocol *protocol_;
    MessageProcessor *messageProcessor_;
    bool allWorkersReady();
    bool allWorkersHaveFinished();
};

#include "manager.cpp"

#endif // MASTERGRIDSEARCH_MANAGER_H
