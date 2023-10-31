#ifndef GRIDSEARCHCPP_CONFIG_READER_H
#define GRIDSEARCHCPP_CONFIG_READER_H

#include <string>
#include <nlohmann/json.hpp>

std::string getBrokerAddress();
nlohmann::json getDataFromJson();

#include "config_reader.cpp"

#endif // GRIDSEARCHCPP_CONFIG_READER_H
