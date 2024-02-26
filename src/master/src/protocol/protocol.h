#ifndef MASTERGRIDSEARCH_PROTOCOL_H
#define MASTERGRIDSEARCH_PROTOCOL_H

#include "nlohmann/json.hpp"
#include "zmq.hpp"
#include <string>

using json = nlohmann::json;

//This class is intended to abstract the zeroMQ communication between the master and the workers
class Protocol
{
  public:
    Protocol(const std::string &pushPort, const std::string &pullPort);
    void send(const std::vector<Interval> &intervals, const std::string &aggregation);
    void send(const std::string &message);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};

#include "protocol.cpp"

#endif // MASTERGRIDSEARCH_PROTOCOL_H
