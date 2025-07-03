cmake_minimum_required(VERSION 3.20)

project(DatabaseWrapper CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(LOGGER source/Logger.cpp)
target_include_directories(LOGGER PUBLIC include)

add_executable(TEST main.cpp)
target_link_libraries(TEST PUBLIC LOGGER)