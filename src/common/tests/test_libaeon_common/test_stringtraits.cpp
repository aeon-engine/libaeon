// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/common/string_traits.h>

static void check_string(const std::string &value)
{
    EXPECT_EQ(value, aeon::common::string::convert<std::string>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<std::string>::to(value));
}

static void check_int(const std::string &value, const int int_value)
{
    EXPECT_EQ(int_value, aeon::common::string::convert<int>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<int>::to(int_value));
}

static void check_bool(const std::string &value, const bool bool_value)
{
    EXPECT_EQ(bool_value, aeon::common::string::convert<bool>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<bool>::to(bool_value));
}

TEST(test_stringtraits, test_stringtraits_to_string)
{
    check_string("");
    check_string(" ");
    check_string("abc");
    check_string("123");
    check_string("\n");
}

TEST(test_stringtraits, test_stringtraits_to_int)
{
    check_int("0", 0);
    check_int("1", 1);
    check_int("42", 42);
    check_int("1337", 1337);
    check_int("-1", -1);
    check_int("-42", -42);
    check_int("-1337", -1337);
}

TEST(test_stringtraits, test_stringtraits_to_bool)
{
    check_bool("0", false);
    check_bool("1", true);
}
