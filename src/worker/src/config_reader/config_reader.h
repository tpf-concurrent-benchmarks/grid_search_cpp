#ifndef WORKERGRIDSEARCHCPP_CONFIG_READER_H
#define WORKERGRIDSEARCHCPP_CONFIG_READER_H

#include <string>

std::string getGraphiteHost();
uint16_t getGraphitePort();
std::string getPushPort();
std::string getPullPort();
std::string getMasterHost();

#include "config_reader.cpp"

#endif // WORKERGRIDSEARCHCPP_CONFIG_READER_H
