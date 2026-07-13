#include "src/utils.hpp"

#include <array>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <print>
#ifdef __APPLE__
#include <_stdio.h>
#endif
#include <string>
#include <string_view>


namespace utils {

CommandResult execute_command(std::string& cmd,
                              bool capture_err,
                              bool capture_output) {
  if (capture_err) {
    cmd.append(" 2>&1");
  }

  constexpr unsigned BUFFER_SIZE { 128 };
  std::array<char, BUFFER_SIZE> buffer {};
  std::string output {};

  // For whatever reason the windows version of these functions
  // start with an underscore? God I hate windows.
  #if defined (_WIN32) || defined (_WIN64)
    FILE* pipe = _popen(cmd.c_str(), "r");
  #else
    FILE* pipe = popen(cmd.c_str(), "r");
  #endif

  if (!pipe) {
    return CommandResult { .output={}, .success=false };
  }

  if (capture_output) {
    while (fgets(buffer.data(),
                 static_cast<int>(buffer.size()),
                 pipe) != nullptr) {
      output += buffer.data();
    }
  }
  else {
    while (fgets(buffer.data(),
                 static_cast<int>(buffer.size()),
                 pipe) != nullptr) {
      std::print("{}", buffer.data());
    }
  }

  #if defined (_WIN32) || defined (_WIN64)
    const int rc = _pclose(pipe);
  #else
    const int rc = pclose(pipe);
  #endif

  if (rc != EXIT_SUCCESS) {
    return CommandResult { .output=output, .success=false };
  }

  return CommandResult { .output=output, .success=true };
}


std::string to_upper(std::string_view str) {
  std::string upper {};
  for (const char c : str) {
    upper.push_back(
      // Sometimes C++ is dumb as fuck...why does toupper
      // take in an int?
      static_cast<char>(std::toupper(static_cast<int>(c)))
    );
  }
  return upper;
}


std::string to_lower(std::string_view str) {
  std::string lower {};
  for (const char c : str) {
    lower.push_back(
      static_cast<char>(std::tolower(static_cast<int>(c)))
    );
  }
  return lower;
}


const std::string_view get_home_dir() {
  const std::string_view HOME = std::getenv("HOME");
  return HOME;
}


const std::string get_profiles_dir() {
  const std::string profiles_dir {
    std::format("{}/.gojocli/profiles", get_home_dir())
  };
  return profiles_dir;
}

}  // namespace utils
