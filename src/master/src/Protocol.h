#ifndef MASTERGRIDSEARCH_PROTOCOL_H
#define MASTERGRIDSEARCH_PROTOCOL_H

#include "MessageProcessor.h"
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
    Protocol(AMQP::TcpChannel *pChannel);
    void send_data(std::string exchangeName, std::string routingKey, json data);
    void send_data(std::string exchangeName, std::string routingKey, std::string data);
    void install_consumer();
    string get_results();

  private:
    AMQP::TcpChannel *channel_;
    MessageProcessor messageProcessor_;
};

#endif // MASTERGRIDSEARCH_PROTOCOL_H
