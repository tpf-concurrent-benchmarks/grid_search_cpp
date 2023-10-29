#include "message_processor.h"
#include <iostream>

MessageProcessor::MessageProcessor() = default;


void MessageProcessor::processMessage(std::string message)
{
    // TODO: use params to unpack parameters then do grid search
    // also change the return type of the method so the protocol can format and send the response
    std::cout << message << std::endl;
}


