#include "protocol.h"

Protocol::Protocol(const std::string &pushPort, const std::string &pullPort)
{
    context_ = zmq::context_t(1);
    sender_ = zmq::socket_t(context_, ZMQ_PUSH);
    receiver_ = zmq::socket_t(context_, ZMQ_PULL);
    sender_.bind("tcp://*:" + pushPort);
    receiver_.bind("tcp://*:" + pullPort);
}

void Protocol::send(const std::vector<Interval> &intervals, const string &aggregation)
{
    json intervalList = json::array();
    for (auto interval : intervals)
    {
        intervalList.push_back(interval.get_interval());
    }
    json message = {
        {"data", intervalList},
        {"agg", aggregation},
    };
    zmq::message_t zmqMessage = createZmqMessage(message);
    const zmq::send_result_t &anOptional = sender_.send(zmqMessage, zmq::send_flags::none);
    if (!anOptional.has_value())
    {
        std::cout << "Error sending message" << std::endl;
    }
}

void Protocol::send(const string &message)
{
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.c_str(), message.size());

    const zmq::send_result_t &anOptional = sender_.send(zmqMessage, zmq::send_flags::none);
    if (!anOptional.has_value())
    {
        std::cout << "Error sending message" << std::endl;
    }
}

zmq::message_t Protocol::createZmqMessage(const json &message) const
{
    string messageAsString = message.dump();
    size_t messageSize = messageAsString.size();

    zmq::message_t zmqMessage(messageSize);
    memcpy(zmqMessage.data(), messageAsString.c_str(), messageSize);
    return zmqMessage;
}

string Protocol::receive()
{
    zmq::message_t message;
    const zmq::recv_result_t &anOptional = receiver_.recv(message);
    if (!anOptional.has_value())
    {
        return "Error message";
    }
    return std::string(static_cast<char *>(message.data()), message.size());
}
