#include "message_processor.h"
#include <iostream>

MessageProcessor::MessageProcessor() = default;

void MessageProcessor::processMessage(std::array<std::array<int, 3>, 3> message)
{
    // TODO: use params to unpack parameters then do grid search
    // also change the return type of the method so the protocol can format and send the response
    for (auto &row : message)
    {
        for (auto &col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}
