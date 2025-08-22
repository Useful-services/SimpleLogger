cmake_minimum_required(VERSION 3.20)

project(DatabaseWrapper CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# include(FetchContent)

# FetchContent_Declare(
#   fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG master
# )

# FetchContent_Declare(
#   zeromq
#   GIT_REPOSITORY https://github.com/zeromq/libzmq.git
#   GIT_TAG v4.3.4
# )

# FetchContent_Declare(
#   cppzmq
#   GIT_REPOSITORY https://github.com/zeromq/cppzmq.git
#   GIT_TAG v4.9.0
# )

set(BUILD_SHARED OFF CACHE BOOL "Build static library")
set(BUILD_STATIC ON CACHE BOOL "Enable static build")
set(WITH_DOCS OFF CACHE BOOL "Disable docs")

# FetchContent_MakeAvailable(fmt zeromq cppzmq)

add_subdirectory(submodules/libzmq)
add_subdirectory(submodules/cppzmq)
add_subdirectory(submodules/fmt)

add_library(LOGGER source/Logger.cpp)

add_library(ZMQ source/ZMQClient.cpp source/ZMQServer.cpp)

target_link_libraries(LOGGER PUBLIC
  fmt::fmt
)
target_include_directories(LOGGER PUBLIC
  include
)

target_link_libraries(ZMQ PUBLIC
  libzmq-static
  cppzmq
)
target_include_directories(ZMQ PUBLIC
  include
)

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