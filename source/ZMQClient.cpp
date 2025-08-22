#include <ZMQClient.hpp>

ZMQClient::ZMQClient(const std::string& addr) {
  context = zmq::context_t(1);
  socket = zmq::socket_t{context, zmq::socket_type::req};
  socket.connect(addr);
}

zmq::socket_t* ZMQClient::get_socket() {
  return &socket;
}

zmq::recv_result_t ZMQClient::receive(zmq::message_t& request, zmq::recv_flags flags) {
  return socket.recv(request, flags);
}

zmq::send_result_t ZMQClient::send(const std::string& data, zmq::send_flags flags) {
  return socket.send(zmq::buffer(data), flags);
}

void ZMQClient::start(const std::function<void()>& action) {
  action();
}