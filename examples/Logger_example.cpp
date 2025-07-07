#include <Logger.hpp>

int main() {
  Logger logger = {};
  logger.println("This is info message in default blue color.", Logger::MSG_TYPE::INFO);
  logger.println("This is warning message in default yellow color.", Logger::MSG_TYPE::WARNING);
  logger.println("This is error message in default red color.", Logger::MSG_TYPE::ERROR);
  logger = Logger({
    {Logger::MSG_TYPE::INFO, { 100, 100, 100 }},
    {Logger::MSG_TYPE::WARNING, {0, 255, 0} },
    {Logger::MSG_TYPE::ERROR, {255, 0, 255}}
  });
  logger.print("This is info message in custom gray color.\n", Logger::MSG_TYPE::INFO);
  logger.print("This is warning message in custom green color.\n", Logger::MSG_TYPE::WARNING);
  logger.print("This is error message in custom purple color.\n", Logger::MSG_TYPE::ERROR);
  return 0;
}