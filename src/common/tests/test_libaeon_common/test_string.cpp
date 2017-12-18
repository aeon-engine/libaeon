/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>

#include <aeon/common/string.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING(4189)

TEST(test_string, test_string_ltrim_none)
{
    std::string str = "value";
    aeon::common::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_ltrim_spaces)
{
    std::string str = "   value";
    aeon::common::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_ltrimsv_spaces)
{
    std::string str = "   value";
    std::string_view strsv = str;
    aeon::common::string::ltrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_ltrim_spaces_at_end)
{
    std::string str = "value  ";
    aeon::common::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string, test_string_ltrimsv_spaces_at_end)
{
    std::string str = "value  ";
    std::string_view strsv = str;
    aeon::common::string::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string, test_string_ltrim_spaces_at_end2)
{
    std::string str = "  value  ";
    aeon::common::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string, test_string_ltrimsv_spaces_at_end2)
{
    std::string str = "  value  ";
    std::string_view strsv = str;
    aeon::common::string::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string, test_string_rtrim_spaces)
{
    std::string str = "value   ";
    aeon::common::string::rtrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_rtrimsv_spaces)
{
    std::string str = "value   ";
    std::string_view strsv = str;
    aeon::common::string::rtrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_rtrim_spaces_at_beginning)
{
    std::string str = "   value";
    aeon::common::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string, test_string_rtrimsv_spaces_at_beginning)
{
    std::string str = "   value";
    std::string_view strsv = str;
    aeon::common::string::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string, test_string_rtrim_spaces_at_beginning2)
{
    std::string str = "   value   ";
    aeon::common::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string, test_string_rtrimsv_spaces_at_beginning2)
{
    std::string str = "   value   ";
    std::string_view strsv = str;
    aeon::common::string::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string, test_string_trim)
{
    std::string str = "   value   ";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv)
{
    std::string str = "   value   ";
    std::string_view strsv = str;
    aeon::common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim2)
{
    std::string str = "   value";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv2)
{
    std::string str = "   value";
    std::string_view strsv = str;
    aeon::common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim3)
{
    std::string str = "value  ";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv3)
{
    std::string str = "value  ";
    std::string_view strsv = str;
    aeon::common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim4)
{
    std::string str = "value";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv4)
{
    std::string str = "value";
    std::string_view strsv = str;
    aeon::common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_ltrimmed)
{
    EXPECT_EQ("value", aeon::common::string::ltrimmed("   value"));
}

TEST(test_string, test_string_ltrimmedsv)
{
    EXPECT_EQ("value", aeon::common::string::ltrimmedsv("   value"));
}

TEST(test_string, test_string_rtrimmed)
{
    EXPECT_EQ("value", aeon::common::string::rtrimmed("value   "));
}

TEST(test_string, test_string_rtrimmedsv)
{
    EXPECT_EQ("value", aeon::common::string::rtrimmedsv("value   "));
}

TEST(test_string, test_string_trimmed)
{
    EXPECT_EQ("value", aeon::common::string::trimmed("   value   "));
}

TEST(test_string, test_string_trimmedsv)
{
    EXPECT_EQ("value", aeon::common::string::trimmedsv("   value   "));
}

TEST(test_string, test_string_trim_tabs)
{
    std::string str = "\t\tvalue\t\t";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv_tabs)
{
    std::string str = "\t\tvalue\t\t";
    std::string_view strsv = str;
    aeon::common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim_mixed)
{
    std::string str = " \t \t \t value \t \t \t ";
    aeon::common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_split_empty)
{
    std::string str = "";
    auto result = aeon::common::string::split(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string, test_string_splitsv_empty)
{
    std::string str = "";
    auto result = aeon::common::string::splitsv(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string, test_string_split)
{
    std::string str = "one two three";
    auto result = aeon::common::string::split(str, ' ');
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string, test_string_splitsv)
{
    std::string str = "one two three";
    auto result = aeon::common::string::splitsv(str, ' ');
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string, test_string_split_double_space)
{
    std::string str = "one  two three";
    auto result = aeon::common::string::split(str, ' ');
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string, test_string_splitsv_double_space)
{
    std::string str = "one  two three";
    auto result = aeon::common::string::splitsv(str, ' ');
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string, test_string_split_one_token)
{
    std::string str = "one";
    std::vector<std::string> result = aeon::common::string::split(str, ' ');
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("one", result[0]);
}

TEST(test_string, test_string_splitsv_one_token)
{
    std::string str = "one";
    auto result = aeon::common::string::splitsv(str, ' ');
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("one", result[0]);
}

TEST(test_string, test_string_left)
{
    EXPECT_EQ("one", aeon::common::string::left("one two three", 3));
}

TEST(test_string, test_string_leftsv)
{
    EXPECT_EQ("one", aeon::common::string::leftsv("one two three", 3));
}

TEST(test_string, test_string_right)
{
    EXPECT_EQ("ree", aeon::common::string::right("one two three", 3));
}

TEST(test_string, test_string_rightsv)
{
    EXPECT_EQ("ree", aeon::common::string::rightsv("one two three", 3));
}

TEST(test_string, test_utility_strip_left)
{
    EXPECT_EQ("two three", aeon::common::string::strip_left("one two three", 4));
}

TEST(test_string, test_utility_strip_leftsv)
{
    EXPECT_EQ("two three", aeon::common::string::strip_leftsv("one two three", 4));
}

TEST(test_string, test_utility_strip_right)
{
    EXPECT_EQ("one two ", aeon::common::string::strip_right("one two three", 5));
}

TEST(test_string, test_utility_strip_rightsv)
{
    EXPECT_EQ("one two ", aeon::common::string::strip_rightsv("one two three", 5));
}

TEST(test_string, test_utility_strip_both)
{
    EXPECT_EQ("test", aeon::common::string::strip_both("test", 0));
    EXPECT_EQ("test", aeon::common::string::strip_both("'test'", 1));
    EXPECT_EQ("ABC", aeon::common::string::strip_both("123ABC123", 3));
    EXPECT_EQ("", aeon::common::string::strip_both("''", 1));
}

TEST(test_string, test_utility_strip_bothsv)
{
    EXPECT_EQ("test", aeon::common::string::strip_bothsv("test", 0));
    EXPECT_EQ("test", aeon::common::string::strip_bothsv("'test'", 1));
    EXPECT_EQ("ABC", aeon::common::string::strip_bothsv("123ABC123", 3));
    EXPECT_EQ("", aeon::common::string::strip_bothsv("''", 1));
}

TEST(test_string, test_string_args_to_vector_empty)
{
    std::vector<std::string> result = aeon::common::string::args_to_vector(0, nullptr);
    EXPECT_TRUE(result.empty());
}

TEST(test_string, test_string_to_lower)
{
    EXPECT_EQ("test", aeon::common::string::to_lower("TeSt"));
    EXPECT_EQ("this is a test.", aeon::common::string::to_lower("THIS iS a TeSt."));
}

TEST(test_string, test_string_to_upper)
{
    EXPECT_EQ("TEST", aeon::common::string::to_upper("TeSt"));
    EXPECT_EQ("THIS IS A TEST.", aeon::common::string::to_upper("THiS iS a TeSt."));
}

TEST(test_string, test_string_begins_with)
{
    EXPECT_TRUE(aeon::common::string::begins_with("", ""));
    EXPECT_TRUE(aeon::common::string::begins_with("This is a test", "T"));
    EXPECT_TRUE(aeon::common::string::begins_with("This is a test", "Th"));
    EXPECT_TRUE(aeon::common::string::begins_with("This is a test", "This"));
    EXPECT_TRUE(aeon::common::string::begins_with("1234 blah", "123"));

    EXPECT_FALSE(aeon::common::string::begins_with("This is a test", "test"));
    EXPECT_FALSE(aeon::common::string::begins_with("This is a test", "this"));
    EXPECT_FALSE(aeon::common::string::begins_with("This is a test", "his"));
    EXPECT_FALSE(aeon::common::string::begins_with("1234 blah", "blah"));
    EXPECT_FALSE(aeon::common::string::begins_with("", "Blah"));
}

TEST(test_string, test_string_begins_withsv)
{
    EXPECT_TRUE(aeon::common::string::begins_withsv("", ""));
    EXPECT_TRUE(aeon::common::string::begins_withsv("This is a test", "T"));
    EXPECT_TRUE(aeon::common::string::begins_withsv("This is a test", "Th"));
    EXPECT_TRUE(aeon::common::string::begins_withsv("This is a test", "This"));
    EXPECT_TRUE(aeon::common::string::begins_withsv("1234 blah", "123"));

    EXPECT_FALSE(aeon::common::string::begins_withsv("This is a test", "test"));
    EXPECT_FALSE(aeon::common::string::begins_withsv("This is a test", "this"));
    EXPECT_FALSE(aeon::common::string::begins_withsv("This is a test", "his"));
    EXPECT_FALSE(aeon::common::string::begins_withsv("1234 blah", "blah"));
    EXPECT_FALSE(aeon::common::string::begins_withsv("", "Blah"));
}

TEST(test_string, test_string_ends_with)
{
    EXPECT_TRUE(aeon::common::string::ends_with("", ""));
    EXPECT_TRUE(aeon::common::string::ends_with("This is a test", "t"));
    EXPECT_TRUE(aeon::common::string::ends_with("This is a test", "est"));
    EXPECT_TRUE(aeon::common::string::ends_with("This is a test", "test"));
    EXPECT_TRUE(aeon::common::string::ends_with("1234 blah", " blah"));

    EXPECT_FALSE(aeon::common::string::ends_with("This is a test", "This"));
    EXPECT_FALSE(aeon::common::string::ends_with("This is a test", "is"));
    EXPECT_FALSE(aeon::common::string::ends_with("This is a test", "Test"));
    EXPECT_FALSE(aeon::common::string::ends_with("1234 blah", "1234"));
    EXPECT_FALSE(aeon::common::string::ends_with("", "Blah"));
}

TEST(test_string, test_string_ends_withsv)
{
    EXPECT_TRUE(aeon::common::string::ends_withsv("", ""));
    EXPECT_TRUE(aeon::common::string::ends_withsv("This is a test", "t"));
    EXPECT_TRUE(aeon::common::string::ends_withsv("This is a test", "est"));
    EXPECT_TRUE(aeon::common::string::ends_withsv("This is a test", "test"));
    EXPECT_TRUE(aeon::common::string::ends_withsv("1234 blah", " blah"));

    EXPECT_FALSE(aeon::common::string::ends_withsv("This is a test", "This"));
    EXPECT_FALSE(aeon::common::string::ends_withsv("This is a test", "is"));
    EXPECT_FALSE(aeon::common::string::ends_withsv("This is a test", "Test"));
    EXPECT_FALSE(aeon::common::string::ends_withsv("1234 blah", "1234"));
    EXPECT_FALSE(aeon::common::string::ends_withsv("", "Blah"));
}