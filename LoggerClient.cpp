#include <string>
#include <iostream>
#include <Windows.h>

#include <ZMQClient.hpp>

int main() {
  ZMQClient client = ZMQClient("tcp://localhost:5555");
  client.start([&]{
    zmq::message_t reply;
    client.send("Some infoi");
    client.receive(reply);
  });

  Sleep(3000);
  
  client.start([&]{
    zmq::message_t reply;
    client.send("Warningw");
    client.receive(reply);
  });

  Sleep(3000);

  client.start([&]{
    zmq::message_t reply;
    client.send("Errore");
    client.receive(reply);
  });

  return 0;
}
