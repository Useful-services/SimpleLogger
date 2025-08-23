#include <ZMQServer.hpp>
#include <cstring>

ZMQServer::ZMQServer(const std::string& addr) {
  context = zmq_ctx_new();
  socket = zmq_socket(context, ZMQ_REP);
  zmq_bind(socket, addr.c_str());
}

ZMQServer::~ZMQServer() {
  if (socket) zmq_close(socket);
  if (context) zmq_ctx_destroy(context);
}

void* ZMQServer::get_socket() {
  return socket;
}

int ZMQServer::receive(void* buffer, size_t size, int flags) {
  return zmq_recv(socket, buffer, size, flags);
}

int ZMQServer::send_array(const char* data, size_t size, int flags) {
  return zmq_send(socket, data, size, flags);
}

int ZMQServer::send_data(const MQData& data, int flags) {
  char raw_data[sizeof(MQData)];
  data.to_buffer(raw_data);
  return send_array(raw_data, sizeof(MQData), flags);
}

int ZMQServer::send_string(const std::string& data, int flags) {
  return zmq_send(socket, data.c_str(), data.length(), flags);
}

void ZMQServer::start(const std::function<void()>& action) {
  action();
}