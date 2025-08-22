cmake_minimum_required(VERSION 3.20)

project(DatabaseWrapper CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# ZMQ build options
set(BUILD_SHARED OFF CACHE BOOL "Build static library")
set(BUILD_STATIC ON CACHE BOOL "Enable static build")
set(WITH_DOCS OFF CACHE BOOL "Disable docs")
set(WITH_TESTS OFF CACHE BOOL "Disable tests")
set(WITH_PERF_TOOL OFF CACHE BOOL "Disable perf tool")

include(FetchContent)

FetchContent_Declare(
  libzmq
  GIT_REPOSITORY https://github.com/zeromq/libzmq.git
  GIT_TAG v4.3.5
)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(libzmq fmt)

add_library(LOGGER STATIC source/Logger.cpp)
target_link_libraries(LOGGER PUBLIC
  fmt::fmt
)
target_include_directories(LOGGER PUBLIC
  include
)

add_library(ZMQ STATIC source/ZMQClient.cpp source/ZMQServer.cpp)
target_link_libraries(ZMQ PUBLIC
  libzmq-static
)
target_include_directories(ZMQ PUBLIC
  include
  ${libzmq_SOURCE_DIR}/include
)

if (SIMPLE_LOGGER_BUILD_EXAMPLES)
  
  add_executable(LOGGER_EXAMPLE examples/Logger_example.cpp)
  target_link_libraries(LOGGER_EXAMPLE PRIVATE LOGGER)

  add_executable(TEST_SERVER test.cpp)
  target_link_libraries(TEST_SERVER PRIVATE ZMQ)

  add_executable(TEST_CLIENT client.cpp)
  target_link_libraries(TEST_CLIENT PRIVATE ZMQ)

  add_executable(COOL_LOGGER LoggerServer.cpp)
  target_link_libraries(COOL_LOGGER PRIVATE ZMQ LOGGER)

  add_executable(LOGGER_USER LoggerClient.cpp)
  target_link_libraries(LOGGER_USER PRIVATE ZMQ LOGGER)

endif()
