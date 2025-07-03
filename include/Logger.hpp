#include <print>
#include <format>
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

    color r;
    color g;
    color b;
  };

  using color_map = std::map<MSG_TYPE, Color>;

  Logger(const color_map& color_map);
  Logger();

  void print(const std::string& message, MSG_TYPE type, FILE* output_file = nullptr) const;
private:
  color_map m_color_map;
};