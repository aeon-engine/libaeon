// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <string>
#include <type_traits>

namespace aeon::common::concepts
{

/*!
 * The given type must be any of std::string, std::wstring, std::u8string, std::u16string or std::u32string
 */
template <typename T>
concept basic_string = std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> ||
    std::is_same_v<T, std::u8string> || std::is_same_v<T, std::u16string> || std::is_same_v<T, std::u32string>;

/*!
 * The given type must be any of std::string, std::wstring, std::u8string, std::u16string or std::u32string or
 * convertible to one of them.
 */
template <typename T>
concept string_like = basic_string<T> || std::is_convertible_v<T, std::string> ||
    std::is_convertible_v<T, std::wstring> || std::is_convertible_v<T, std::u8string> ||
    std::is_convertible_v<T, std::u16string> || std::is_convertible_v<T, std::u32string>;

/*!
 * The given type must be any of std::string_view, std::wstring_view, std::u8string_view, std::u16string_view or
 * std::u32string_view
 */
template <typename T>
concept basic_string_view = std::is_same_v<T, std::string_view> || std::is_same_v<T, std::wstring_view> ||
    std::is_same_v<T, std::u8string_view> || std::is_same_v<T, std::u16string_view> ||
    std::is_same_v<T, std::u32string_view>;

/*!
 * The given type must be any of std::string_view, std::wstring_view, std::u8string_view, std::u16string_view or
 * std::u32string_view or convertible to one of them.
 */
template <typename T>
concept string_view_like = basic_string<T> || std::is_convertible_v<T, std::string_view> ||
    std::is_convertible_v<T, std::wstring_view> || std::is_convertible_v<T, std::u8string_view> ||
    std::is_convertible_v<T, std::u16string_view> || std::is_convertible_v<T, std::u32string_view>;

} // namespace aeon::common::concepts
