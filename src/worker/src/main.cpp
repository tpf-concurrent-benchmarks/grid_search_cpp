#include "../../shared/constants.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"
#include <constants.h>

int main()
{
    Protocol protocol("localhost", "5558", "5557");
    MessageProcessor messageProcessor;
    protocol.send(Constants::READY_MESSAGE, std::string());

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            protocol.send(Constants::END_WORK_MESSAGE, std::string());
        }
        else
        {
            json jsonMessage = json::parse(message);
            ResultsDTO *results = messageProcessor.processMessage(jsonMessage);
            protocol.send(results->toJson().dump(), std::string());
            delete results;
        }
    }

    return 0;
}
