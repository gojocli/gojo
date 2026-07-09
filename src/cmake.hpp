#ifndef GOJO_SRC_CMAKE_HPP
#define GOJO_SRC_CMAKE_HPP

#include <optional>
#include <string>
#include <string_view>

#include "src/config.hpp"


namespace cmake {

std::optional<std::string> configure(const config::GojoConfig& cfg, bool reconfigure=false);


std::optional<std::string> build(const config::GojoConfig& cfg, std::string_view target, bool clean);


std::optional<std::string> clean(const config::GojoConfig& cfg, bool deep);

}  // namespace cmake

#endif
