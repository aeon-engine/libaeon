// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/container.h>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

namespace aeon::common::string
{

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <typename T>
[[nodiscard]] inline auto split(const std::basic_string<T> &str, const T delim,
                                std::vector<std::basic_string<T>> &elements) -> std::vector<std::basic_string<T>> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
template <typename T>
[[nodiscard]] inline auto split(const std::basic_string<T> &str, const T delim) -> std::vector<std::basic_string<T>>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
template <typename T>
[[nodiscard]] inline auto splitsv(const std::basic_string_view<T> &str, const T delim,
                                  std::vector<std::basic_string_view<T>> &elements)
    -> std::vector<std::basic_string_view<T>>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Returns a vector of split elements.
 */
template <typename T>
[[nodiscard]] inline auto splitsv(const std::basic_string_view<T> &str, const T delim)
    -> std::vector<std::basic_string_view<T>>;

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void ltrim(std::basic_string<T> &str);

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void ltrimsv(std::basic_string_view<T> &str);

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void rtrim(std::basic_string<T> &str);

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void rtrimsv(std::basic_string_view<T> &str);

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void trim(std::basic_string<T> &str);

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
inline void trimsv(std::basic_string_view<T> &str);

/*!
 * Trim from the start of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto ltrimmed(const std::basic_string<T> &str) -> std::basic_string<T>;

/*!
 * Trim from the start of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto ltrimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>;

/*!
 * Trim from the ending of a string. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto rtrimmed(const std::basic_string<T> &str) -> std::basic_string<T>;

/*!
 * Trim from the ending of a string_view. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto rtrimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>;

/*!
 * Trim a string at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto trimmed(const std::basic_string<T> &str) -> std::basic_string<T>;

/*!
 * Trim a string_view at the start and end. Note that this function does not take encoding or locale into account for
 * performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto trimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>;

/*!
 * Get len characters from the left of the string.
 */
template <typename T>
[[nodiscard]] inline auto left(const std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
    -> std::basic_string<T>;

/*!
 * Get len characters from the left of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto leftsv(const std::basic_string_view<T> &str,
                                 const typename std::basic_string_view<T>::size_type len) -> std::basic_string_view<T>;

/*!
 * Get len characters from the right of the string.
 */
template <typename T>
[[nodiscard]] inline auto right(const std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
    -> std::basic_string<T>;

/*!
 * Get len characters from the right of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto rightsv(const std::basic_string_view<T> &str,
                                  const typename std::basic_string_view<T>::size_type len) -> std::basic_string_view<T>;

/*!
 * Strip len characters at the left of the string
 */
template <typename T>
[[nodiscard]] inline auto stripped_left(const std::basic_string<T> &str,
                                        const typename std::basic_string<T>::size_type len) -> std::basic_string<T>;

/*!
 * Strip len characters at the left of the string_view
 */
template <typename T>
[[nodiscard]] inline auto stripped_leftsv(const std::basic_string_view<T> &str,
                                          const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>;

/*!
 * Strip len characters at the right of the string
 */
template <typename T>
[[nodiscard]] inline auto stripped_right(const std::basic_string<T> &str,
                                         const typename std::basic_string<T>::size_type len) -> std::basic_string<T>;

/*!
 * Strip len characters at the right of the string_view
 */
template <typename T>
[[nodiscard]] inline auto stripped_rightsv(const std::basic_string_view<T> &str,
                                           const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>;

/*!
 * Strip len characters on both sides of the string.
 */
template <typename T>
[[nodiscard]] inline auto stripped_both(const std::basic_string<T> &str,
                                        const typename std::basic_string<T>::size_type len) -> std::basic_string<T>;

/*!
 * Strip len characters on both sides of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto stripped_bothsv(const std::basic_string_view<T> &str,
                                          const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>;

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_left(const std::basic_string<T> &str, const T c) -> std::basic_string<T>;

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_leftsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>;

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_right(const std::basic_string<T> &str, const T c) -> std::basic_string<T>;

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_rightsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>;

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_both(const std::basic_string<T> &str, const T c) -> std::basic_string<T>;

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
template <typename T>
[[nodiscard]] inline auto char_stripped_bothsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>;

/*!
 * Strip len characters at the left of the string
 */
template <typename T>
inline void strip_left(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len);

/*!
 * Strip len characters at the left of the string_view
 */
template <typename T>
inline void strip_leftsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len);

/*!
 * Strip len characters at the right of the string
 */
template <typename T>
inline void strip_right(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len);

/*!
 * Strip len characters at the right of the string_view
 */
template <typename T>
inline void strip_rightsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len);

/*!
 * Strip len characters on both sides of the string.
 */
template <typename T>
inline void strip_both(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len);

/*!
 * Strip len characters on both sides of the string_view.
 */
template <typename T>
inline void strip_bothsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len);

/*!
 * Strip all characters equal to c on the left side of the string.
 */
template <typename T>
inline void char_strip_left(std::basic_string<T> &str, const T c);

/*!
 * Strip all characters equal to c on the left side of the string_view.
 */
template <typename T>
inline void char_strip_leftsv(std::basic_string_view<T> &str, const T c);

/*!
 * Strip all characters equal to c on the right side of the string.
 */
template <typename T>
inline void char_strip_right(std::basic_string<T> &str, const T c);

/*!
 * Strip all characters equal to c on the right side of the string_view.
 */
template <typename T>
inline void char_strip_rightsv(std::basic_string_view<T> &str, const T c);

/*!
 * Strip all characters equal to c on both sides of the string.
 */
template <typename T>
inline void char_strip_both(std::basic_string<T> &str, const T c);

/*!
 * Strip all characters equal to c on both sides of the string_view.
 */
template <typename T>
inline void char_strip_bothsv(std::basic_string_view<T> &str, const T c);

/*!
 * Replace all occurrences of a string with another string.
 */
template <typename T>
inline void replace(std::basic_string<T> &str, const std::basic_string<T> &from, const std::basic_string<T> &to);

/*!
 * Replace all occurrences of a string with another string.
 */
template <typename T>
[[nodiscard]] inline auto replace_copy(const std::basic_string<T> &str, const std::basic_string<T> &from,
                                       const std::basic_string<T> &to) -> std::basic_string<T>;

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <typename T>
inline void to_lower(std::basic_string<T> &str);

/*!
 * Convert the current string to lowercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <typename T>
[[nodiscard]] inline auto to_lower_copy(const std::basic_string<T> &str) -> std::basic_string<T>;

/*!
 * Convert the current string to uppercase based to the locale settings. This function does not take character encoding
 * into account for performance reasons.
 */
template <typename T>
inline void to_upper(std::basic_string<T> &str);

/*!
 * Convert the current string to uppercase based to the locale settings
 */
template <typename T>
[[nodiscard]] inline auto to_upper_copy(const std::basic_string<T> &str) -> std::basic_string<T>;

/*!
 * Check if a string begins with another string
 */
template <typename T>
[[nodiscard]] inline auto begins_with(const std::basic_string<T> &str, const std::basic_string<T> &val) -> bool;

/*!
 * Check if a string_view begins with another string_view
 */
template <typename T>
[[nodiscard]] inline auto begins_withsv(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val)
    -> bool;

/*!
 * Check if a string begins with another string
 */
template <typename T>
[[nodiscard]] inline auto ends_with(const std::basic_string<T> &str, const std::basic_string<T> &val) -> bool;

/*!
 * Check if a string_view begins with another string_view
 */
template <typename T>
[[nodiscard]] inline auto ends_withsv(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val)
    -> bool;

/*!
 * Check if the string "val" is found within "str".
 */
template <typename T>
[[nodiscard]] inline auto contains(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val) -> bool;

/*!
 * Check if the character c is found within "str".
 */
template <typename T>
[[nodiscard]] inline auto contains(const std::basic_string_view<T> &str, const T c) -> bool;

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

} // namespace aeon::common::string

#include <aeon/common/impl/string_impl.h>
