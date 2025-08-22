#include <string>
#include <iostream>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  client.start([&]{
    client.send("Some infoi");
  });

  client.start([&]{
    client.send("Warningw");
  });

  client.start([&]{
    client.send("Errore");
  });

  return 0;
}
