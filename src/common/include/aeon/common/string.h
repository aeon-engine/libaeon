/*
 * Copyright (c) 2012-2017 Robin Degen
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
#include <vector>
#include <sstream>

namespace aeon
{
namespace common
{
namespace string
{

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
auto split(const std::string &str, char delim, std::vector<std::string> &elements) -> std::vector<std::string> &;

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
auto split(const std::string &str, char delim) -> std::vector<std::string>;

/*!
 * Trim from the start of a string
 */
void ltrim(std::string &str);

/*!
 * Trim from the ending of a string
 */
void rtrim(std::string &str);

/*!
 * Trim a string at the start and end.
 */
void trim(std::string &str);

/*!
 * Trim from the start of a string
 */
auto ltrimmed(const std::string &str) -> std::string;

/*!
 * Trim from the ending of a string
 */
auto rtrimmed(const std::string &str) -> std::string;

/*!
 * Trim a string at the start and end.
 */
auto trimmed(const std::string &str) -> std::string;

/*!
 * Get len characters from the left of the string.
 */
auto left(const std::string &str, std::size_t len) -> std::string;

/*!
 * Get len characters from the right of the string.
 */
auto right(const std::string &str, std::size_t len) -> std::string;

/*!
 * Trim len characters at the left of the string
 */
auto strip_left(const std::string &str, std::size_t len) -> std::string;

/*!
 * Trim len characters at the right of the string
 */
auto strip_right(const std::string &str, std::size_t len) -> std::string;

/*!
 * Tren len characters on both sides of the string.
 */
auto strip_both(const std::string &str, std::size_t len) -> std::string;

/*!
 * Convert standard argc and argv arguments into a vector of strings.
 */
auto args_to_vector(int argc, char *argv[]) -> std::vector<std::string>;

/*!
 * Replace all occurances of a string with another string.
 */
void replace(std::string &str, const std::string &from, const std::string &to);

/*!
 * Convert the current string to lowercase based to the locale settings
 */
auto to_lower(const std::string &str) -> std::string;

/*!
 * Convert the current string to uppercase based to the locale settings
 */
auto to_upper(const std::string &str) -> std::string;

/*!
 * Check if a string begins with another string
 */
auto begins_with(const std::string &str, const std::string &val) -> bool;

/*!
 * Check if a string begins with another string
 */
auto ends_with(const std::string &str, const std::string &val) -> bool;

/*!
 * Convert a string in HEX format ("0x1234") to an integer.
 */
template <typename T>
auto hex_string_to_int(const std::string &str)
{
    T value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return value;
}

} // namespace string
} // namespace common
} // namespace aeon
