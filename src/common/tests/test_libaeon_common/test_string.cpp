// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/string.h>
#include <aeon/common/compilers.h>
#include <gtest/gtest.h>

AEON_IGNORE_VS_WARNING(4189)

using namespace aeon;

TEST(test_string, test_string_ltrim_none)
{
    std::string str = "value";
    common::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_ltrim_spaces)
{
    std::string str = "   value";
    common::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_ltrimsv_spaces)
{
    std::string str = "   value";
    std::string_view strsv = str;
    common::string::ltrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_ltrim_spaces_at_end)
{
    std::string str = "value  ";
    common::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string, test_string_ltrimsv_spaces_at_end)
{
    std::string str = "value  ";
    std::string_view strsv = str;
    common::string::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string, test_string_ltrim_spaces_at_end2)
{
    std::string str = "  value  ";
    common::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_string, test_string_ltrimsv_spaces_at_end2)
{
    std::string str = "  value  ";
    std::string_view strsv = str;
    common::string::ltrimsv(strsv);
    EXPECT_EQ("value  ", strsv);
}

TEST(test_string, test_string_rtrim_spaces)
{
    std::string str = "value   ";
    common::string::rtrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_rtrimsv_spaces)
{
    std::string str = "value   ";
    std::string_view strsv = str;
    common::string::rtrimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_rtrim_spaces_at_beginning)
{
    std::string str = "   value";
    common::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string, test_string_rtrimsv_spaces_at_beginning)
{
    std::string str = "   value";
    std::string_view strsv = str;
    common::string::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string, test_string_rtrim_spaces_at_beginning2)
{
    std::string str = "   value   ";
    common::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_string, test_string_rtrimsv_spaces_at_beginning2)
{
    std::string str = "   value   ";
    std::string_view strsv = str;
    common::string::rtrimsv(strsv);
    EXPECT_EQ("   value", strsv);
}

TEST(test_string, test_string_trim)
{
    std::string str = "   value   ";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv)
{
    std::string str = "   value   ";
    std::string_view strsv = str;
    common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim2)
{
    std::string str = "   value";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv2)
{
    std::string str = "   value";
    std::string_view strsv = str;
    common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim3)
{
    std::string str = "value  ";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv3)
{
    std::string str = "value  ";
    std::string_view strsv = str;
    common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim4)
{
    std::string str = "value";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv4)
{
    std::string str = "value";
    std::string_view strsv = str;
    common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_ltrimmed)
{
    EXPECT_EQ("value", common::string::ltrimmed<char>("   value"));
}

TEST(test_string, test_string_ltrimmedsv)
{
    EXPECT_EQ("value", common::string::ltrimmedsv<char>("   value"));
}

TEST(test_string, test_string_rtrimmed)
{
    EXPECT_EQ("value", common::string::rtrimmed<char>("value   "));
}

TEST(test_string, test_string_rtrimmedsv)
{
    EXPECT_EQ("value", common::string::rtrimmedsv<char>("value   "));
}

TEST(test_string, test_string_trimmed)
{
    EXPECT_EQ("value", common::string::trimmed<char>("   value   "));
}

TEST(test_string, test_string_trimmedsv)
{
    EXPECT_EQ("value", common::string::trimmedsv<char>("   value   "));
}

TEST(test_string, test_string_trim_tabs)
{
    std::string str = "\t\tvalue\t\t";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_trimsv_tabs)
{
    std::string str = "\t\tvalue\t\t";
    std::string_view strsv = str;
    common::string::trimsv(strsv);
    EXPECT_EQ("value", strsv);
}

TEST(test_string, test_string_trim_mixed)
{
    std::string str = " \t \t \t value \t \t \t ";
    common::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_string, test_string_split_empty)
{
    std::string str = "";
    auto result = common::string::split<char>(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string, test_string_splitsv_empty)
{
    std::string str = "";
    auto result = common::string::splitsv<char>(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_string, test_string_split)
{
    std::string str = "one two three";
    auto result = common::string::split<char>(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string, test_string_splitsv)
{
    std::string str = "one two three";
    auto result = common::string::splitsv<char>(str, ' ');
    ASSERT_EQ(3u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_string, test_string_split_double_space)
{
    std::string str = "one  two three";
    auto result = common::string::split(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string, test_string_splitsv_double_space)
{
    std::string str = "one  two three";
    auto result = common::string::splitsv<char>(str, ' ');
    ASSERT_EQ(4u, std::size(result));
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_string, test_string_split_one_token)
{
    std::string str = "one";
    const auto result = common::string::split(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string, test_string_splitsv_one_token)
{
    std::string str = "one";
    const auto result = common::string::splitsv<char>(str, ' ');
    ASSERT_EQ(1u, std::size(result));
    EXPECT_EQ("one", result[0]);
}

TEST(test_string, test_string_left)
{
    EXPECT_EQ("one", common::string::left<char>("one two three", 3));
}

TEST(test_string, test_string_leftsv)
{
    EXPECT_EQ("one", common::string::leftsv<char>("one two three", 3));
}

TEST(test_string, test_string_right)
{
    EXPECT_EQ("ree", common::string::right<char>("one two three", 3));
}

TEST(test_string, test_string_rightsv)
{
    EXPECT_EQ("ree", common::string::rightsv<char>("one two three", 3));
}

TEST(test_string, test_utility_strip_left)
{
    EXPECT_EQ("two three", common::string::stripped_left<char>("one two three", 4));

    std::string str = "one two three";
    common::string::strip_left(str, 4);
    EXPECT_EQ("two three", str);
}

TEST(test_string, test_utility_strip_leftsv)
{
    EXPECT_EQ("two three", common::string::stripped_leftsv<char>("one two three", 4));

    const std::string str = "one two three";
    std::string_view view = str;
    common::string::strip_leftsv(view, 4);
    EXPECT_EQ("two three", view);
}

TEST(test_string, test_utility_strip_right)
{
    EXPECT_EQ("one two ", common::string::stripped_right<char>("one two three", 5));

    std::string str = "one two three";
    common::string::strip_right(str, 5);
    EXPECT_EQ("one two ", str);
}

TEST(test_string, test_utility_strip_rightsv)
{
    EXPECT_EQ("one two ", common::string::stripped_rightsv<char>("one two three", 5));

    const std::string str = "one two three";
    std::string_view view = str;
    common::string::strip_rightsv(view, 5);
    EXPECT_EQ("one two ", view);
}

TEST(test_string, test_utility_strip_both)
{
    EXPECT_EQ("test", common::string::stripped_both<char>("test", 0));
    EXPECT_EQ("test", common::string::stripped_both<char>("'test'", 1));
    EXPECT_EQ("ABC", common::string::stripped_both<char>("123ABC123", 3));
    EXPECT_EQ("", common::string::stripped_both<char>("''", 1));

    std::string test = "test";
    common::string::strip_both(test, 0);
    EXPECT_EQ("test", test);

    std::string test2 = "'test'";
    common::string::strip_both(test2, 1);
    EXPECT_EQ("test", test2);

    std::string test3 = "123ABC123";
    common::string::strip_both(test3, 3);
    EXPECT_EQ("ABC", test3);

    std::string test4 = "''";
    common::string::strip_both(test4, 1);
    EXPECT_EQ("", test4);
}

TEST(test_string, test_utility_strip_bothsv)
{
    EXPECT_EQ("test", common::string::stripped_bothsv<char>("test", 0));
    EXPECT_EQ("test", common::string::stripped_bothsv<char>("'test'", 1));
    EXPECT_EQ("ABC", common::string::stripped_bothsv<char>("123ABC123", 3));
    EXPECT_EQ("", common::string::stripped_bothsv<char>("''", 1));

    const std::string test = "test";
    std::string_view view = test;
    common::string::strip_bothsv(view, 0);
    EXPECT_EQ("test", view);

    const std::string test2 = "'test'";
    std::string_view view2 = test2;
    common::string::strip_bothsv(view2, 1);
    EXPECT_EQ("test", view2);

    const std::string test3 = "123ABC123";
    std::string_view view3 = test3;
    common::string::strip_bothsv(view3, 3);
    EXPECT_EQ("ABC", view3);

    const std::string test4 = "''";
    std::string_view view4 = test4;
    common::string::strip_bothsv(view4, 1);
    EXPECT_EQ("", view4);
}

TEST(test_string, test_utility_char_strip_left)
{
    EXPECT_EQ("two three", common::string::char_stripped_left<char>("--two three", '-'));
    EXPECT_EQ("--two three", common::string::char_stripped_left<char>("--two three", '+'));

    std::string str = "--two three";
    common::string::char_strip_left(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string, test_utility_char_strip_leftsv)
{
    EXPECT_EQ("two three--", common::string::char_stripped_leftsv<char>("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string::char_stripped_leftsv<char>("--two three--", '+'));

    std::string_view str = "--two three--";
    common::string::char_strip_leftsv(str, '-');
    EXPECT_EQ("two three--", str);
}

TEST(test_string, test_utility_char_strip_right)
{
    EXPECT_EQ("--two three", common::string::char_stripped_right<char>("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string::char_stripped_right<char>("--two three--", '+'));

    std::string str = "--two three--";
    common::string::char_strip_right(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string, test_utility_char_strip_rightsv)
{
    EXPECT_EQ("--two three", common::string::char_stripped_rightsv<char>("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string::char_stripped_rightsv<char>("--two three--", '+'));

    std::string_view str = "--two three--";
    common::string::char_strip_rightsv(str, '-');
    EXPECT_EQ("--two three", str);
}

TEST(test_string, test_utility_char_strip_both)
{
    EXPECT_EQ("two three", common::string::char_stripped_both<char>("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string::char_stripped_both<char>("--two three--", '+'));

    std::string str = "--two three--";
    common::string::char_strip_both(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string, test_utility_char_strip_bothsv)
{
    EXPECT_EQ("two three", common::string::char_stripped_bothsv<char>("--two three--", '-'));
    EXPECT_EQ("--two three--", common::string::char_stripped_bothsv<char>("--two three--", '+'));

    std::string_view str = "--two three--";
    common::string::char_strip_bothsv(str, '-');
    EXPECT_EQ("two three", str);
}

TEST(test_string, test_string_to_lower)
{
    EXPECT_EQ("test", common::string::to_lower_copy<char>("TeSt"));
    EXPECT_EQ("this is a test.", common::string::to_lower_copy<char>("THIS iS a TeSt."));

    std::string test = "TeSt";
    common::string::to_lower(test);
    EXPECT_EQ("test", test);

    std::string this_is_a_test = "THIS iS a TeSt.";
    common::string::to_lower(this_is_a_test);
    EXPECT_EQ("this is a test.", this_is_a_test);
}

TEST(test_string, test_string_to_upper)
{
    EXPECT_EQ("TEST", common::string::to_upper_copy<char>("TeSt"));
    EXPECT_EQ("THIS IS A TEST.", common::string::to_upper_copy<char>("THiS iS a TeSt."));

    std::string test = "TeSt";
    common::string::to_upper(test);
    EXPECT_EQ("TEST", test);

    std::string this_is_a_test = "THIS iS a TeSt.";
    common::string::to_upper(this_is_a_test);
    EXPECT_EQ("THIS IS A TEST.", this_is_a_test);
}

TEST(test_string, test_string_begins_with)
{
    EXPECT_TRUE(common::string::begins_with<char>("", ""));
    EXPECT_TRUE(common::string::begins_with<char>("This is a test", "T"));
    EXPECT_TRUE(common::string::begins_with<char>("This is a test", "Th"));
    EXPECT_TRUE(common::string::begins_with<char>("This is a test", "This"));
    EXPECT_TRUE(common::string::begins_with<char>("1234 blah", "123"));

    EXPECT_FALSE(common::string::begins_with<char>("This is a test", "test"));
    EXPECT_FALSE(common::string::begins_with<char>("This is a test", "this"));
    EXPECT_FALSE(common::string::begins_with<char>("This is a test", "his"));
    EXPECT_FALSE(common::string::begins_with<char>("1234 blah", "blah"));
    EXPECT_FALSE(common::string::begins_with<char>("", "Blah"));
}

TEST(test_string, test_string_begins_withsv)
{
    EXPECT_TRUE(common::string::begins_withsv<char>("", ""));
    EXPECT_TRUE(common::string::begins_withsv<char>("This is a test", "T"));
    EXPECT_TRUE(common::string::begins_withsv<char>("This is a test", "Th"));
    EXPECT_TRUE(common::string::begins_withsv<char>("This is a test", "This"));
    EXPECT_TRUE(common::string::begins_withsv<char>("1234 blah", "123"));

    EXPECT_FALSE(common::string::begins_withsv<char>("This is a test", "test"));
    EXPECT_FALSE(common::string::begins_withsv<char>("This is a test", "this"));
    EXPECT_FALSE(common::string::begins_withsv<char>("This is a test", "his"));
    EXPECT_FALSE(common::string::begins_withsv<char>("1234 blah", "blah"));
    EXPECT_FALSE(common::string::begins_withsv<char>("", "Blah"));
}

TEST(test_string, test_string_ends_with)
{
    EXPECT_TRUE(common::string::ends_with<char>("", ""));
    EXPECT_TRUE(common::string::ends_with<char>("This is a test", "t"));
    EXPECT_TRUE(common::string::ends_with<char>("This is a test", "est"));
    EXPECT_TRUE(common::string::ends_with<char>("This is a test", "test"));
    EXPECT_TRUE(common::string::ends_with<char>("1234 blah", " blah"));

    EXPECT_FALSE(common::string::ends_with<char>("This is a test", "This"));
    EXPECT_FALSE(common::string::ends_with<char>("This is a test", "is"));
    EXPECT_FALSE(common::string::ends_with<char>("This is a test", "Test"));
    EXPECT_FALSE(common::string::ends_with<char>("1234 blah", "1234"));
    EXPECT_FALSE(common::string::ends_with<char>("", "Blah"));
}

TEST(test_string, test_string_ends_withsv)
{
    EXPECT_TRUE(common::string::ends_withsv<char>("", ""));
    EXPECT_TRUE(common::string::ends_withsv<char>("This is a test", "t"));
    EXPECT_TRUE(common::string::ends_withsv<char>("This is a test", "est"));
    EXPECT_TRUE(common::string::ends_withsv<char>("This is a test", "test"));
    EXPECT_TRUE(common::string::ends_withsv<char>("1234 blah", " blah"));

    EXPECT_FALSE(common::string::ends_withsv<char>("This is a test", "This"));
    EXPECT_FALSE(common::string::ends_withsv<char>("This is a test", "is"));
    EXPECT_FALSE(common::string::ends_withsv<char>("This is a test", "Test"));
    EXPECT_FALSE(common::string::ends_withsv<char>("1234 blah", "1234"));
    EXPECT_FALSE(common::string::ends_withsv<char>("", "Blah"));
}

TEST(test_string, test_make_string_view)
{
    std::string expected = "Hello";
    const auto expected_view = common::string::make_string_view(std::begin(expected), std::end(expected));
    EXPECT_EQ(expected, expected_view);
}

TEST(test_string, test_make_string_view_empty)
{
    std::string expected;
    const auto expected_view = common::string::make_string_view(std::begin(expected), std::end(expected));
    EXPECT_TRUE(expected_view.empty());
    EXPECT_EQ(expected, expected_view);
}
