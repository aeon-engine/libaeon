// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <aeon/common/string_concepts.h>
#include <aeon/common/string_traits.h>
#include <string>
#include <string_view>
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
template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto iequals(const T &str1, const U &str2) noexcept -> bool;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto split(const T &str, const char_type<T> delim, std::vector<basic_string_type<T>> &elements)
    -> std::vector<basic_string_type<T>> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto split(const T &str, const char_type<T> delim) -> std::vector<basic_string_type<T>>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto splitsv(const T &str, const char_type<T> delim,
                                  std::vector<basic_string_view_type<T>> &elements)
    -> std::vector<basic_string_view_type<T>>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Returns a vector of split elements.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto splitsv(const T &str, const char_type<T> delim) -> std::vector<basic_string_view_type<T>>;

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::basic_string T>
inline void ltrim(T &str);

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
inline void ltrimsv(T &str);

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::basic_string T>
inline void rtrim(T &str);

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
inline void rtrimsv(T &str);

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::basic_string T>
inline void trim(T &str);

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
inline void trimsv(T &str);

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto ltrimmed(const T &str) -> basic_string_type<T>;

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto ltrimmedsv(const T &str) -> basic_string_view_type<T>;

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto rtrimmed(const T &str) -> basic_string_type<T>;

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto rtrimmedsv(const T &str) -> basic_string_view_type<T>;

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto trimmed(const T &str) -> basic_string_type<T>;

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto trimmedsv(const T &str) -> basic_string_view_type<T>;

/*!
 * Get len characters from the left of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto left(const T &str, const size_type<T> len) -> basic_string_type<T>;

/*!
 * Get len characters from the left of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto leftsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>;

/*!
 * Get len characters from the right of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto right(const T &str, const size_type<T> len) -> basic_string_type<T>;

/*!
 * Get len characters from the right of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto rightsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>;

/*!
 * Strip len characters at the left of the string
 */
template <concepts::string_like T>
[[nodiscard]] inline auto stripped_left(const T &str, const size_type<T> len) -> basic_string_type<T>;

/*!
 * Strip len characters at the left of the string_view
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_leftsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>;

/*!
 * Strip len characters at the right of the string
 */
template <concepts::string_like T>
[[nodiscard]] inline auto stripped_right(const T &str, const size_type<T> len) -> basic_string_type<T>;

/*!
 * Strip len characters at the right of the string_view
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_rightsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>;

/*!
 * Strip len characters on both sides of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto stripped_both(const T &str, const size_type<T> len) -> basic_string_type<T>;

/*!
 * Strip len characters on both sides of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_bothsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>;

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_left(const T &str, const char_type<T> c) -> basic_string_type<T>;

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_leftsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>;

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_right(const T &str, const char_type<T> c) -> basic_string_type<T>;

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_rightsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>;

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_both(const T &str, const char_type<T> c) -> basic_string_type<T>;

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_bothsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>;

/*!
 * Strip len characters at the left of the string
 */
template <concepts::basic_string T>
inline void strip_left(T &str, const size_type<T> len);

/*!
 * Strip len characters at the left of the string_view
 */
template <concepts::basic_string_view T>
inline void strip_leftsv(T &str, const size_type<T> len);

/*!
 * Strip len characters at the right of the string
 */
template <concepts::basic_string T>
inline void strip_right(T &str, const size_type<T> len);

/*!
 * Strip len characters at the right of the string_view
 */
template <concepts::basic_string_view T>
inline void strip_rightsv(T &str, const size_type<T> len);

/*!
 * Strip len characters on both sides of the string.
 */
template <concepts::basic_string T>
inline void strip_both(T &str, const size_type<T> len);

/*!
 * Strip len characters on both sides of the string_view.
 */
template <concepts::basic_string_view T>
inline void strip_bothsv(T &str, const size_type<T> len);

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <concepts::basic_string T>
inline void char_strip_left(T &str, const char_type<T> c);

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
template <concepts::basic_string_view T>
inline void char_strip_leftsv(T &str, const char_type<T> c);

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <concepts::basic_string T>
inline void char_strip_right(T &str, const char_type<T> c);

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
template <concepts::basic_string_view T>
inline void char_strip_rightsv(T &str, const char_type<T> c);

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <concepts::basic_string T>
inline void char_strip_both(T &str, const char_type<T> c);

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
template <concepts::basic_string_view T>
inline void char_strip_bothsv(T &str, const char_type<T> c);

/*!
 * Replace all occurrences of a string with another string.
 */
template <concepts::basic_string T, concepts::string_view_like U, concepts::string_view_like V>
inline void replace(T &str, const U &from, const V &to);

/*!
 * Replace all occurrences of a string with another string.
 */
template <concepts::string_view_like T, concepts::string_view_like U, concepts::string_view_like V>
[[nodiscard]] inline auto replace_copy(const T &str, const U &from, const V &to) -> basic_string_type<T>;

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <concepts::basic_string T>
inline void to_lower(T &str);

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto to_lower_copy(const T &str) -> basic_string_type<T>;

/*!
 * Convert the current string to uppercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <concepts::basic_string T>
inline void to_upper(T &str);

/*!
 * Convert the current string to uppercase based to the locale settings
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto to_upper_copy(const T &str) -> basic_string_type<T>;

/*!
 * Check if a string begins with another string
 */
template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto begins_with(const T &str, const U &val) -> bool;

/*!
 * Check if a string begins with another string
 */
template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto ends_with(const T &str, const U &val) -> bool;

/*!
 * Check if the string "val" is found within "str".
 */
template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto contains(const T &str, const U &val) -> bool;

/*!
 * Check if the character c is found within "str".
 */
template <concepts::string_view_like T>
[[nodiscard]] inline auto contains(const T &str, const char_type<T> c) -> bool;

/*!
 * Convert a character into a hex string.
 * For example: 'a' becomes "61".
 */
[[nodiscard]] auto char_to_hex(const char c) -> std::string;

/*
 * Convert a hex string into a char
 * For example: "61" becomes 'a'.
 */
[[nodiscard]] auto hex_to_char(const std::string &str) -> char;

/*!
 * Convert a string in HEX format ("0x1234") to an integer.
 */
template <typename T>
[[nodiscard]] inline auto hex_string_to_int(const std::string &str)
{
    T value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return value;
}

template <>
[[nodiscard]] inline auto hex_string_to_int<std::uint8_t>(const std::string &str)
{
    int value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return static_cast<std::uint8_t>(value);
}

/*!
 * Convert a value into HEX format (ie. 255 becomes "ff")
 */
template <typename T>
[[nodiscard]] inline auto int_to_hex_string(const T value) -> std::string
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << static_cast<std::int64_t>(value);
    return stream.str();
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
