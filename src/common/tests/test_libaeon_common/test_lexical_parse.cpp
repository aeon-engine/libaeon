// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/lexical_parse.h>
#include <gtest/gtest.h>

TEST(test_lexical_parse, test_parse_int)
{
    const auto result = aeon::common::lexical_parse::number("1234");
    EXPECT_TRUE(result.is_integer());
    EXPECT_EQ(result.integer_value(), 1234);
    EXPECT_EQ(result.offset(), 4u);
}

TEST(test_lexical_parse, test_parse_int_with_junk)
{
    const auto result = aeon::common::lexical_parse::number("-1234abc");
    EXPECT_TRUE(result.is_integer());
    EXPECT_EQ(result.integer_value(), -1234);
    EXPECT_EQ(result.offset(), 5u);
}

TEST(test_lexical_parse, test_parse_double)
{
    const auto result = aeon::common::lexical_parse::number("1234.0");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 1234.0);
    EXPECT_EQ(result.offset(), 6u);
}

TEST(test_lexical_parse, test_parse_double_with_junk)
{
    const auto result = aeon::common::lexical_parse::number("1234.0abc");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 1234.0);
    EXPECT_EQ(result.offset(), 6u);
}

TEST(test_lexical_parse, test_parse_double_scientific)
{
    const auto result = aeon::common::lexical_parse::number("1234e-1");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}

TEST(test_lexical_parse, test_parse_double_scientific2)
{
    const auto result = aeon::common::lexical_parse::number("1234E-1");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}

TEST(test_lexical_parse, test_parse_double_scientific_with_junk)
{
    const auto result = aeon::common::lexical_parse::number("1234E-1abc");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}

TEST(test_lexical_parse, test_u8parse_int)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234");
    EXPECT_TRUE(result.is_integer());
    EXPECT_EQ(result.integer_value(), 1234);
    EXPECT_EQ(result.offset(), 4u);
}

TEST(test_lexical_parse, test_u8parse_int_with_junk)
{
    const auto result = aeon::common::lexical_parse::number(u8"-1234abc");
    EXPECT_TRUE(result.is_integer());
    EXPECT_EQ(result.integer_value(), -1234);
    EXPECT_EQ(result.offset(), 5u);
}

TEST(test_lexical_parse, test_u8parse_double)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234.0");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 1234.0);
    EXPECT_EQ(result.offset(), 6u);
}

TEST(test_lexical_parse, test_u8parse_double_with_junk)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234.0abc");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 1234.0);
    EXPECT_EQ(result.offset(), 6u);
}

TEST(test_lexical_parse, test_u8parse_double_scientific)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234e-1");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}

TEST(test_lexical_parse, test_u8parse_double_scientific2)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234E-1");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}

TEST(test_lexical_parse, test_u8parse_double_scientific_with_junk)
{
    const auto result = aeon::common::lexical_parse::number(u8"1234E-1abc");
    EXPECT_TRUE(result.is_double());
    EXPECT_EQ(result.double_value(), 123.4);
    EXPECT_EQ(result.offset(), 7u);
}
