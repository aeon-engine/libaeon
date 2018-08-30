/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <iomanip>

namespace aeon::common::string
{

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
auto split(const std::string &str, const char delim, std::vector<std::string> &elements) -> std::vector<std::string> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
auto split(const std::string &str, const char delim) -> std::vector<std::string>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
auto splitsv(const std::string_view &str, const char delim, std::vector<std::string_view> &elements)
    -> std::vector<std::string_view>;

/*!
 * Split/tokenize a string_view into a vector of string_views based on a delimiter.
 * Returns a vector of split elements.
 */
auto splitsv(const std::string_view &str, const char delim) -> std::vector<std::string_view>;

/*!
 * Trim from the start of a string
 */
void ltrim(std::string &str);

/*!
 * Trim from the start of a string_view
 */
void ltrimsv(std::string_view &str);

/*!
 * Trim from the ending of a string
 */
void rtrim(std::string &str);

/*!
 * Trim from the ending of a string_view
 */
void rtrimsv(std::string_view &str);

/*!
 * Trim a string at the start and end.
 */
void trim(std::string &str);

/*!
 * Trim a string_view at the start and end.
 */
void trimsv(std::string_view &str);

/*!
 * Trim from the start of a string
 */
auto ltrimmed(const std::string &str) -> std::string;

/*!
 * Trim from the start of a string_view
 */
auto ltrimmedsv(const std::string_view &str) -> std::string_view;

/*!
 * Trim from the ending of a string
 */
auto rtrimmed(const std::string &str) -> std::string;

/*!
 * Trim from the ending of a string_view
 */
auto rtrimmedsv(const std::string_view &str) -> std::string_view;

/*!
 * Trim a string at the start and end.
 */
auto trimmed(const std::string &str) -> std::string;

/*!
 * Trim a string_view at the start and end.
 */
auto trimmedsv(const std::string_view &str) -> std::string_view;

/*!
 * Get len characters from the left of the string.
 */
auto left(const std::string &str, const std::size_t len) -> std::string;

/*!
 * Get len characters from the left of the string_view.
 */
auto leftsv(const std::string_view &str, const std::size_t len) -> std::string_view;

/*!
 * Get len characters from the right of the string.
 */
auto right(const std::string &str, const std::size_t len) -> std::string;

/*!
 * Get len characters from the right of the string_view.
 */
auto rightsv(const std::string_view &str, const std::size_t len) -> std::string_view;

/*!
 * Strip len characters at the left of the string
 */
auto stripped_left(const std::string &str, const std::size_t len) -> std::string;

/*!
 * Strip len characters at the left of the string_view
 */
auto stripped_leftsv(const std::string_view &str, const std::size_t len) -> std::string_view;

/*!
 * Strip len characters at the right of the string
 */
auto stripped_right(const std::string &str, const std::size_t len) -> std::string;

/*!
 * Strip len characters at the right of the string_view
 */
auto stripped_rightsv(const std::string_view &str, const std::size_t len) -> std::string_view;

/*!
 * Strip len characters on both sides of the string.
 */
auto stripped_both(const std::string &str, const std::size_t len) -> std::string;

/*!
 * Strip len characters on both sides of the string_view.
 */
auto stripped_bothsv(const std::string_view &str, const std::size_t len) -> std::string_view;

/*!
 * Strip len characters at the left of the string
 */
void strip_left(std::string &str, const std::size_t len);

/*!
 * Strip len characters at the left of the string_view
 */
void strip_leftsv(std::string_view &str, const std::size_t len);

/*!
 * Strip len characters at the right of the string
 */
void strip_right(std::string &str, const std::size_t len);

/*!
 * Strip len characters at the right of the string_view
 */
void strip_rightsv(std::string_view &str, const std::size_t len);

/*!
 * Strip len characters on both sides of the string.
 */
void strip_both(std::string &str, const std::size_t len);

/*!
 * Strip len characters on both sides of the string_view.
 */
void strip_bothsv(std::string_view &str, const std::size_t len);

/*!
 * Convert standard argc and argv arguments into a vector of strings.
 */
auto args_to_vector(int argc, char *argv[]) -> std::vector<std::string>;

/*!
 * Replace all occurrences of a string with another string.
 */
void replace(std::string &str, const std::string &from, const std::string &to);

/*!
 * Replace all occurrences of a string with another string.
 */
auto replace_copy(const std::string &str, const std::string &from, const std::string &to) -> std::string;

/*!
 * Convert the current string to lowercase based to the locale settings
 */
void to_lower(std::string &str);

/*!
 * Convert the current string to lowercase based to the locale settings
 */
auto to_lower_copy(const std::string &str) -> std::string;

/*!
 * Convert the current string to uppercase based to the locale settings
 */
void to_upper(std::string &str);

/*!
 * Convert the current string to uppercase based to the locale settings
 */
auto to_upper_copy(const std::string &str) -> std::string;

/*!
 * Check if a string begins with another string
 */
auto begins_with(const std::string &str, const std::string &val) -> bool;

/*!
 * Check if a string_view begins with another string_view
 */
auto begins_withsv(const std::string_view &str, const std::string_view &val) -> bool;

/*!
 * Check if a string begins with another string
 */
auto ends_with(const std::string &str, const std::string &val) -> bool;

/*!
 * Check if a string_view begins with another string_view
 */
auto ends_withsv(const std::string_view &str, const std::string_view &val) -> bool;

/*!
 * Check if the string "val" is found within "str".
 */
auto contains(const std::string_view &str, const std::string_view &val) -> bool;

/*!
 * Convert a character into a hex string.
 * For example: 'a' becomes "61".
 */
auto char_to_hex(const char c) -> std::string;

/*
 * Convert a hex string into a char
 * For example: "61" becomes 'a'.
 */
auto hex_to_char(const std::string &str) -> char;

/*!
 * Convert a string in HEX format ("0x1234") to an integer.
 */
template <typename T>
inline auto hex_string_to_int(const std::string &str)
{
    T value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return value;
}

template <>
inline auto hex_string_to_int<std::uint8_t>(const std::string &str)
{
    int value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return static_cast<std::uint8_t>(value);
}

/*!
 * Convert a value into HEX format (ie. 255 becomes "FF")
 */
template <typename T>
inline auto int_to_hex_string(const T value) -> std::string
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << static_cast<std::int64_t>(value);
    return stream.str();
}

} // namespace aeon::common::string
