// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/utf8_utils.h>

namespace aeon::common::utf8
{

inline auto to_utf8_string(const char32_t *str) -> std::string;

inline auto to_wstring(const std::string_view &str) -> std::wstring;

} // namespace aeon::common::utf8

#include <aeon/common/impl/utf8_convert_impl.h>
