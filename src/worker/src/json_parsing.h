#ifndef JSON_PARSING_H
#define JSON_PARSING_H

#include "params.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <std::size_t len> Params<len> json_to_params(const json &json_params);

#include "json_parsing.cpp"

#endif // JSON_PARSING_H
