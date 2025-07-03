#include <Logger.hpp>

int main () {
  Logger logger = {};
  logger.print("Hello, world!", Logger::MSG_TYPE::INFO);
  logger.print("Hello, world!", Logger::MSG_TYPE::WARNING);
  logger.print("Hello, world!", Logger::MSG_TYPE::ERROR);
}