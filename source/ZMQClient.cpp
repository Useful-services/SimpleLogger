#include <ZMQClient.hpp>
#include <cstring>

ZMQClient::ZMQClient(const std::string& addr) {
  context = zmq_ctx_new();
  socket = zmq_socket(context, ZMQ_REQ);
  zmq_connect(socket, addr.c_str());
}

ZMQClient::~ZMQClient() {
  if (socket) zmq_close(socket);
  if (context) zmq_ctx_destroy(context);
}

void* ZMQClient::get_socket() {
  return socket;
}

int ZMQClient::receive(void* buffer, size_t size, int flags) {
  return zmq_recv(socket, buffer, size, flags);
}

int ZMQClient::send(const std::string& data, int flags) {
  return zmq_send(socket, data.c_str(), data.length(), flags);
}

void ZMQClient::start(const std::function<void()>& action) {
  action();
}