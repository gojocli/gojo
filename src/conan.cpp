#include "src/conan.hpp"

#include <cstdio>
#include <expected>
#include <filesystem>
#include <format>
#include <fstream>
#include <optional>
#include <ostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

#include "src/config.hpp"
#include "src/utils.hpp"


namespace {

constexpr std::string_view PROFILES = ".conan2/profiles";


std::optional<std::string> setup_profiles(const config::GojoConfig& cfg) {
  // Check for conan profile
  const std::filesystem::path default_profile {
    std::format("{}/{}/default", utils::get_home_dir(), PROFILES)
  };
  if (!std::filesystem::exists(default_profile)) {
    std::string cmd { "conan profile detect --force" };
    const auto res { utils::execute_command(cmd) };
    if (!res.success) {
      return std::make_optional("failed to detect conan profile");
    }
  }

  auto read_res { conan::read_profile("default") };
  if (!read_res.has_value()) {
    return std::make_optional(std::move(read_res.error()));
  }

  // Read default profile and create new profile based on a combination
  // of the default and the GojoConfig, ensuring the same compiler, build mode,
  // and language standard are used for both.
  const conan::Profile profile { read_res.value() };
  auto write_res { write_profile(profile, cfg) };
  if (write_res.has_value()) {
    return write_res;
  }

  return std::nullopt;
}


std::optional<std::string> get_compiler_version(std::string_view compiler) {
  std::string cmd { std::format("{} -dumpversion", compiler) };
  auto res { utils::execute_command(cmd, true, true) };
  if (!res.success) {
    return std::nullopt;
  }

  // Return the major version number without any decimals.
  auto idx { res.output.find_first_of('.') };
  if (idx == std::string::npos) {
    // No decimals included in the string.
    return res.output;
  }

  return res.output.substr(0, idx);
}

}  // namespace

namespace conan {

// This function is probably not needed.
/*
std::optional<std::string> init(const config::GojoConfig& cfg) {
  auto result { setup_profiles(cfg) };
  if (result.has_value()) {
    return result;
  }

  return install(cfg);
}
*/


std::optional<std::string> install(const config::GojoConfig& cfg) {
  const std::filesystem::path profile_file {
    std::format("{}/{}/{}", utils::get_home_dir(), PROFILES, cfg.project_name)
  };
  if (!std::filesystem::exists(profile_file)) {
    auto result { setup_profiles(cfg) };
    if (result.has_value()) {
      return result;
    }
  }

  constexpr std::string_view cmd_str { 
    "conan install . "
    "--deployer=full_deploy "
    "--output-folder=./deps "
    "--build=missing "
    "--profile={} "
    "-s build_type={}"
  };

  // In order to download the packages in debug and release mode, we have
  // to install two times, one, for each build type.
  // Kinda sucks...
  std::string cmd_dbg { std::format(cmd_str, cfg.project_name, "Debug") };
  std::string cmd_rel { std::format(cmd_str, cfg.project_name, "Release") };

  std::println(MAGENTA("Installing conan dependencies...\n"));
  std::fflush(stdout);

  std::filesystem::current_path(cfg.project_root);
  auto dbg_res { utils::execute_command(cmd_dbg) };
  if (!dbg_res.success) {
    return std::make_optional("failed to install conan dependencies");
  }

  auto rel_res { utils::execute_command(cmd_rel) };
  if (!rel_res.success) {
    return std::make_optional("failed to install conan dependencies");
  }

  std::fflush(stdout);
  std::println(GREEN("\nDependencies installed successfully"));
  std::println(
    MAGENTA(
      "\nAdd the following line to your CMakeLists.txt"
      " in the root of the project:"
    )
  );
  std::println(CYAN("\tfind_package(<package_name> REQUIRED)"));
  std::println(MAGENTA("for each package installed."));
  return std::nullopt;
}


std::expected<Profile, std::string>
read_profile(std::string_view profile_name) {
  const std::filesystem::path profile_file {
    std::format("{}/{}/{}", utils::get_home_dir(), PROFILES, profile_name)
  };
  if (!std::filesystem::exists(profile_file)) {
    return std::unexpected {
      std::format("file not found: {}", profile_file.string())
    };
  }

  std::ifstream profile_stream(profile_file);
  if (!profile_stream.is_open()) {
    return std::unexpected {
      std::format("failed to open file: {}", profile_file.string())
    };
  }

  Profile profile {};
  std::string line {};
  std::string label {};
  std::string other_settings {};

  while (std::getline(profile_stream, line)) {
    // Conan profiles typically start with a '[settings]' section.
    if (line.starts_with('[')) {
      continue;
    }

    // Split line by '='.
    std::stringstream ss { line };
    std::getline(ss, label, '=');

    if (label == "arch") {
      std::getline(ss, profile.arch);
    }
    else if (label == "build_type") {
      std::getline(ss, profile.build_type);
    }
    else if (label == "compiler") {
      std::getline(ss, profile.compiler);
    }
    else if (label == "compiler.cppstd" || label == "compiler.cstd") {
      std::getline(ss, profile.std);
    }
    else if (label == "compiler.libcxx") {
      std::getline(ss, profile.lib);
    }
    else if (label == "compiler.version") {
      std::getline(ss, profile.compiler_version);
    }
    else if (label == "os") {
      std::getline(ss, profile.os);
    }
    else {
      // Not a field that we need to care about, but we should still
      // copy it over to the profile for this project.
      std::getline(ss, other_settings);
      profile.other_settings.append(label + '=');
      profile.other_settings.append(other_settings + '\n');
    }
  }

  return profile;
}


std::optional<std::string> write_profile(const Profile& profile,
                                         const config::GojoConfig& cfg) {
  const std::filesystem::path profile_file {
    std::format("{}/{}/{}", utils::get_home_dir(), PROFILES, cfg.project_name)
  };

  std::ofstream profile_stream(profile_file);
  if (!profile_stream.is_open()) {
    return std::make_optional(
      std::format("failed to open file: {}", profile_file.string())
    );
  }

  // Need to chop off the '++' for conan, only gcc and clang are valid compilers,
  // though they refer to the C++ versions (g++ and clang++) when compiling C++
  // libraries.
  // TODO: Let user decide compiler version ?
  std::string_view compiler { profile.compiler };
  std::string_view compiler_version { profile.compiler_version };
  if (cfg.compiler.starts_with("clang")) {
    compiler = "clang";
    auto cv_res { get_compiler_version(cfg.compiler) };
    if (!cv_res.has_value()) {
      return std::make_optional(std::format("failed to find compiler: {}", cfg.compiler));
    }
    compiler_version = cv_res.value();
  }
  if (cfg.compiler.starts_with("g")) {
    compiler = "gcc";
    auto cv_res { get_compiler_version(cfg.compiler) };
    if (!cv_res.has_value()) {
      return std::make_optional(std::format("failed to find compiler: {}", cfg.compiler));
    }
    compiler_version = cv_res.value();
  }

  const bool is_cpp { cfg.project_lang == "C++" };
  std::string lang_std { std::to_string(cfg.lang_standard) };
  if (cfg.gnu_extensions) {
    lang_std = "gnu" + lang_std;
  }

  const std::string updated_profile { std::format(
R"([settings]
arch={0}
build_type={1}
compiler={2}
{3}={4}
compiler.libcxx={5}
copmiler.version={6}
os={7}
{8})",
      profile.arch,
      cfg.build_type,
      compiler,
      is_cpp ? "compiler.cppstd" : "compiler.cstd",
      lang_std,
      profile.lib,
      compiler_version,
      profile.os,
      profile.other_settings)
  };

  profile_stream << updated_profile << std::flush;

  return std::nullopt;
}

}  // namespace conan
