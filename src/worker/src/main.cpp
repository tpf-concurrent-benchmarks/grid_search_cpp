#include "config_reader.h"
#include "protocol.h"

int main()
{
    std::string brokerAddress = getBrokerAddress();

    Protocol protocol(brokerAddress);
    protocol.installConsumer();

    return 0;
}
