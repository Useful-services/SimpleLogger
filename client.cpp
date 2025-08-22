#include <string>
#include <iostream>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  const std::string data{"Hello"};
  client.start([&]{
    for (auto request_num = 0; request_num < 10; ++request_num) {
      std::cout << "Sending Hello " << request_num << "..." << std::endl;
      client.send(data);
      
      char buffer[1024];
      auto result = client.receive(buffer, sizeof(buffer));
      if (result > 0) {
        std::string reply(buffer, result);
        std::cout << "Received " << reply; 
        std::cout << " (" << request_num << ")";
        std::cout << std::endl;
      }
    }
  });

  return 0;
}
