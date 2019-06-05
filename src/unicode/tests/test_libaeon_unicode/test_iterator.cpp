// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/unicode/encoding.h>
#include <aeon/unicode/utf_string_view.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>

using namespace aeon;

TEST(test_iterator, test_iterator_utf)
{
    const auto utf8_str = u8"らき☆すた";
    const auto utf16_str = unicode::utf8::to_utf16(utf8_str);

    unicode::utf_string_view utf8_view{utf8_str};
    const std::vector<char32_t> decoded_utf8(std::begin(utf8_view), std::end(utf8_view));
    EXPECT_EQ(5, std::size(decoded_utf8));
    EXPECT_THAT(decoded_utf8, testing::ElementsAre(12425, 12365, 9734, 12377, 12383));

    unicode::utf_string_view utf16_view{utf16_str};
    const std::vector<char32_t> decoded_utf16(std::begin(utf16_view), std::end(utf16_view));
    EXPECT_EQ(5, std::size(decoded_utf16));
    EXPECT_THAT(decoded_utf16, testing::ElementsAre(12425, 12365, 9734, 12377, 12383));
}

TEST(test_iterator, test_iterator_utf8_character_str)
{
    const auto utf8_str = u8"らき☆すた";
    const auto utf16_str = unicode::utf8::to_utf16(utf8_str);

    unicode::utf_string_view utf8_view{utf8_str};
    for (auto itr = std::begin(utf8_view); itr != std::end(utf8_view); ++itr)
    {
        EXPECT_EQ(unicode::utf32::to_utf8(*itr), itr.character_str());
    }
}

TEST(test_iterator, test_iterator_utf16_character_str)
{
    const auto utf8_str = u8"らき☆すた";
    const auto utf16_str = unicode::utf8::to_utf16(utf8_str);

    unicode::utf_string_view utf16_view{utf16_str};
    for (auto itr = std::begin(utf16_view); itr != std::end(utf16_view); ++itr)
    {
        EXPECT_EQ(unicode::utf32::to_utf16(*itr), itr.character_str());
    }
}

TEST(test_iterator, test_iterator_utf32)
{
    const auto str = U"らき☆すた";

    unicode::utf_string_view utf32_view{str};
    const std::vector<char32_t> decoded(std::begin(utf32_view), std::end(utf32_view));
    EXPECT_EQ(5, std::size(decoded));
    EXPECT_THAT(decoded, testing::ElementsAre(12425, 12365, 9734, 12377, 12383));
}
