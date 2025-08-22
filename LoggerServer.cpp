#include <Logger.hpp>
#include <ZMQServer.hpp>
#include <cstring>

int main() {
  ZMQServer server = ZMQServer("tcp://*:5555");
  Logger logger;

  server.start([&]{
    for(;;) {
      char buffer[1024];
      auto result = server.receive(buffer, sizeof(buffer));
      if (result > 0) {
        std::string str(buffer, result);
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
      server.send("");
    }
  });

  return 0;
}