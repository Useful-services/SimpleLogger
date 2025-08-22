#pragma once

#include <functional>
#include <string>
#include <zmq.h>

class ZMQServer {
public:
  ZMQServer(const std::string& addr);
  ~ZMQServer();

  void* get_socket();

  int receive(void* buffer, size_t size, int flags = 0);
  int send(const std::string& data, int flags = 0);

  void start(const std::function<void()>& action);
private:
  void* context;
  void* socket;
};