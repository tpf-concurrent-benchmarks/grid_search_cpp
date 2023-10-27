#ifndef MASTERGRIDSEARCH_MESSAGEPROCESSOR_H
#define MASTERGRIDSEARCH_MESSAGEPROCESSOR_H

#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>

using json = nlohmann::json;

class MessageProcessor
{

  public:
    MessageProcessor(int n_workers);
    void process_message(std::string message);

    std::string get_results();

  private:
    int n_workers_;
    std::string results_;
};

#endif // MASTERGRIDSEARCH_MESSAGEPROCESSOR_H
