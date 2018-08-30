/*
 * Copyright (c) 2012-2018 Robin Degen
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
#include <aeon/common/utf8_string_view.h>
#include <aeon/common/utf8_utils.h>
#include <string>

using namespace aeon;

TEST(test_utf8_string_view, test_bom_check)
{
    EXPECT_FALSE(common::utf8::has_bom(""));
    EXPECT_FALSE(common::utf8::has_bom("a"));
    EXPECT_FALSE(common::utf8::has_bom("ab"));
    EXPECT_FALSE(common::utf8::has_bom("abc"));

    const std::string str = "abcde";
    EXPECT_FALSE(common::utf8::has_bom(str));

    const std::string str2 = common::utf8::bom() + "abcde";
    EXPECT_TRUE(common::utf8::has_bom(str2));
}

static void check_strip_bom(const std::string &str)
{
    std::string bom_str = common::utf8::bom() + str;
    EXPECT_TRUE(common::utf8::has_bom(bom_str));
    EXPECT_EQ(bom_str.size(), str.size() + 3);

    common::utf8::strip_bom(bom_str);
    EXPECT_FALSE(common::utf8::has_bom(bom_str));
    EXPECT_EQ(bom_str.size(), str.size());
}

TEST(test_utf8_string_view, test_strip_bom)
{
    check_strip_bom("");
    check_strip_bom(u8"abcde");
    check_strip_bom(u8"\u0100\u0101\u0102\u0103\u0104");
}

static void check_skip_bom(const std::string &str)
{
    std::string bom_str = common::utf8::bom() + str;
    const auto itr = common::utf8::skip_bom(std::begin(bom_str), std::end(bom_str));
    EXPECT_EQ(str, (std::string{itr, std::end(bom_str)}));
}

TEST(test_utf8_string_view, test_skip_bom)
{
    check_skip_bom(u8"");
    check_skip_bom(u8"abcde");
    check_skip_bom(u8"\u0100\u0101\u0102\u0103\u0104");
}

TEST(test_utf8_string_view, test_codepoints)
{
    const auto bom_str = common::utf8::bom();
    EXPECT_EQ(3, common::utf8::codepoint_length(std::begin(bom_str)));

    const std::string str = u8"abcde";

    for (auto itr = std::begin(str); itr != std::end(str);)
    {
        EXPECT_EQ(1, common::utf8::codepoint_length(itr));

        char32_t value = 0;
        ASSERT_NO_THROW(itr = common::utf8::read_codepoint(itr, std::end(str), value));
    }

    const std::string str2 = u8"\u0100\u0101\u0102\u0103\u0104";

    for (auto itr = std::begin(str2); itr != std::end(str2);)
    {
        EXPECT_EQ(2, common::utf8::codepoint_length(itr));

        char32_t value = 0;
        ASSERT_NO_THROW(itr = common::utf8::read_codepoint(itr, std::end(str2), value));
    }

    const std::string str3 = u8"\u0800\u0801\u0802\u0803\u0804";

    for (auto itr = std::begin(str3); itr != std::end(str3);)
    {
        EXPECT_EQ(3, common::utf8::codepoint_length(itr));

        char32_t value = 0;
        ASSERT_NO_THROW(itr = common::utf8::read_codepoint(itr, std::end(str3), value));
    }

    const std::string str4 = u8"\U0001F600\U0001F601\U0001F602\U0001F603";

    for (auto itr = std::begin(str4); itr != std::end(str4);)
    {
        EXPECT_EQ(4, common::utf8::codepoint_length(itr));

        char32_t value = 0;
        ASSERT_NO_THROW(itr = common::utf8::read_codepoint(itr, std::end(str4), value));
    }
}

template <typename iterator_t>
static void check_read_codepoint(const iterator_t itr, const iterator_t end, const char32_t expected)
{
    char32_t value = 0;
    ASSERT_NO_THROW(common::utf8::read_codepoint(itr, end, value));
    EXPECT_EQ(expected, value);
}

TEST(test_utf8_string_view, test_codepoint_values_1byte)
{
    const std::string str = u8"abcdefghijklmnop";

    for (auto itr = std::begin(str); itr != std::end(str); ++itr)
    {
        check_read_codepoint<std::string::const_iterator>(itr, std::end(str), *itr);
    }
}

TEST(test_utf8_string_view, test_codepoint_values_2bytes)
{
    const std::string str = u8"\u0100\u0101\u0102\u0103\u0104\u0105\u0106\u0107";

    char32_t c = 0x100;
    for (auto itr = std::begin(str); itr != std::end(str); itr += 2)
    {
        check_read_codepoint<std::string::const_iterator>(itr, std::end(str), c++);
    }
}

TEST(test_utf8_string_view, test_codepoint_values_3bytes)
{
    const std::string str = u8"\u0800\u0801\u0802\u0803\u0804\u0805\u0806\u0807";

    char32_t c = 0x800;
    for (auto itr = std::begin(str); itr != std::end(str); itr += 3)
    {
        check_read_codepoint<std::string::const_iterator>(itr, std::end(str), c++);
    }
}

TEST(test_utf8_string_view, test_codepoint_values_4bytes)
{
    const std::string str = u8"\U0001F600\U0001F601\U0001F602\U0001F603\U0001F604";

    char32_t c = 0x1f600;
    for (auto itr = std::begin(str); itr != std::end(str); itr += 4)
    {
        check_read_codepoint<std::string::const_iterator>(itr, std::end(str), c++);
    }
}

TEST(test_utf8_string_view, test_utf8_string_view_1byte)
{
    const std::string str = u8"abcde";
    const common::utf8::utf8_string_view view{str};

    auto count = 0;
    EXPECT_NO_THROW(for (const auto c : view) { ++count; });
    EXPECT_EQ(count, str.size());
}

TEST(test_utf8_string_view, test_utf8_string_view_2bytes)
{
    const std::string str = u8"\u0100\u0101\u0102\u0103\u0104\u0105\u0106\u0107";
    const common::utf8::utf8_string_view view{str};

    auto count = 0;
    EXPECT_NO_THROW(for (const auto c : view) { ++count; });
    EXPECT_EQ(count, 8);
}

TEST(test_utf8_string_view, test_utf8_string_view_3bytes)
{
    const std::string str = u8"\u0800\u0801\u0802\u0803\u0804\u0805\u0806\u0807";
    const common::utf8::utf8_string_view view{str};

    auto count = 0;
    EXPECT_NO_THROW(for (const auto c : view) { ++count; });
    EXPECT_EQ(count, 8);
}

TEST(test_utf8_string_view, test_utf8_string_view_4bytes)
{
    const std::string str = u8"\U0001F600\U0001F601\U0001F602\U0001F603\U0001F604";
    const common::utf8::utf8_string_view view{str};

    auto count = 0;
    EXPECT_NO_THROW(for (const auto c : view) { ++count; });
    EXPECT_EQ(count, 5);
}

TEST(test_utf8_string_view, test_utf8_string_view_mixed_bytes)
{
    const std::string str = u8"\u0102a\u0804bc\u0100\u0102\U0001F600g\u0804\u0107\U0001F601\u0102ef";
    const common::utf8::utf8_string_view view{str};

    auto count = 0;
    EXPECT_NO_THROW(for (const auto c : view) { ++count; });
    EXPECT_EQ(count, 15);
}

TEST(test_utf8_string_view, test_utf8_strlen)
{
    EXPECT_EQ(5, common::utf8::utf8_strlen(u8"abcde"));
    EXPECT_EQ(8, common::utf8::utf8_strlen(u8"\u0100\u0101\u0102\u0103\u0104\u0105\u0106\u0107"));
    EXPECT_EQ(8, common::utf8::utf8_strlen(u8"\u0800\u0801\u0802\u0803\u0804\u0805\u0806\u0807"));
    EXPECT_EQ(5, common::utf8::utf8_strlen(u8"\U0001F600\U0001F601\U0001F602\U0001F603\U0001F604"));
    EXPECT_EQ(15, common::utf8::utf8_strlen(u8"\u0102a\u0804bc\u0100\u0102\U0001F600g\u0804\u0107\U0001F601\u0102ef"));
}

TEST(test_utf8_string_view, test_utf8_append_and_read)
{
    std::array<char32_t, 10> expected{0x1f600, 0x101, 0x801, 'a', 0x1f600, 0x102, 0x103, 0x806, ' ', 0x806};

    std::string str;

    for (auto i = 0u; i < expected.size(); ++i)
    {
        common::utf8::utf8_append(std::back_inserter(str), expected[i]);
        EXPECT_EQ(i + 1, common::utf8::utf8_strlen(str));
    }

    const common::utf8::utf8_string_view view{str};

    auto i = 0u;
    for (auto c : view)
    {
        EXPECT_EQ(c, expected[i++]);
    }
}

TEST(test_utf8_string_view, test_utf8_append_to_string)
{
    std::string str;
    EXPECT_EQ(0, common::utf8::utf8_strlen(str));
    common::utf8::utf8_append(str, 0x806);
    EXPECT_EQ(1, common::utf8::utf8_strlen(str));
    common::utf8::utf8_append(str, 0x1f600);
    EXPECT_EQ(2, common::utf8::utf8_strlen(str));
}
