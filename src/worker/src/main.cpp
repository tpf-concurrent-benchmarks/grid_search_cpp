#include "../../shared/constants.h"
#include "config_reader/config_reader.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"

#include "grid_search/grid_search.h"
#include "grid_search/objective_fun.h"
#include "results_dto/avg_results_DTO.h"
// include params
#include "grid_search/params.h"

int main()
{
    std::string pushPort = getPushPort();
    std::string pullPort = getPullPort();
    std::string masterHost = getMasterHost();

    Protocol protocol(masterHost, pushPort, pullPort);
    std::string nodeId = getNodeId();
    MessageProcessor messageProcessor(nodeId);
    std::cout << "Worker " << nodeId << " ready, sending meessage to Manager" << std::endl;
    protocol.send(Constants::READY_MESSAGE);

    bool shouldStop = false;

    while (!shouldStop)
    {
        std::string message = protocol.receive();
        if (message == Constants::STOP_MESSAGE)
        {
            shouldStop = true;
            std::cout << "Worker " << nodeId << " received stop message, sending END message to Manager" << std::endl;
            protocol.send(Constants::END_WORK_MESSAGE);
        }
        else
        {
            json jsonMessage = json::parse(message);
            std::cout << "Worker " << nodeId << " received message: " << jsonMessage.dump() << std::endl;
            ResultsDTO *results = messageProcessor.processMessage(jsonMessage);
            protocol.send(results->toJson().dump());
            delete results;
        }
    }
    protocol.close();

    return 0;
}
