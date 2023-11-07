#include "../../shared/constants.h"
#include "config_reader/config_reader.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"

int main()
{
    // TODO: These ports should be from the docker compose --> env variable.
    // Also the host should be changed accordingly
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();
    std::string masterHost = getMasterHost();

    Protocol protocol(masterHost, pushPort, pullPort);
    std::string nodeId = getNodeId();
    MessageProcessor messageProcessor(nodeId);
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
            ResultsDTO *results = messageProcessor.processMessage(jsonMessage);
            protocol.send(results->toJson().dump());
            delete results;
        }
    }
    protocol.close();

    return 0;
}
