#ifndef WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
#define WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H

#include "nlohmann/json.hpp"
#include <cstdint>
#include <string>
#include "ResultsDTO.h"

using json = nlohmann::json;

class MessageProcessor
{

  public:
    MessageProcessor();
    ResultsDTO processMessage(json message);
};

#include "message_processor.cpp"

#endif // WORKERGRIDSEARCH_MESSAGE_PROCESSOR_H
