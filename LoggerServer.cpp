#include <Logger.hpp>
#include <ZMQServer.hpp>

int main() {
  ZMQServer server = ZMQServer("tcp://*:5555");
  Logger logger;

  server.start([&]{
    for(;;) {
      zmq::message_t request;
      auto result = server.receive(request);
      auto str = request.to_string();
      char type = str.back();
      str.pop_back();
      switch (type) {
        case 'w':
          logger.print_warning_ln(str);
          break;
        case 'e':
          logger.print_error_ln(str);
          break;
        case 'i':
          logger.print_info_ln(str);
          break;
      }
    }
  });

  return 0;
}