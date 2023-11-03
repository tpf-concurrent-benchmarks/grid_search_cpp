#include "config_reader.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

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
