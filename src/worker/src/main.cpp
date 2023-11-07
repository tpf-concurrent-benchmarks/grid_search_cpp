#include "../../shared/constants.h"
#include "message_processor/message_processor.h"
#include "protocol/protocol.h"
#include <constants.h>
#include <cstdlib>

#include "grid_search/grid_search.h"
#include "grid_search/objective_fun.h"
#include "results_dto/avg_results_DTO.h"
//include params
#include "grid_search/params.h"

int main()
{
    // TODO: These ports should be from the docker compose --> env variable.
    // Also the host should be changed accordingly
    // Protocol protocol("localhost", "5558", "5557");
    // const char *ID = std::getenv("NODE_ID");
    // if (ID == nullptr)
    // {
    //     ID = "0";
    // }
    // MessageProcessor messageProcessor(ID);
    // protocol.send(Constants::READY_MESSAGE);

    // bool shouldStop = false;

    // while (!shouldStop)
    // {
    //     std::string message = protocol.receive();
    //     if (message == Constants::STOP_MESSAGE)
    //     {
    //         shouldStop = true;
    //         protocol.send(Constants::END_WORK_MESSAGE);
    //     }
    //     else
    //     {
    //         json jsonMessage = json::parse(message);
    //         ResultsDTO *results = messageProcessor.processMessage(jsonMessage);
    //         protocol.send(results->toJson().dump());
    //         delete results;
    //     }
    // }
    // protocol.close();

    Params<3> params(std::array<float, 3>{0, 0, 0}, std::array<float, 3>{1, 10, 10}, std::array<float, 3>{1, 1, 1});
    GridSearch<3> grid_search(std::move(params), "MIN");
    grid_search.search(griewankFun);
    std::cout << grid_search.getResult() << std::endl;
    

    return 0;
}
