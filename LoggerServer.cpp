#include <Logger.hpp>
#include <ZMQServer.hpp>
#include <cstring>
#include <iostream>

int main() {
  ZMQServer server = ZMQServer("tcp://*:5555");
  Logger logger;

  // server.start([&]{
  //   for(;;) {
  //     char buffer[MY_BUFFER_SIZE];
  //     auto result = server.receive(buffer, sizeof(buffer));
  //     if (result > 0) {
  //       std::string str(buffer, result);
  //       char type = str.back();
  //       str.pop_back();
  //       switch (type) {
  //         case 'w':
  //           logger.print_warning_ln(str);
  //           break;
  //         case 'e':
  //           logger.print_error_ln(str);
  //           break;
  //         case 'i':
  //           logger.print_info_ln(str);
  //           break;
  //       }
  //     }
  //     server.send("");
  //   }
  // });

  server.start([&] {
    for(;;) {
      char buffer[MY_BUFFER_SIZE] = {};
      auto result = server.receive(buffer, sizeof(buffer));
      server.send_string("");
      MQData data = MQData::from_buffer(buffer);
      switch (data.msg_info.msg_type) {
        case MQData::MessageInfo::msg_type::INFO: {
          logger.print_info_ln(data.message_content);
          break;
        }
        case MQData::MessageInfo::msg_type::WARN: {
          logger.print_warning_ln(data.message_content);
          break;
        }
        case MQData::MessageInfo::msg_type::ERR: {
          logger.print_error_ln(data.message_content);
          break;
        }
      }
    }
  });

  return 0;
}