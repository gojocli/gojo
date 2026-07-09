#include <filesystem>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "src/config.hpp"


namespace {

// This code is run from <PROJECT_ROOT>/build/Debug/test
// The assets path is <PROJECT_ROOT>/test/assets
const std::filesystem::path ASSETS_PATH {
  "../../../test/assets"
};

const std::filesystem::path GOOD_GOJO_CONFIG {
  ASSETS_PATH / "test_config_good.gojo"
};

const std::filesystem::path BAD_GOJO_CONFIG {
  ASSETS_PATH / "test_config_bad.gojo"
};

}  // namespace


TEST(ConfigTest, IsMultiConfig) {
  EXPECT_TRUE(config::is_multi_config("XCode"));
  EXPECT_TRUE(config::is_multi_config("Ninja Multi-Config"));
  EXPECT_TRUE(config::is_multi_config("Visual Studio 18 2026"));
  EXPECT_TRUE(config::is_multi_config("Visual Studio 17 2022"));

  // Anything starting with "Visual Studio" is considered multi-config.
  EXPECT_TRUE(config::is_multi_config("Visual Studio blah blah blah"));

  // Capitalization matters.
  EXPECT_FALSE(config::is_multi_config("visual studio"));

  // Windows default generator is multi-config.
  #if defined (_WIN64) || (_WIN32)
    EXPECT_TRUE(config::is_multi_config("system default"));
  #else
    EXPECT_FALSE(config::is_multi_config("system default"));
  #endif


  EXPECT_FALSE(config::is_multi_config("any random string"));
}


TEST(ConfigTest, ReadFromFile) {
  auto good_result { config::read_from_file(GOOD_GOJO_CONFIG) };
  ASSERT_TRUE(good_result.has_value());

  const config::GojoConfig cfg { std::move(good_result.value()) };

  EXPECT_EQ(cfg.project_name, "example");
  EXPECT_FALSE(cfg.is_library);
  EXPECT_EQ(cfg.project_root, std::filesystem::current_path());
  EXPECT_EQ(cfg.executable_name, "example");
  EXPECT_EQ(cfg.project_lang, "C++");
  EXPECT_EQ(cfg.lang_standard, 23);
  EXPECT_TRUE(cfg.gnu_extensions);
  EXPECT_EQ(cfg.compiler, "system default");
  EXPECT_EQ(cfg.compiler_flags, "-Wall -Werror");
  EXPECT_EQ(cfg.build_system, "CMake");
  EXPECT_EQ(cfg.generator, "system default");
  EXPECT_FALSE(cfg.multi_config);
  EXPECT_EQ(cfg.build_type, "Debug");
  EXPECT_EQ(cfg.pkg_manager, "none");
  EXPECT_EQ(cfg.src_ext, "cpp");
  EXPECT_EQ(cfg.hdr_ext, "hpp");
  EXPECT_EQ(cfg.fmt_style, "llvm");
  EXPECT_TRUE(cfg.clangd_enabled);
  EXPECT_TRUE(cfg.clang_tidy_enabled);
  EXPECT_TRUE(cfg.clang_tidy_args.empty());
  EXPECT_FALSE(cfg.cppcheck_enabled);
  EXPECT_TRUE(cfg.cppcheck_checks.empty());
  EXPECT_TRUE(cfg.cppcheck_args.empty());
  EXPECT_TRUE(cfg.testing_enabled);
  EXPECT_EQ(cfg.testing_framework, "none");
  EXPECT_FALSE(cfg.git_repo);

  const auto bad_result { config::read_from_file(BAD_GOJO_CONFIG) };
  EXPECT_FALSE(bad_result.has_value());
  EXPECT_TRUE(
    bad_result
      .error()
      .starts_with(
        "label 'project target' must be one of the following values:"
      )
  );

  // TODO: Test other failure states...gonna be a HUGE pain in the ass...
}


TEST(ConfigTest, WriteToFile) {
  config::GojoConfig cfg { config::DEFAULT };
  cfg.project_name = "example";
  cfg.project_root = ASSETS_PATH.string();
  cfg.executable_name = "example";
  const auto write_result { config::write_to_file(cfg) };
  EXPECT_FALSE(write_result.has_value());

  std::string cfg_path { ASSETS_PATH.string() };
  cfg_path.append("/.gojo");
  EXPECT_TRUE(std::filesystem::exists(cfg_path));

  auto read_result { config::read_from_file(cfg_path) };
  ASSERT_TRUE(read_result.has_value());

  cfg = std::move(read_result.value());
  ASSERT_EQ(cfg.project_name, "example");
  ASSERT_EQ(cfg.project_root, ASSETS_PATH.string());
  ASSERT_EQ(cfg.executable_name, "example");
  ASSERT_EQ(cfg.compiler, config::DEFAULT.compiler);
  ASSERT_EQ(cfg.lang_standard, config::DEFAULT.lang_standard);
  ASSERT_EQ(cfg.compiler_flags, config::DEFAULT.compiler_flags);
  // TODO: check all other fields...should I even bother?

  ASSERT_TRUE(std::filesystem::remove(cfg_path));
}


TEST(ConfigTest, CreateTemplate) {
  const auto create_result { config::create_template(ASSETS_PATH) };
  ASSERT_FALSE(create_result.has_value());

  std::string cfg_path { ASSETS_PATH.string() };
  cfg_path.append("/.gojo");
  ASSERT_TRUE(std::filesystem::exists(cfg_path));

  // All fields are empty, should fail on a read.
  const auto read_result { config::read_from_file(cfg_path) };
  EXPECT_TRUE(!read_result.has_value());

  ASSERT_TRUE(std::filesystem::remove(cfg_path));
}
