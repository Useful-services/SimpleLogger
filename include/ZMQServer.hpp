#pragma once

#include <functional>
#include <string>
#include <zmq.hpp>

class ZMQServer {
public:
  ZMQServer(const std::string& addr);

  zmq::socket_t* get_socket();

  zmq::recv_result_t receive(zmq::message_t& request, zmq::recv_flags flags = zmq::recv_flags::none);
  zmq::send_result_t send(const std::string& data, zmq::send_flags flags = zmq::send_flags::none);

  void start(const std::function<void()>& action);
private:
  zmq::context_t context;
  zmq::socket_t socket;
};