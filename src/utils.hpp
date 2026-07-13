#ifndef GOJO_SRC_UTILS_HPP
#define GOJO_SRC_UTILS_HPP

#include <string>
#include <string_view>

#define RED(str) "\033[1;31m" str "\033[0m"
#define GREEN(str) "\033[1;32m" str "\033[0m"
#define YELLOW(str) "\033[33m" str "\033[0m"
#define MAGENTA(str) "\033[1;35m" str "\033[0m"
#define CYAN(str) "\033[36m" str "\033[0m"


namespace utils {

constexpr std::string RED               { "\033[0;31m" };
constexpr std::string_view RED_BOLD     { "\033[1;31m" };
constexpr std::string_view GREEN        { "\033[0;32m" };
constexpr std::string_view GREEN_BOLD   { "\033[1;32m" };
constexpr std::string_view YELLOW       { "\033[0;33m" };
constexpr std::string_view YELLOW_BOLD  { "\033[1;33m" };
constexpr std::string_view MAGENTA      { "\033[0;35m" };
constexpr std::string_view MAGENTA_BOLD { "\033[1;35m" };
constexpr std::string_view CYAN         { "\033[0;36m" };
constexpr std::string_view CYAN_BOLD    { "\033[1;36m" };
constexpr std::string CLEAR             { "\033[0m" };

constexpr int STD11 { 11 };
constexpr int STD20 { 20 };
constexpr int STD23 { 23 };


struct CommandResult {
  std::string output;
  bool success;
};


CommandResult execute_command(const std::string& cmd,
                              bool capture_output=false);


std::string to_upper(std::string_view str);


std::string to_lower(std::string_view str);


const std::string_view get_home_dir();


const std::string get_profiles_dir();

}  // namespace utils

#endif
