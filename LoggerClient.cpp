#include <string>
#include <iostream>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  client.start([&]{
    char buffer[MY_BUFFER_SIZE];
    using ns = MQData::MessageInfo;
    client.send_data({
      {
        ns::msg_type::INFO,
        ns::action_type::NONE,
        0
      },
      "some text"
    }, sizeof(buffer));
    client.receive(buffer, sizeof(buffer));
    
    client.send_data({
      {
        ns::msg_type::WARN,
        ns::action_type::NONE,
        0
      },
      "Be cautious!"
    }, sizeof(buffer));
    client.receive(buffer, sizeof(buffer));
  });

  return 0;
}
