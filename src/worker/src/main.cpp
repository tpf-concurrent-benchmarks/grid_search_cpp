#include "config_reader.h"
#include "params.h"
#include "protocol.h"
#include "grid_search.h"
#include "objective_fun.h"

int main()
{
    std::string brokerAddress = getBrokerAddress();

    Protocol protocol(brokerAddress);
    protocol.installConsumer();

    Params<3> params(std::array<float, 3>{0, 0, 0}, std::array<float, 3>{10, 10, 10}, std::array<float, 3>{0.1, 1, 1}, "id");
    GridSearch<3> grid_search(std::move(params));
    grid_search.search(objectiveFun);
    std::cout << "max: " << grid_search.get_max() << std::endl;
    std::cout << "min: " << grid_search.get_min() << std::endl;
    std::cout << "total: " << grid_search.get_total() << std::endl;
    std::cout << "total_inputs: " << grid_search.get_total_inputs() << std::endl;
    std::cout << "max_input: " << grid_search.get_max_input()[0] << " " << grid_search.get_max_input()[1] << " " << grid_search.get_max_input()[2] << std::endl;
    std::cout << "min_input: " << grid_search.get_min_input()[0] << " " << grid_search.get_min_input()[1] << " " << grid_search.get_min_input()[2] << std::endl;

    return 0;
}
