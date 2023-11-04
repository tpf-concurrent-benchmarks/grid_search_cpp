#ifndef WORKERGRIDSEARCH_PROTOCOL_H
#define WORKERGRIDSEARCH_PROTOCOL_H

#include "zmq.hpp"
#include <string>

class Protocol
{
  public:
    Protocol(const std::string &host, const std::string &pushPort, const std::string &pullPort);
    void send(const std::string &message);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;
};

#include "protocol.cpp"

#endif // WORKERGRIDSEARCH_PROTOCOL_H
