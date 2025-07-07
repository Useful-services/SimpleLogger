#include <Logger.hpp>

Logger::Color::Color(uint8_t r, uint8_t g, uint8_t b) :
  r(r),
  g(g),
  b(b) {}


Logger::Logger(const Logger::color_map& col_map) :
  m_color_map(col_map) {
  if (m_color_map.find(MSG_TYPE::INFO) == m_color_map.end()) {
    m_color_map[MSG_TYPE::INFO] = {0, 0, 255};
  }
  if (m_color_map.find(MSG_TYPE::WARNING) == m_color_map.end()) {
    m_color_map[MSG_TYPE::WARNING] = {255, 255, 0};
  }
  if (m_color_map.find(MSG_TYPE::ERROR) == m_color_map.end()) {
    m_color_map[MSG_TYPE::ERROR] = {255, 0, 0};
  }
}

Logger::Logger() :
  Logger({
    {MSG_TYPE::INFO, {0, 0, 255}},
    {MSG_TYPE::WARNING, {255, 255, 0}},
    {MSG_TYPE::ERROR, {255, 0, 0}}
  }) {}

template<bool new_line>
std::string Logger::create_formatted_string(const std::string& message, Logger::MSG_TYPE type) const {
  std::string prefix;
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

  if constexpr(new_line) {
    return fmt::format("{}{}\n", prefix, message);
  } else {
    return fmt::format("{}{}", prefix, message);
  }
}

void Logger::print(const std::string& message, Logger::MSG_TYPE type, const std::string& output_file_path) const {
  print_formatted_text(create_formatted_string<false>(message, type), type, output_file_path);
}

void Logger::println(const std::string& message, Logger::MSG_TYPE type, const std::string& output_file_path) const {
  print_formatted_text(create_formatted_string<true>(message, type), type, output_file_path);
}

void Logger::print_formatted_text(const std::string& formatted_message, Logger::MSG_TYPE type, const std::string& output_file_path) const {
  if (!output_file_path.empty()) {
    try {
      auto out_file = fmt::output_file(output_file_path, fmt::file::APPEND);
      out_file.print("{}", formatted_message);
    }
    catch (const std::exception& e) {
      fmt::print(stderr, "Failed to write in file: {}\n", e.what());
    }
  } else {
    const auto& color = m_color_map.at(type);
    fmt::print(fg(fmt::rgb(color.r, color.g, color.b)), "{}", formatted_message);
  }
}