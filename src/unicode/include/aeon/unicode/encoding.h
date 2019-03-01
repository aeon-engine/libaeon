// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>
#include <string_view>

namespace aeon::unicode
{

namespace utf8
{

[[nodiscard]] auto to_utf16(const std::string_view &str) -> std::wstring;
[[nodiscard]] auto to_utf32(const std::string_view &str) -> std::u32string;

void append(const char32_t from, std::string &to);
void append(const std::u32string_view &from, std::string &to);

} // namespace utf8

namespace utf16
{

[[nodiscard]] auto to_utf8(const std::wstring_view &str) -> std::string;
[[nodiscard]] auto to_utf32(const std::wstring_view &str) -> std::u32string;

void append(const char32_t from, std::wstring &to);
void append(const std::u32string_view &from, std::wstring &to);

} // namespace utf16

namespace utf32
{

[[nodiscard]] auto to_utf8(const char32_t c) -> std::string;
[[nodiscard]] auto to_utf8(const std::u32string_view &str) -> std::string;

[[nodiscard]] auto to_utf16(const char32_t c) -> std::wstring;
[[nodiscard]] auto to_utf16(const std::u32string_view &str) -> std::wstring;

} // namespace utf32

} // namespace aeon::unicode
