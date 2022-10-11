// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <aeon/common/string_concepts.h>
#include <aeon/common/string_traits.h>
#include <aeon/common/string.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

namespace aeon::common::string_utils
{

/*!
 * Compare 2 strings case insensitive. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto iequals(const string_view &str1, const string_view &str2) noexcept -> bool;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto split(const string &str, const T delim, std::vector<string> &elements)
    -> std::vector<string> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto split(const string &str, const T delim) -> std::vector<string>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto splitsv(const string_view &str, const T delim, std::vector<string_view> &elements)
    -> std::vector<string_view>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Returns a vector of split elements.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto splitsv(const string_view &str, const T delim) -> std::vector<string_view>;

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void ltrim(string &str);

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void ltrimsv(string_view &str);

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void rtrim(string &str);

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void rtrimsv(string_view &str);

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void trim(string &str);

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
inline void trimsv(string_view &str);

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto ltrimmed(const string_view &str) -> string;

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto ltrimmedsv(const string_view &str) -> string_view;

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto rtrimmed(const string_view &str) -> string;

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto rtrimmedsv(const string_view &str) -> string_view;

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto trimmed(const string_view &str) -> string;

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
[[nodiscard]] inline auto trimmedsv(const string_view &str) -> string_view;

/*!
 * Get len characters from the left of the string.
 */
[[nodiscard]] inline auto left(const string_view &str, const string_view::size_type len) -> string;

/*!
 * Get len characters from the left of the string_view.
 */
[[nodiscard]] inline auto leftsv(const string_view &str, const string_view::size_type len) -> string_view;

/*!
 * Get len characters from the right of the string.
 */
[[nodiscard]] inline auto right(const string_view &str, const string_view::size_type len) -> string;

/*!
 * Get len characters from the right of the string_view.
 */
[[nodiscard]] inline auto rightsv(const string_view &str, const string_view::size_type len) -> string_view;

/*!
 * Strip len characters at the left of the string
 */
[[nodiscard]] inline auto stripped_left(const string_view &str, const string_view::size_type len) -> string;

/*!
 * Strip len characters at the left of the string_view
 */
[[nodiscard]] inline auto stripped_leftsv(const string_view &str, const string_view::size_type len) -> string_view;

/*!
 * Strip len characters at the right of the string
 */
[[nodiscard]] inline auto stripped_right(const string_view &str, const string_view::size_type len) -> string;

/*!
 * Strip len characters at the right of the string_view
 */
[[nodiscard]] inline auto stripped_rightsv(const string_view &str, const string_view::size_type len) -> string_view;

/*!
 * Strip len characters on both sides of the string.
 */
[[nodiscard]] inline auto stripped_both(const string_view &str, const string_view::size_type len) -> string;

/*!
 * Strip len characters on both sides of the string_view.
 */
[[nodiscard]] inline auto stripped_bothsv(const string_view &str, const string_view::size_type len) -> string_view;

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_left(const string_view &str, const T c) -> string;

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_leftsv(const string_view &str, const T c) -> string_view;

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_right(const string_view &str, const T c) -> string;

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_rightsv(const string_view &str, const T c) -> string_view;

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_both(const string_view &str, const T c) -> string;

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_bothsv(const string_view &str, const T c) -> string_view;

/*!
 * Strip len characters at the left of the string
 */
inline void strip_left(string &str, const string::size_type len);

/*!
 * Strip len characters at the left of the string_view
 */
inline void strip_leftsv(string_view &str, const string_view::size_type len);

/*!
 * Strip len characters at the right of the string
 */
inline void strip_right(string &str, const string::size_type len);

/*!
 * Strip len characters at the right of the string_view
 */
inline void strip_rightsv(string_view &str, const string_view::size_type len);

/*!
 * Strip len characters on both sides of the string.
 */
inline void strip_both(string &str, const string::size_type len);

/*!
 * Strip len characters on both sides of the string_view.
 */
inline void strip_bothsv(string_view &str, const string_view::size_type len);

/*!
 * Strip all characters equal to c on the left side of the string.
 */
inline void char_strip_left(string &str, const string::value_type c);

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
inline void char_strip_leftsv(string_view &str, const string_view::value_type c);

/*!
 * Strip all characters equal to c on the right side of the string.
 */
inline void char_strip_right(string &str, const string::value_type c);

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
inline void char_strip_rightsv(string_view &str, const string_view::value_type c);

/*!
 * Strip all characters equal to c on both sides of the string.
 */
inline void char_strip_both(string &str, const string::value_type c);

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
inline void char_strip_bothsv(string_view &str, const string_view::value_type c);

/*!
 * Replace all occurrences of a string with another string.
 */
inline void replace(string &str, const string_view &from, const string_view &to);

/*!
 * Replace all occurrences of a string with another string.
 */
[[nodiscard]] inline auto replace_copy(const string_view &str, const string_view &from, const string_view &to)
    -> string;

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
inline void to_lower(string &str);

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
[[nodiscard]] inline auto to_lower_copy(const string_view &str) -> string;

/*!
 * Convert the current string to uppercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
inline void to_upper(string &str);

/*!
 * Convert the current string to uppercase based to the locale settings
 */
[[nodiscard]] inline auto to_upper_copy(const string_view &str) -> string;

/*!
 * Check if a string begins with another string
 */
[[nodiscard]] inline auto begins_with(const string_view &str, const string_view &val) -> bool;

/*!
 * Check if a string begins with another string
 */
[[nodiscard]] inline auto ends_with(const string_view &str, const string_view &val) -> bool;

/*!
 * Check if the string "val" is found within "str".
 */
[[nodiscard]] inline auto contains(const string_view &str, const string_view &val) -> bool;

/*!
 * Check if the character c is found within "str".
 */
[[nodiscard]] inline auto contains(const string_view &str, const string_view::value_type c) -> bool;

/*!
 * Convert a character into a hex string.
 * For example: 'a' becomes "61".
 */
[[nodiscard]] auto char_to_hex(const char c) -> string;

/*
 * Convert a hex string into a char
 * For example: "61" becomes 'a'.
 */
[[nodiscard]] auto hex_to_char(const string &str) -> char;

/*!
 * Convert a string in HEX format ("0x1234") to an integer.
 */
template <typename T>
[[nodiscard]] inline auto hex_string_to_int(const string &str)
{
    T value;
    std::istringstream iss(str.str());
    iss >> std::hex >> value;
    return value;
}

template <>
[[nodiscard]] inline auto hex_string_to_int<std::uint8_t>(const string &str)
{
    int value;
    std::istringstream iss(str.str());
    iss >> std::hex >> value;
    return static_cast<std::uint8_t>(value);
}

/*!
 * Convert a value into HEX format (ie. 255 becomes "ff")
 */
template <typename T>
[[nodiscard]] inline auto int_to_hex_string(const T value) -> string
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << static_cast<std::int64_t>(value);
    return std::move(stream.str());
}

/*!
 * Convert a byte into HEX format (ie. 255 becomes "ff")
 */
[[nodiscard]] inline auto uint8_to_hex_string(const std::uint8_t value) noexcept -> const char *;

/*!
 * Construct a string_view from given iterators
 */
template <typename iterator_t>
[[nodiscard]] inline constexpr auto make_string_view(iterator_t begin, iterator_t end) noexcept
{
    using result_type = std::basic_string_view<typename std::iterator_traits<iterator_t>::value_type>;

    if (begin == end)
        return result_type{};

    return result_type{&*begin, static_cast<typename result_type::size_type>(
                                    std::max(std::distance(begin, end), typename result_type::difference_type{}))};
}

} // namespace aeon::common::string_utils

#include <aeon/common/impl/string_utils_impl.h>
