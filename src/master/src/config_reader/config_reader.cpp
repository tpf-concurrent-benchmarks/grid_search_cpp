#include "config_reader.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

ifstream readFile(string path)
{
    ifstream file(path);
    if (!file)
    {
        cerr << "Error: Could not open the file: " << path << endl;
        exit(1);
    }
    return file;
}

json configFileToJson(ifstream &configFile)
{
    json configData;
    configFile >> configData;
    return configData;
}

json getDataFromJson(const char *dataPath)
{
    ifstream dataFile = readFile(dataPath);
    json data = configFileToJson(dataFile);
    return data;
}

size_t getNWorkers()
{
    size_t nWorkers = 1;
    char *nWorkersFromEnv = getenv("N_WORKERS");
    if (nWorkersFromEnv != nullptr)
    {
        nWorkers = atoi(nWorkersFromEnv);
    }
    return nWorkers;
}

std::string getPullPort()
{
    const char *pullPort = "5558";
    char *pullPortFromEnv = getenv("PULL_PORT");
    if (pullPortFromEnv != nullptr)
    {

        pullPort = pullPortFromEnv;
    }
    return pullPort;
}

std::string getPushPort()
{
    const char *pushPort = "5557";
    char *pushPortFromEnv = getenv("PUSH_PORT");
    if (pushPortFromEnv != nullptr)
    {

        pushPort = pushPortFromEnv;
    }
    return pushPort;
}

uint16_t getGraphitePort()
{
    return 8125;
}

std::string getGraphiteHost()
{
    const char *graphiteHost = "graphite";
    if (getenv("ENV") != nullptr && string(getenv("ENV")) == "LOCAL")
    {
        graphiteHost = "localhost";
    }
    return graphiteHost;
}

std::string getMasterHost()
{
    const char *host = "manager";
    if (getenv("ENV") != nullptr && string(getenv("ENV")) == "LOCAL")
    {
        host = "localhost";
    }
    return host;
}
