#include "config_reader.h"
#include "grid_search.h"
#include "json_parsing.h"
#include "params.h"
#include <amqpcpp.h>
#include <amqpcpp/libuv.h>
#include <amqpcpp/linux_tcp.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <uv.h>

using json = nlohmann::json;

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

    return 0;
}
