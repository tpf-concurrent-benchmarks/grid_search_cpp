#include "manager.h"

Manager::Manager(size_t n_workers, Protocol *protocol, MessageProcessor *messageProcessor)
    : nWorkers_(n_workers), protocol_(protocol), messageProcessor_(messageProcessor)
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
            std::cout << "Worker ready: " << workersReady_ << "of " << nWorkers_ << std::endl;
        }
    }

    while (partition.available())
    {
        auto partition_data = partition.next();
        std::cout << "Sending partition " << std::endl;
        protocol_->send(partition_data, aggregation);
    }

    for (size_t i = 0; i < nWorkers_; i++)
    {
        std::cout << "Sending stop message to workers: " << i + 1 << "of " << nWorkers_ << std::endl;
        protocol_->send(Constants::STOP_MESSAGE);
    }

    while (!allWorkersHaveFinished())
    {
        std::string message = protocol_->receive();
        if (message == Constants::END_WORK_MESSAGE)
        {
            nWorkers_--;
            std::cout << "Worker finished: " << nWorkers_ << "left" << std::endl;
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
