#include "interval.h"
#include <nlohmann/json.hpp>
#include <vector>

std::vector<Interval> jsonToIntervals(const nlohmann::json &json_params)
{
    std::vector<Interval> intervals;
    for (int i = 0; i < json_params.size(); i++)
    {
        intervals.push_back(Interval(json_params[i][0], json_params[i][1], json_params[i][2]));
        if (json_params[i].size() > 3)
        {
            intervals[i].setPrecision(json_params[i][3]);
        }
    }
    return intervals;
}
