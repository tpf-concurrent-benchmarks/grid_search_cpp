#include "json_parsing.h"

template <std::size_t len> Params<len> json_to_params(const json &json_params)
{
    std::string id = json_params[0];
    std::array<int, len> start;
    std::array<int, len> end;
    std::array<int, len> step;
    for (int i = 1; i < len + 1; i++)
    {
        start[i - 1] = json_params[i][0];
        end[i - 1] = json_params[i][1];
        step[i - 1] = json_params[i][2];
    }
    return Params<len>(std::move(start), std::move(end), std::move(step), std::move(id));
}