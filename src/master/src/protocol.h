#ifndef MASTERGRIDSEARCH_PROTOCOL_H
#define MASTERGRIDSEARCH_PROTOCOL_H

#include "message_processor.h"
#include <amqpcpp.h>
#include <amqpcpp/libuv.h>
#include <amqpcpp/linux_tcp.h>
#include <nlohmann/json.hpp>
#include <string>
#include <uv.h>

using json = nlohmann::json;

class Protocol
{
  public:
    Protocol(const std::string &brokerAddress, size_t n_workers);
    void sendData(const std::string &exchangeName, const std::string &routingKey, std::string data);
    void sendData(const std::string &exchangeName, const std::string &routingKey, std::vector<Interval> data);
    void installConsumer();
    void clean();

  private:
    AMQP::TcpChannel *channel_;
    AMQP::LibUvHandler *handler_;
    AMQP::TcpConnection *connection_;
    uv_loop_t *loop_;
    MessageProcessor messageProcessor_ = MessageProcessor();
    size_t n_workers_;
};

#include "protocol.cpp"

#endif // MASTERGRIDSEARCH_PROTOCOL_H
