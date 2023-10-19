#include <iostream>
#include <nlohmann/json.hpp>
#include <amqpcpp.h>
#include "params.h"
# include "grid_search.h"

int main() {
    using json = nlohmann::json;
    json example = {
            {"happy", true},
            {"pi", 3.141},
    };
    std::cout << example << std::endl;

    std::array<int, 2> start = {0, 0};
    std::array<int, 2> end = {5, 4};
    std::array<int, 2> step = {1, 1};
    Params<2> params(start, end, step);
    std::cout << params.get_total_iterations() << std::endl;
    for (int i = 0; i < params.get_total_iterations(); i++) {
        std::array<int, 2> current = params.get_current();
        std::cout << current[0] << " " << current[1] << std::endl;
        params.next();
    }
    // calculates every combination of the two parameters and prints it
    return 0;
}
