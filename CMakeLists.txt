cmake_minimum_required(VERSION 3.31.6...4.4.0)

project(
  gojo
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

if (BUILD_TESTING)
  add_subdirectory(test)
endif()