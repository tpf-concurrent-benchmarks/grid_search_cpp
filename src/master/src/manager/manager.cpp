#include "manager.h"
#include "../config_reader/config_reader.h"
#include "../interval/partition.h"

Manager::Manager(size_t nWorkers, Protocol *protocol, MessageProcessor *messageProcessor)
    : nWorkers_(nWorkers), protocol_(protocol), messageProcessor_(messageProcessor)
{
}

void Manager::run(Partition partition, const std::string &aggregation)
{
    while (!allWorkersReady())
    {
        std::string message = protocol_->receive();
        if (message == Constants::READY_MESSAGE)
        {
            workersReady_++;
        }
    }

    while (partition.available())
    {
        auto partition_data = partition.next();
        protocol_->send(partition_data, aggregation);
    }

    for (size_t i = 0; i < nWorkers_; i++)
    {
        protocol_->send(Constants::STOP_MESSAGE);
    }

    while (!allWorkersHaveFinished())
    {
        std::string message = protocol_->receive();
        if (message == Constants::END_WORK_MESSAGE)
        {
            nWorkers_--;
        }
        else
        {
            messageProcessor_->processMessage(json::parse(message));
        }
    }

    messageProcessor_->saveResults();
}

bool Manager::allWorkersReady()
{
    return workersReady_ == nWorkers_;
}

bool Manager::allWorkersHaveFinished()
{
    return nWorkers_ == 0;
}
