#include "config_reader.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

string createBrokerAddress(const string &user, const string &password, const string &address, const int port)
{
    return "amqp://" + user + ":" + password + "@" + address + ":" + to_string(port) + "/";
}

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

string getBrokerAddress()
{
    const char *rabbitPath = "./rabbitmq-config.json";
    if (getenv("ENV") != nullptr && string(getenv("ENV")) == "LOCAL")
    {
        rabbitPath = "../../../rabbitmq-config-local.json";
    }
    ifstream configFile = readConfigFile(rabbitPath);
    json configData = configFileToJson(configFile);
    return createBrokerAddress(configData["user"], configData["password"], configData["address"], configData["port"]);
}

json getDataFromJson()
{
    const char *dataPath = "../resources/example-min.json";
    ifstream dataFile = readConfigFile(dataPath);
    json data = configFileToJson(dataFile);
    return data;
}
