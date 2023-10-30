#include "config_reader.h"
#include "params.h"
#include "protocol.h"

int max_sum(std::array<int, 3> &current, int res)
{
    int sum = current[0] + current[1] + current[2];
    if (sum > res)
    {
        return sum;
    }
    else
    {
        return res;
    }
}

int main()
{
    std::string brokerAddress = getBrokerAddress();

    Protocol protocol(brokerAddress);
    protocol.installConsumer();

    return 0;
}
