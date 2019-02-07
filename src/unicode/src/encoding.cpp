// Copyright (c) 2012-2019 Robin Degen

#include <aeon/unicode/encoding.h>
#include <aeon/unicode/utf_string_view.h>
#include "ucnv_wrapper.h"

namespace aeon::unicode
{

namespace utf8
{

auto to_utf16(const std::string_view &str) -> std::wstring
{
    internal::uconverter converter{"utf-8"};
    return converter.to_uchars(str);
}

auto to_utf32(const std::string_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

} // namespace utf8

namespace utf16
{

auto to_utf8(const std::wstring_view &str) -> std::string
{
    internal::uconverter converter{"utf-8"};
    return converter.from_uchars(str);
}

auto to_utf32(const std::wstring_view &str) -> std::u32string
{
    utf_string_view view{str};
    return {std::begin(view), std::end(view)};
}

} // namespace utf16

} // namespace aeon::unicode
