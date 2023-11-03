#ifndef JSON_PARSING_H
#define JSON_PARSING_H

#include "interval.h"
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

std::vector<Interval> jsonToIntervals(const json &json_params);

#include "json_parsing.cpp"

#endif // JSON_PARSING_H
