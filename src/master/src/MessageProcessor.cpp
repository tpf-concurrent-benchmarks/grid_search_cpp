#include "MessageProcessor.h"
#include <iostream>

void MessageProcessor::process_message(std::string message)
{
    json jsonMessage = json::parse(message);
    std::cout << jsonMessage.dump(4) << std::endl;
}

void MessageProcessor::save_results()
{
    std::cout << "Results: saving results" << results_ << std::endl;
}
