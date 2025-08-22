#include <iostream>
#include <ZMQServer.hpp>

int main() {
  
  ZMQServer server = ZMQServer("tcp://*:5555");
  
  const std::string data{"World"};
  server.start([&]{
    for(;;) {
      zmq::message_t request;
      auto result = server.receive(request);
      std::cout << "Received " << request.to_string() << std::endl;
      server.send(data);
    }
  });
  
  return 0;
}