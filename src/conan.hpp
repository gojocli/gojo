#ifndef GOJO_SRC_CONAN_HPP
#define GOJO_SRC_CONAN_HPP

#include <expected>
#include <optional>
#include <string>
#include <string_view>

#include "src/config.hpp"


namespace conan {

struct Profile {
  std::string arch;
  std::string build_type;
  std::string compiler;
  std::string std;
  std::string lib;
  std::string compiler_version;
  std::string os;
  std::string other_settings;
};


std::optional<std::string> install(const config::GojoConfig& cfg);


std::expected<Profile, std::string>
read_profile(std::string_view profile_name);


std::optional<std::string> write_profile(const Profile& profile,
                                         const config::GojoConfig& cfg);

}  // namespace conan

#endif
