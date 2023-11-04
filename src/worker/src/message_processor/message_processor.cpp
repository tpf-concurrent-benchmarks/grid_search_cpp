#include "message_processor.h"
#include "../grid_search/grid_search.h"
#include "../grid_search/objective_fun.h"
#include "../results_dto/avg_results_DTO.h"
#include "../results_dto/max_results_DTO.h"
#include "../results_dto/min_results_DTO.h"

MessageProcessor::MessageProcessor() = default;

ResultsDTO *MessageProcessor::processMessage(json message)
{
    std::string aggregation = message["agg"];
    std::array<std::array<float, 3>, 3> parameters = message["data"];
    Params<3> params(std::move(parameters[0]), std::move(parameters[1]), std::move(parameters[2]));
    GridSearch<3> grid_search(std::move(params));
    grid_search.search(griewankFun);

    if (aggregation == "MAX")
    {
        auto *maxResultsDto = new MaxResultsDTO(grid_search.getMax(), grid_search.getMaxInput());
        return maxResultsDto;
    }
    else if (aggregation == "MIN")
    {
        auto *minResultsDto = new MinResultsDTO(grid_search.getMin(), grid_search.getMinInput());
        return minResultsDto;
    }
    else
    {
        // TODO: implement AVG
        auto *avgResultsDto = new AvgResultsDTO(grid_search.getTotal(), grid_search.getTotalInputs());
        return avgResultsDto;
    }
}
