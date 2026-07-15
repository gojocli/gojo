/// @file      src/templates.hpp
/// @brief     File templates used to create project files based on user
///            configuration.
/// @author    William Huffman (whuffman36)
/// @date      2026
/// @copyright MIT License


#ifndef GOJO_SRC_TEMPLATES_HPP
#define GOJO_SRC_TEMPLATES_HPP

#include <string>

#include "src/config.hpp"


namespace templates {

/// @brief Return the contents of the project root CMakeLists.txt file.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's project root CMakeLists.txt file.
std::string cmakelists_root(const config::GojoConfig& cfg);


/// @brief Return the contents of the src directory CMakeLists.txt file.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's src directory CMakeLists.txt file.
std::string cmakelists_src(const config::GojoConfig& cfg);


/// @brief Return the contents of the test directory CMakeLists.txt file.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's test directory CMakeLists.txt file.
std::string cmakelists_test(const config::GojoConfig& cfg);


/// @brief Return the contents of the starter source code file.
/// @details The contents of this file depends on whether the project target
///          is a binary or a library. If the project is a binary target, this
///          file contains the main function entry point of the program. If it
///          is a library target, this file contains the implementation of the
///          header file created in `templates::header_file()`. The file can
///          be C or C++ code, depending on the project configuration.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's starter source code file.
std::string source_file(const config::GojoConfig& cfg);


/// @brief Return the contents of the starter header file.
/// @details This function only applies to projects with a library target. The
///          file can be C or C++ code, depending on the project configuration.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's starter header file.
std::string header_file(const config::GojoConfig& cfg);


/// @brief Return the contents of the starter unit test file.
/// @details The file can be C or C++ code, depending on the project
///          configuration.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's starter unit test file.
std::string test_file(const config::GojoConfig& cfg);


/// @brief Return the contents of the project's clangd config file.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's clangd config file.
std::string clangd(const config::GojoConfig& cfg);


/// @brief Return the contents of the project's clang-tidy config file.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's clang-tidy config file.
std::string clangtidy(const config::GojoConfig& cfg);


/// @brief Return the contents of the project's conan config file.
/// @details This function assumes the use of a conanfile.py config file
///          rather than a conanfile.txt config file, though gojo still
///          works with the .txt variant if added later.
/// @param cfg Project configuration to customize the file contents.
/// @returns Contents of the project's conan config file.
std::string conanfile(const config::GojoConfig& cfg);

}  // namespace templates

#endif
