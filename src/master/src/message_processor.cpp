#include "message_processor.h"
#include <iostream>

MessageProcessor::MessageProcessor(std::string aggregation) : aggregation_(std::move(aggregation)){};

void MessageProcessor::processMessage(const json &message)
{
    float value = message["value"];
    std::array<float, 3> parameters = message["parameters"];

    if (aggregation_ == "MAX")
    {
        if (value > value_)
        {
            value_ = value;
            parameters_ = parameters;
        }
    }
    else if (aggregation_ == "MIN")
    {
        if (value < value_)
        {
            value_ = value;
            parameters_ = parameters;
        }
    }
    else
    {
        // TODO: add avg
    }
}

void MessageProcessor::saveResults()
{
    std::cout << "Saving results" << std::endl;
    json results = {{"value", value_}, {"parameters", parameters_}, {"agg", aggregation_}};
    std::ofstream file;
    file.open(RESULTS_PATH);
    file << std::setw(2) << results;
    file.close();
}
