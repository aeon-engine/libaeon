// Copyright (c) 2012-2019 Robin Degen

#include <aeon/unicode/encoding.h>
#include <array>

#include <gtest/gtest.h>

using namespace aeon;

constexpr std::array<const std::uint8_t, 3> bom_signature{0xef, 0xbb, 0xbf};

inline auto bom() -> std::string
{
    return std::string{std::begin(bom_signature), std::end(bom_signature)};
}

TEST(test_encoding, test_encoding_convert)
{
    const auto str = u8"I like Π, and らき☆すた, Raki☆Suta ";
    const auto converted = unicode::utf8::to_utf16(str);
    const auto converted2 = unicode::utf16::to_utf8(converted);

    EXPECT_EQ(str, converted2);
}

TEST(test_encoding, test_encoding_convert_with_bom)
{
    const auto str = bom() + u8"I like Π, and らき☆すた, Raki☆Suta ";
    const auto converted = unicode::utf8::to_utf16(str);
    const auto converted2 = unicode::utf16::to_utf8(converted);

    EXPECT_EQ(str, converted2);
}
