#include "manager.h"

Manager::Manager(size_t n_workers, Protocol *protocol, MessageProcessor *messageProcessor)
    : nWorkers_(n_workers), protocol_(protocol), messageProcessor_(messageProcessor)
{
}

void Manager::run(Partition partition, const std::string &aggregation)
{

    std::set<string> workers;

    while (workers.size() != nWorkers_)
    {
        protocol_->send(Constants::READY_MESSAGE);
        std::string workerId = protocol_->receive();
        const pair<set<string>::iterator, bool> &inserted = workers.insert(workerId);
        if (inserted.second)
        {
            std::cout << "Worker ready: " << workers.size() << " of " << nWorkers_ << std::endl;
        }
    }

    for (int i = 0; i < nWorkers_; i++)
    {
        std::cout << "Signaling workers, starting work: " << i + 1 << " of " << nWorkers_ << std::endl;
        protocol_->send(Constants::START_WORK_MESSAGE);
    }

    while (partition.available())
    {
        auto partition_data = partition.next();
        std::cout << "Sending partition " << std::endl;
        protocol_->send(partition_data, aggregation);
    }

    for (size_t i = 0; i < nWorkers_; i++)
    {
        std::cout << "Sending stop message to workers: " << i + 1 << " of " << nWorkers_ << std::endl;
        protocol_->send(Constants::STOP_MESSAGE);
    }

    while (!allWorkersHaveFinished())
    {
        std::string message = protocol_->receive();
        if (message == Constants::END_WORK_MESSAGE)
        {
            nWorkers_--;
            std::cout << "Worker finished: " << nWorkers_ << " left" << std::endl;
        }
        else
        {
            messageProcessor_->processMessage(json::parse(message));
        }
    }

    messageProcessor_->saveResults();
}

bool Manager::allWorkersHaveFinished()
{
    return nWorkers_ == 0;
}
