// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/unicode/encoding.h>
#include <aeon/unicode/utf_string_view.h>
#include <aeon/unicode/exception.h>
#include "ucnv_wrapper.h"
#include <array>

namespace aeon::unicode
{

namespace utf8
{

[[nodiscard]] auto to_utf16(const std::u8string_view &str) -> std::u16string
{
    const internal::uconverter converter{"utf-8"};
    return converter.to_uchars(str);
}

[[nodiscard]] auto to_utf32(const std::u8string_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

void append(const char32_t from, std::u8string &to)
{
    std::array<std::uint8_t, 4> data;
    auto data_offset = 0u;
    UBool error = 0;

    U8_APPEND(std::data(data), data_offset, std::size(data), from, error);

    if (error == 1)
        throw unicode_conversion_exception{};

    to.append(std::begin(data), std::begin(data) + data_offset);
}

void append(const std::u32string_view &from, std::u8string &to)
{
    for (const auto c : from)
    {
        append(c, to);
    }
}

} // namespace utf8

namespace utf16
{

[[nodiscard]] auto to_utf8(const std::u16string_view &str) -> std::u8string
{
    const internal::uconverter converter{"utf-8"};
    return converter.from_uchars(str);
}

[[nodiscard]] auto to_utf32(const std::u16string_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

void append(const char32_t from, std::u16string &to)
{
    std::array<char16_t, 2> data;
    auto data_offset = 0u;
    UBool error = 0;

    U16_APPEND(std::data(data), data_offset, std::size(data), from, error);

    if (error == 1)
        throw unicode_conversion_exception{};

    to.append(std::begin(data), std::begin(data) + data_offset);
}

void append(const std::u32string_view &from, std::u16string &to)
{
    for (const auto c : from)
    {
        append(c, to);
    }
}

} // namespace utf16

namespace utf32
{

[[nodiscard]] auto to_utf8(const char32_t c) -> std::u8string
{
    std::u8string to;
    utf8::append(c, to);
    return to;
}

[[nodiscard]] auto to_utf8(const std::u32string_view &str) -> std::u8string
{
    std::u8string to;
    utf8::append(str, to);
    return to;
}

[[nodiscard]] auto to_utf16(const char32_t c) -> std::u16string
{
    std::u16string to;
    utf16::append(c, to);
    return to;
}

[[nodiscard]] auto to_utf16(const std::u32string_view &str) -> std::u16string
{
    std::u16string to;
    utf16::append(str, to);
    return to;
}

} // namespace utf32

} // namespace aeon::unicode
