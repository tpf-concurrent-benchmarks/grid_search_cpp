#include "message_processor.h"
#include "../grid_search/grid_search.h"
#include "../grid_search/objective_fun.h"
#include "../results_dto/avg_results_DTO.h"
#include "../results_dto/max_results_DTO.h"
#include "../results_dto/min_results_DTO.h"
#include <StatsdClient.hpp>
#include <chrono>

MessageProcessor::MessageProcessor(std::string ID) : statClient{"localhost", 8125, ID} {
    //TODO: add this to config file
};

ResultsDTO *MessageProcessor::aggregate(GridSearch<3> &grid_search, std::string &aggregation)
{
    if (aggregation == "MAX")
    {
        auto *maxResultsDto = new MaxResultsDTO(grid_search.getResult(), grid_search.getInput());
        return maxResultsDto;
    }
    else if (aggregation == "MIN")
    {
        auto *minResultsDto = new MinResultsDTO(grid_search.getResult(), grid_search.getInput());
        return minResultsDto;
    }
    else
    {
        // TODO: implement AVG
        auto *avgResultsDto = new AvgResultsDTO(grid_search.getResult(), grid_search.getTotalInputs());
        return avgResultsDto;
    }
}


ResultsDTO *MessageProcessor::processMessage(json message)
{
    std::chrono::milliseconds start_time_ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );

    std::string aggregation = message["agg"];
    std::array<std::array<float, 3>, 3> parameters = message["data"];
    Params<3> params(std::move(parameters[0]), std::move(parameters[1]), std::move(parameters[2]));
    GridSearch<3> grid_search(std::move(params), aggregation);
    grid_search.search(griewankFun);

    ResultsDTO *resultsDto = aggregate(grid_search, aggregation);

    std::chrono::milliseconds end_time_ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::chrono::milliseconds completion_time = end_time_ms - start_time_ms;
    statClient.timing("work_time", completion_time.count(), 1);
    statClient.increment("results_produced");
    return resultsDto;
}
