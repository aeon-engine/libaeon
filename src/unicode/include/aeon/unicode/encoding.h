// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::unicode
{

namespace utf8
{

auto to_utf16(const std::string &str) -> std::wstring;

} // namespace utf8

namespace utf16
{

auto to_utf8(const std::wstring &str) -> std::string;

} // namespace utf16

} // namespace aeon::unicode
