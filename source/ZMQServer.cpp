#include <ZMQServer.hpp>

ZMQServer::ZMQServer(const std::string& addr) {
  context = zmq::context_t(1);
  socket = zmq::socket_t{context, zmq::socket_type::rep};
  socket.bind(addr);
}

zmq::socket_t* ZMQServer::get_socket() {
  return &socket;
}

zmq::recv_result_t ZMQServer::receive(zmq::message_t& request, zmq::recv_flags flags) {
  return socket.recv(request, flags);
}

zmq::send_result_t ZMQServer::send(const std::string& data, zmq::send_flags flags) {
  return socket.send(zmq::buffer(data), flags);
}

void ZMQServer::start(const std::function<void()>& action) {
  action();
}