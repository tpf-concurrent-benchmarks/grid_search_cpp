#ifndef GRIDSEARCHCPP_CONFIG_READER_H
#define GRIDSEARCHCPP_CONFIG_READER_H

#include "nlohmann/json.hpp"
#include <string>

nlohmann::json getDataFromJson(const char *dataPath);
std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getPushPort();
std::string getPullPort();
size_t getNWorkers();

#include "config_reader.cpp"

#endif // GRIDSEARCHCPP_CONFIG_READER_H
