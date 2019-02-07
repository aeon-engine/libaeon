// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::unicode
{

namespace utf8
{

auto to_utf16(const std::string_view &str) -> std::wstring;
auto to_utf32(const std::string_view &str) -> std::u32string;

} // namespace utf8

namespace utf16
{

auto to_utf8(const std::wstring_view &str) -> std::string;
auto to_utf32(const std::wstring_view &str) -> std::u32string;

} // namespace utf16

} // namespace aeon::unicode
