#ifndef GOJO_SRC_TEMPLATES_HPP
#define GOJO_SRC_TEMPLATES_HPP

#include <string>

#include "src/config.hpp"


namespace templates {

std::string cmakelists_root(const config::GojoConfig& cfg);


std::string cmakelists_src(const config::GojoConfig& cfg);


std::string cmakelists_test(const config::GojoConfig& cfg);


std::string source_file(const config::GojoConfig& cfg);


std::string header_file(const config::GojoConfig& cfg);


std::string test_file(const config::GojoConfig& cfg);


std::string clangd(const config::GojoConfig& cfg);


std::string clangtidy(const config::GojoConfig& cfg);


std::string conanfile(const config::GojoConfig& cfg);

}  // namespace templates

#endif
