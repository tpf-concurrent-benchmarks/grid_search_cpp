#include "config_reader.h"
#include "protocol.h"
#include "grid_search.h"

int main()
{
    std::string brokerAddress = getBrokerAddress();

    Protocol protocol(brokerAddress);
    protocol.installConsumer();

    return 0;
}
