#include "message_processor.h"
#include "protocol.h"

int main()
{
    Protocol protocol;
    MessageProcessor messageProcessor_;
    protocol.send(Constants::READY_MESSAGE);

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            protocol.send(Constants::END_WORK_MESSAGE);
        }
        else
        {
            json jsonMessage = json::parse(message);
            ResultsDTO *results = messageProcessor_.processMessage(jsonMessage);
            protocol.send(results->toJson().dump());
            delete results;
        }
    }

    return 0;
}
