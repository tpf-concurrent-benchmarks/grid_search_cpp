#include "config_reader.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

ifstream readConfigFile(string path)
{
    ifstream configFile(path);
    if (!configFile)
    {
        cerr << "Error: Could not open the configuration file." << endl;
        exit(1);
    }
    return configFile;
}

json configFileToJson(ifstream &configFile)
{
    json configData;
    configFile >> configData;
    return configData;
}

json getDataFromJson(const char *dataPath)
{
    ifstream dataFile = readConfigFile(dataPath);
    json data = configFileToJson(dataFile);
    return data;
}
