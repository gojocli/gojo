enable_testing()

find_package(GTest REQUIRED)

# Link all following targets to gtest
link_libraries(gtest::gtest)

# Config
add_executable(config_test)

target_sources(
  config_test
  PRIVATE
  config_test.cpp
  ../src/config.cpp
  ../src/utils.cpp
)

target_include_directories(
  config_test
  PRIVATE
  ${CMAKE_SOURCE_DIR}
)

# Utils
add_executable(utils_test)

target_sources(
  utils_test
  PRIVATE
  utils_test.cpp
  ../src/utils.cpp
)

target_include_directories(
  utils_test
  PRIVATE
  ${CMAKE_SOURCE_DIR}
)


include(GoogleTest)
gtest_discover_tests(config_test)
gtest_discover_tests(utils_test)