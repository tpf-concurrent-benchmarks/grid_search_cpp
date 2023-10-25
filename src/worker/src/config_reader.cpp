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
    ifstream configFile = readConfigFile("../../../rabbitmq-config.json");
    json configData = configFileToJson(configFile);
    return createBrokerAddress(configData["user"], configData["password"], configData["address"], configData["port"]);
}
