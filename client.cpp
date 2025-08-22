#include <string>
#include <iostream>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  const std::string data{"Hello"};
  client.start([&]{
    for (auto request_num = 0; request_num < 10; ++request_num) {
      std::cout << "Sending Hello " << request_num << "..." << std::endl;
      client.send(data, zmq::send_flags::none);
      
      zmq::message_t reply{};
      client.receive(reply, zmq::recv_flags::none);  
      std::cout << "Received " << reply.to_string(); 
      std::cout << " (" << request_num << ")";
      std::cout << std::endl;
    }
  });

  return 0;
}
