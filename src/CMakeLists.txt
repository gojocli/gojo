add_executable(gojo)

target_sources(
  gojo
  PRIVATE
  gojo.cpp
  cmake.cpp
  commands.cpp
  conan.cpp
  config.cpp
  templates.cpp
  utils.cpp
)

target_include_directories(
  gojo
  PRIVATE
  "${CMAKE_SOURCE_DIR}"
)
