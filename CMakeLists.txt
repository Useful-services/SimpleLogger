cmake_minimum_required(VERSION 3.20)

project(DatabaseWrapper CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_library(LOGGER source/Logger.cpp include/Logger.hpp)
target_link_libraries(LOGGER
  PRIVATE
  fmt::fmt
)

add_executable(LOGGER_EXAMPLE examples/Logger_example.cpp)
target_link_libraries(LOGGER_EXAMPLE PRIVATE LOGGER)