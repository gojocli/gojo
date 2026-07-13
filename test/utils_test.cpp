#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "src/utils.hpp"


TEST(UtilsTest, ExecuteCommand) {
  const std::string cmd { "ls" };

  const auto result1 { utils::execute_command(cmd) };
  EXPECT_TRUE(result1.output.empty());
  EXPECT_TRUE(result1.success);

  const auto result2 { utils::execute_command(cmd, true) };
  EXPECT_FALSE(result2.output.empty());
  EXPECT_TRUE(result2.success);

  const std::string bad_cmd { "bad-cmd" };

  const auto result3 { utils::execute_command(bad_cmd) };
  EXPECT_TRUE(result3.output.empty());
  EXPECT_FALSE(result3.success);

  const auto result4 { utils::execute_command(bad_cmd, true) };
  EXPECT_FALSE(result4.output.empty());
  EXPECT_FALSE(result4.success);

  const auto result5 { utils::execute_command(bad_cmd, true) };
  EXPECT_FALSE(result5.output.empty());
  EXPECT_FALSE(result5.success);

}


TEST(UtilsTest, ToUpper) {
  constexpr std::string_view str1 {
    "all lowercase"
  };

  EXPECT_EQ(utils::to_upper(str1), "ALL LOWERCASE");

  constexpr std::string_view str2 {
    "AlTeRnAtInG"
  };

  EXPECT_EQ(utils::to_upper(str2), "ALTERNATING");

  // Not really sure this is necessary, project names should only consist
  // of ASCII characters without numbers or alternate characters.
  constexpr std::string_view str3 {
    "other chars..._-69"
  };

  EXPECT_EQ(utils::to_upper(str3), "OTHER CHARS..._-69");
}


TEST(UtilsTest, ToLower) {
  constexpr std::string_view str1 {
    "ALL UPPERCASE"
  };

  EXPECT_EQ(utils::to_lower(str1), "all uppercase");

  constexpr std::string_view str2 {
    "AlTeRnAtInG"
  };

  EXPECT_EQ(utils::to_lower(str2), "alternating");

  constexpr std::string_view str3 {
    "other chars..._-69"
  };

  // No change.
  EXPECT_EQ(utils::to_lower(str3), str3);
}
