// Copyright (c) 2012-2019 Robin Degen

#include <aeon/unicode/encoding.h>
#include "ucnv_wrapper.h"

namespace aeon::unicode
{

namespace utf8
{

auto to_utf16(const std::string &str) -> std::wstring
{
    internal::uconverter converter{"utf-8"};
    return converter.to_uchars(str);
}

} // namespace utf8

namespace utf16
{

auto to_utf8(const std::wstring &str) -> std::string
{
    internal::uconverter converter{"utf-8"};
    return converter.from_uchars(str);
}

} // namespace utf16

} // namespace aeon::unicode
