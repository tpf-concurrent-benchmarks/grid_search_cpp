#include "message_processor.h"
#include <iostream>

MessageProcessor::MessageProcessor() = default;

void MessageProcessor::processMessage(std::string message)
{
    json jsonMessage = json::parse(message);
    std::cout << jsonMessage.dump(4) << std::endl;
}

void MessageProcessor::saveResults()
{
    std::cout << "Results: saving results" << results_ << std::endl;
}
