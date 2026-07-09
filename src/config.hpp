#ifndef GOJO_SRC_CONFIG_HPP
#define GOJO_SRC_CONFIG_HPP

#include <expected>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>


namespace config {

struct GojoConfig {
  std::string project_name;
  std::string project_root;
  std::string project_lang;
  std::string executable_name;
  std::string compiler;
  std::string compiler_flags;
  std::string build_system;
  std::string generator;
  std::string build_type;
  std::string pkg_manager;
  std::string src_ext;
  std::string hdr_ext;
  std::string fmt_style;
  std::string clang_tidy_args;
  std::string cppcheck_checks;
  std::string cppcheck_args;
  std::string testing_framework;
  int lang_standard;
  bool is_library;
  bool testing_enabled;
  bool git_repo;
  bool clang_tidy_enabled;
  bool cppcheck_enabled;
  bool gnu_extensions;
  bool multi_config;
  bool clangd_enabled;
};


const GojoConfig DEFAULT = {
  .project_name = "",
  .project_root = ".",
  .project_lang = "C++",
  .executable_name = "",
  .compiler = "system default",
  .compiler_flags = "-Wall -Wextra -Wpedantic -Wconversion -Wshadow",
  .build_system = "CMake",
  .generator = "system default",
  .build_type = "Debug",
  .pkg_manager = "none",
  .src_ext = "cpp",
  .hdr_ext = "hpp",
  .fmt_style = "google",
  .clang_tidy_args = "",
  .cppcheck_checks = "warning,performance,portability,missingInclude",
  .cppcheck_args = "--inline-suppr --suppress=missingIncludeSystem",
  .testing_framework = "none",
  .lang_standard = 23,
  .is_library = false,
  .testing_enabled = true,
  .git_repo = true,
  .clang_tidy_enabled = true,
  .cppcheck_enabled = true,
  .gnu_extensions = true,
  .multi_config = false,
  .clangd_enabled = true,
};


bool is_multi_config(std::string_view generator);


std::expected<GojoConfig, std::string>
read_from_file(const std::filesystem::path& cfg_file);


std::optional<std::string> write_to_file(const GojoConfig& cfg,
                                         const std::filesystem::path& file={});


std::optional<std::string>
create_template(const std::filesystem::path& project_root);


std::optional<std::string> create_profile(std::string_view profile_name);


std::expected<GojoConfig, std::string>
read_profile(std::string_view profile_name);


}  // namespace config


#endif
