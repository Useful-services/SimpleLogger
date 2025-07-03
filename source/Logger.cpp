#include <Logger.hpp>

Logger::Color::Color(uint8_t r, uint8_t g, uint8_t b) :
  r(r),
  g(g),
  b(b) {}

Logger::Logger(const Logger::color_map& color_map) :
  m_color_map(color_map) {}

Logger::Logger() :
  Logger(
    Logger::color_map({
      {MSG_TYPE::INFO, { 0, 0, 255 }},
      {MSG_TYPE::WARNING, {0, 255, 255}},
      {MSG_TYPE::ERROR, {255, 0, 0}}
    })
  ) {}

void Logger::print(const std::string& message, Logger::MSG_TYPE type, FILE* output_file) const {
  std::string prefix = {};
  switch (type) {
    case Logger::MSG_TYPE::INFO: {
      prefix = "[INFO] ";
      break;
    }
    case Logger::MSG_TYPE::WARNING: {
      prefix = "[WARNING] ";
      break;
    }
    case Logger::MSG_TYPE::ERROR: {
      prefix = "[ERROR] ";
      break;
    }
  }
  if (output_file) {
    std::println(output_file, std::format("{}{}", prefix, message));
  } else {
    std::println(std::format("{}{}", prefix, message));
  }
}