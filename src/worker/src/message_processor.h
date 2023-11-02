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
    void processMessage(std::array<std::array<float, 3>, 3> message);
};

#include "message_processor.cpp"

#endif // MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H
