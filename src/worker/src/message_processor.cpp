#include "message_processor.h"
#include "grid_search.h"
#include "objective_fun.h"
#include "params.h"

MessageProcessor::MessageProcessor() = default;

ResultsDTO MessageProcessor::processMessage(json message)
{
    std::string aggregation = message["agg"];
    std::array<std::array<float, 3>, 3> parameters = message["data"];
    Params<3> params(std::move(parameters[0]), std::move(parameters[1]), std::move(parameters[2]), "id");
    GridSearch<3> grid_search(std::move(params));
    grid_search.search(objectiveFun);

    if (aggregation == "MAX")
    {
        ResultsDTO resultsDto(grid_search.getMax(), grid_search.getMaxInput());
        return resultsDto;
    }
    else if (aggregation == "MIN")
    {
        ResultsDTO resultsDto(grid_search.getMin(), grid_search.getMinInput());
        return resultsDto;
    }
    else
    {
        // TODO: implement AVG
        return ResultsDTO(111, {111, 0, 0});
    }
}
