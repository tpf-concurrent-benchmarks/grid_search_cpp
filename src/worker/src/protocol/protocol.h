#ifndef WORKERGRIDSEARCH_PROTOCOL_H
#define WORKERGRIDSEARCH_PROTOCOL_H

#include "zmq.hpp"
#include <string>

class Protocol
{
  public:
    Protocol();
    void send(const std::string &message);
    std::string receive();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;
};

#include "protocol.cpp"

#endif // WORKERGRIDSEARCH_PROTOCOL_H
