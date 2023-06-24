// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/unicode/encoding.h>
#include <aeon/unicode/utf_string_view.h>
#include <aeon/unicode/exception.h>
#include <aeon/unicode/utf8_iterator.h>
#include <array>

namespace aeon::unicode
{

namespace utf8
{

[[nodiscard]] auto to_utf16(const common::string_view &str) -> std::u16string
{
    std::u16string result;

    for (auto i = 0u; i < std::size(str);)
    {
        char32_t codepoint = 0;
        const auto first_byte = static_cast<uint8_t>(str[i]);

        if ((first_byte & 0b10000000) == 0)
        {
            // Single-byte character (0xxxxxxx)
            codepoint = first_byte;
            i += 1;
        }
        else if ((first_byte & 0b11100000) == 0b11000000)
        {
            // Two-byte character (110xxxxx)
            codepoint = static_cast<char32_t>(first_byte & 0b00011111) << 6;
            codepoint |= static_cast<char32_t>(str[i + 1] & 0b00111111);
            i += 2;
        }
        else if ((first_byte & 0b11110000) == 0b11100000)
        {
            // Three-byte character (1110xxxx)
            codepoint = static_cast<char32_t>(first_byte & 0b00001111) << 12;
            codepoint |= static_cast<char32_t>(str[i + 1] & 0b00111111) << 6;
            codepoint |= static_cast<char32_t>(str[i + 2] & 0b00111111);
            i += 3;
        }
        else if ((first_byte & 0b11111000) == 0b11110000)
        {
            // Four-byte character (11110xxx)
            codepoint = static_cast<char32_t>(first_byte & 0b00000111) << 18;
            codepoint |= static_cast<char32_t>(str[i + 1] & 0b00111111) << 12;
            codepoint |= static_cast<char32_t>(str[i + 2] & 0b00111111) << 6;
            codepoint |= static_cast<char32_t>(str[i + 3] & 0b00111111);
            i += 4;
        }
        else
        {
            // Invalid UTF-8 sequence
            // Handle the error or continue with a replacement character
            codepoint = 0xFFFD; // Replacement character
            i += 1;
        }

        if (codepoint <= 0xFFFF)
        {
            // Codepoint fits in a single UTF-16 code unit
            result.push_back(static_cast<char16_t>(codepoint));
        }
        else
        {
            // Codepoint requires a surrogate pair
            const auto u = codepoint - 0x10000;
            result.push_back(static_cast<char16_t>((u >> 10) + 0xD800));
            result.push_back(static_cast<char16_t>((u & 0x3FF) + 0xDC00));
        }
    }

    return result;
}

[[nodiscard]] auto to_utf32(const common::string_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

} // namespace utf8

namespace utf16
{

[[nodiscard]] auto to_utf8(const std::u16string_view &str) -> common::string
{
    common::string result;

    for (auto i = 0; i < std::size(str); ++i)
    {
        const auto codepoint = str[i];

        if (codepoint <= 0x7F)
        {
            // Single-byte character (0x0000-0x007F)
            result += static_cast<char>(codepoint);
        }
        else if (codepoint <= 0x7FF)
        {
            // Two-byte character (0x0080-0x07FF)
            result += static_cast<char>(0xC0 | ((codepoint >> 6) & 0x1F));
            result += static_cast<char>(0x80 | (codepoint & 0x3F));
        }
        else
        {
            // Three-byte character (0x0800-0xFFFF)
            result += static_cast<char>(0xE0 | ((codepoint >> 12) & 0x0F));
            result += static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (codepoint & 0x3F));
        }
    }

    return result;
}

[[nodiscard]] auto to_utf32(const std::u16string_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

} // namespace utf16

namespace utf32
{

[[nodiscard]] auto to_utf8(const char32_t c) -> common::string
{
    common::string result;

    if (c <= 0x7F)
    {
        // If the character is within the ASCII range, it can be represented as a single byte in UTF-8.
        result += static_cast<char8_t>(c);
    }
    else if (c <= 0x7FF)
    {
        // If the character is within the range 0x80 - 0x7FF, it requires 2 bytes in UTF-8 representation.
        result += static_cast<char8_t>((c >> 6) | 0xC0);
        result += static_cast<char8_t>((c & 0x3F) | 0x80);
    }
    else if (c <= 0xFFFF)
    {
        // If the character is within the range 0x800 - 0xFFFF, it requires 3 bytes in UTF-8 representation.
        result += static_cast<char8_t>((c >> 12) | 0xE0);
        result += static_cast<char8_t>(((c >> 6) & 0x3F) | 0x80);
        result += static_cast<char8_t>((c & 0x3F) | 0x80);
    }
    else if (c <= 0x10FFFF)
    {
        // If the character is within the range 0x10000 - 0x10FFFF, it requires 4 bytes in UTF-8 representation.
        result += static_cast<char8_t>((c >> 18) | 0xF0);
        result += static_cast<char8_t>(((c >> 12) & 0x3F) | 0x80);
        result += static_cast<char8_t>(((c >> 6) & 0x3F) | 0x80);
        result += static_cast<char8_t>((c & 0x3F) | 0x80);
    }

    return result;
}

[[nodiscard]] auto to_utf8(const std::u32string_view &str) -> common::string
{
    common::string result;
    result.reserve(std::size(str) * 4);

    for (const auto c : str)
    {
        result += to_utf8(c);
    }

    return result;
}

[[nodiscard]] auto to_utf16(const char32_t c) -> std::u16string
{
    std::u16string result;

    if (c <= 0xFFFF)
    {
        // If the character is within the BMP (Basic Multilingual Plane), it can be represented as a single UTF-16 code
        // unit.
        result += static_cast<wchar_t>(c);
    }
    else if (c <= 0x10FFFF)
    {
        // If the character is outside the BMP, it requires a surrogate pair in UTF-16 representation.

        // High surrogate (first 10 bits)
        result += static_cast<wchar_t>(((c - 0x10000) >> 10) + 0xD800);

        // Low surrogate (second 10 bits)
        result += static_cast<wchar_t>(((c - 0x10000) & 0x3FF) + 0xDC00);
    }

    return result;
}

[[nodiscard]] auto to_utf16(const std::u32string_view &str) -> std::u16string
{
    std::u16string result;
    result.reserve(std::size(str) * 2);

    for (const auto c : str)
    {
        result += to_utf16(c);
    }

    return result;
}

} // namespace utf32

} // namespace aeon::unicode
