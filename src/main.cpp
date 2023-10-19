#include <iostream>
#include <nlohmann/json.hpp>
#include <amqpcpp.h>

int main() {
    using json = nlohmann::json;
    json example = {
            {"happy", true},
            {"pi", 3.141},
    };
    std::cout << example << std::endl;
    return 0;
}
