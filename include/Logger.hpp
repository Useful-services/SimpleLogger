#pragma once

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/os.h>
#include <memory>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdint.h>
#include <string>
#include <map>


class Logger {
public:
  enum class MSG_TYPE {
    INFO,
    WARNING,
    ERROR
  };

  struct Color {

    using color = uint8_t;

    Color(color r, color g, color b);
    Color() = default;

    color r;
    color g;
    color b;
  };

  using color_map = std::map<MSG_TYPE, Color>;

  Logger(const color_map& col_map);
  Logger();

  void print(const std::string& message, MSG_TYPE type, const std::string& output_file_path = "") const;
  void println(const std::string& message, MSG_TYPE type, const std::string& output_file_path = "") const;
private:

  template<bool new_line>
  std::string create_formatted_string(const std::string& message, MSG_TYPE type) const;
  void print_formatted_text(const std::string& formatted_message, MSG_TYPE type, const std::string& output_file_path) const;

  color_map m_color_map;
};