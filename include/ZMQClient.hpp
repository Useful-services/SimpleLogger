#pragma once

#include <functional>
#include <string>
#include <zmq.h>

class ZMQClient {
public:
  ZMQClient(const std::string& addr);
  ~ZMQClient();
  
  void* get_socket();

  int receive(void* buffer, size_t size, int flags = 0);
  int send(const std::string& data, int flags = 0);

  void start(const std::function<void()>& action);
private:
  void* context;
  void* socket;
};