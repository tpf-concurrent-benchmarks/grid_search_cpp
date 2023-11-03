#ifndef MASTERGRIDSEARCH_PROTOCOL_H
#define MASTERGRIDSEARCH_PROTOCOL_H

#include "message_processor.h"
#include "zmq.hpp"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Protocol
{
  public:
    Protocol(MessageProcessor messageProcessor, size_t n_workers);
    void send(const std::vector<Interval> &intervals, const std::string &aggregation);
    void send(const string &message);
    void installConsumer();
    void clean();

    std::string receive();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;
    MessageProcessor messageProcessor_;
    size_t n_workers_;

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};

#include "protocol.cpp"

#endif // MASTERGRIDSEARCH_PROTOCOL_H
