#ifndef MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H
#define MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H

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

#endif // MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H
