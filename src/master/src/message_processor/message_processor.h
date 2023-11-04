#ifndef MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H
#define MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H

#include "nlohmann/json.hpp"
#include <cstdint>
#include <constants.h>
#include <string>

using json = nlohmann::json;

class MessageProcessor
{

  public:
    explicit MessageProcessor(std::string aggregation);
    void processMessage(const json &message);
    void saveResults();

  private:
    float value_{};
    std::array<float, 3> parameters_{};
    std::string aggregation_;
};

#include "message_processor.cpp"

#endif // MASTERGRIDSEARCH_MESSAGE_PROCESSOR_H
