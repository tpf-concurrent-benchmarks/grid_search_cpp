#include "config_reader.h"

using namespace std;

std::string getPullPort()
{
    const char *pullPort = "5557";
    char *pullPortFromEnv = getenv("PULL_PORT");
    if (pullPortFromEnv != nullptr)
    {

        pullPort = pullPortFromEnv;
    }
    return pullPort;
}

std::string getPushPort()
{
    const char *pushPort = "5558";
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

std::string getNodeId()
{
    const char *nodeId = "0";
    char *nodeIdFromEnv = getenv("NODE_ID");
    if (nodeIdFromEnv != nullptr)
    {
        nodeId = nodeIdFromEnv;
    }
    return nodeId;
}
