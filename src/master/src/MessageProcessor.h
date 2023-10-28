#ifndef MASTERGRIDSEARCH_MESSAGEPROCESSOR_H
#define MASTERGRIDSEARCH_MESSAGEPROCESSOR_H

#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>

using json = nlohmann::json;

class MessageProcessor
{

  public:
    MessageProcessor();
    void process_message(std::string message);
    void save_results();

  private:
    std::string results_;
};

#endif // MASTERGRIDSEARCH_MESSAGEPROCESSOR_H
