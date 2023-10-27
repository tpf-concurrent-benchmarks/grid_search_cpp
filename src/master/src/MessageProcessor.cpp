#include "MessageProcessor.h"
#include <iostream>

std::string MessageProcessor::get_results()
{
    return std::string();
}

void MessageProcessor::process_message(std::string message)
{
    if (message == "end")
    {
        n_workers_--;
        if (n_workers_ == 0)
        {
            // TODO: use cond_var to notify main thread that all workers are done
        }
    }
    else
    {
        // Convert message to json and print it out
        json jsonMessage = json::parse(message);
        std::cout << jsonMessage.dump(4) << std::endl;
    }
}
