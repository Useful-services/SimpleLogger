#include <iostream>
#include <ZMQServer.hpp>

int main() {
  
  ZMQServer server = ZMQServer("tcp://*:5555");
  
  const std::string data{"World"};
  server.start([&]{
    for(;;) {
      char buffer[1024];
      auto result = server.receive(buffer, sizeof(buffer));
      if (result > 0) {
        std::string request(buffer, result);
        std::cout << "Received " << request << std::endl;
      }
      server.send(data);
    }
  });
  
  return 0;
}