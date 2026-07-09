#ifndef GOJO_SRC_COMMANDS_HPP
#define GOJO_SRC_COMMANDS_HPP

#include <optional>
#include <span>
#include <string>
#include <string_view>

#include "src/config.hpp"


namespace commands {

std::optional<std::string> init(std::span<std::string_view> args);


std::optional<std::string> build(std::span<std::string_view> args);


std::optional<std::string> run(std::span<std::string_view> args);


std::optional<std::string> test(std::span<std::string_view> args);


std::optional<std::string> clean(std::span<std::string_view> args);


std::optional<std::string> fmt(std::span<std::string_view> args);


std::optional<std::string> check(std::span<std::string_view> args);


std::optional<std::string> file_template(std::span<std::string_view> args);


std::optional<std::string> refresh(std::span<std::string_view> args,
                                   std::optional<config::GojoConfig> cfg_in);


std::optional<std::string> install(std::span<std::string_view> args);


std::optional<std::string> profile(std::span<std::string_view> args);


void info();


void help();

}  // namespace commands

#endif
