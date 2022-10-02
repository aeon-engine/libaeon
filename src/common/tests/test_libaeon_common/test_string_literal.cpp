// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/string_literal.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace aeon::common;

TEST(test_string_literal, test_string_literal_create_char)
{
    string_literal s{"Hello"};
    string_literal s2 = "Hello";

    EXPECT_EQ(s.size(), strlen("Hello") + 1);
    EXPECT_EQ(s2.size(), strlen("Hello") + 1);

    EXPECT_EQ(std::string{s.c_str()}, std::string{s2.c_str()});
}

TEST(test_string_literal, test_string_literal_create_u8char)
{
    u8string_literal s{u8"Hello"};
    u8string_literal s2 = u8"Hello";

    EXPECT_EQ(s.size(), strlen("Hello") + 1);
    EXPECT_EQ(s2.size(), strlen("Hello") + 1);

    EXPECT_EQ(std::u8string{s.c_str()}, std::u8string{s2.c_str()});
}
