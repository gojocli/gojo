cmake_minimum_required(VERSION 4.3.4)

project(
  gojo
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(test)