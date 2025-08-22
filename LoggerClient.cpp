#include <string>
#include <iostream>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  client.start([&]{
    char buffer[1024];
    client.send("Some infoi");
    client.receive(buffer, sizeof(buffer));
  });
  
  client.start([&]{
    char buffer[1024];
    client.send("Warningw");
    client.receive(buffer, sizeof(buffer));
  });

  client.start([&]{
    char buffer[1024];
    client.send("Errore");
    client.receive(buffer, sizeof(buffer));
  });

  return 0;
}
