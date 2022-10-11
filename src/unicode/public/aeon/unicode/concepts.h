// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <type_traits>
#include <string_view>

namespace aeon::unicode::concepts
{

template <typename T>
concept utf_string_view = std::is_same_v<T, common::string_view> || std::is_same_v<T, std::string_view> ||
                          std::is_same_v<T, std::u8string_view> || std::is_same_v<T, std::u16string_view> ||
                          std::is_same_v<T, std::u32string_view>;

} // namespace aeon::unicode::concepts
