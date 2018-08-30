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

#include <aeon/common/string.h>
#include <aeon/common/literals.h>
#include <aeon/common/container.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace aeon::common::string
{

auto split(const std::string &str, const char delim, std::vector<std::string> &elements) -> std::vector<std::string> &
{
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elements.push_back(item);
    }

    return elements;
}

auto split(const std::string &str, const char delim) -> std::vector<std::string>
{
    std::vector<std::string> elements;
    split(str, delim, elements);
    return elements;
}

auto splitsv(const std::string_view &str, const char delim, std::vector<std::string_view> &elements)
    -> std::vector<std::string_view>
{
    auto start = 0_size_t;
    auto pos = str.find_first_of(delim, start);

    while (pos != std::string_view::npos)
    {
        elements.push_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }

    if (start < str.length())
        elements.push_back(str.substr(start, str.length() - start));

    return elements;
}

auto splitsv(const std::string_view &str, const char delim) -> std::vector<std::string_view>
{
    std::vector<std::string_view> elements;
    splitsv(str, delim, elements);
    return elements;
}

void ltrim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](const int c) { return !std::isspace(c); }));
}

void ltrimsv(std::string_view &str)
{
    str.remove_prefix(
        container::count_until(std::begin(str), std::end(str), [](const int c) { return !std::isspace(c); }));
}

void rtrim(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](const int c) { return !std::isspace(c); }).base(), str.end());
}

void rtrimsv(std::string_view &str)
{
    str.remove_suffix(
        container::count_until(std::rbegin(str), std::rend(str), [](const int c) { return !std::isspace(c); }));
}

void trim(std::string &str)
{
    ltrim(str);
    rtrim(str);
}

void trimsv(std::string_view &str)
{
    ltrimsv(str);
    rtrimsv(str);
}

auto ltrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    ltrim(trimstr);
    return trimstr;
}

auto ltrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    ltrimsv(trimstr);
    return trimstr;
}

auto rtrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    rtrim(trimstr);
    return trimstr;
}

auto rtrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    rtrimsv(trimstr);
    return trimstr;
}

auto trimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    trim(trimstr);
    return trimstr;
}

auto trimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    trimsv(trimstr);
    return trimstr;
}

auto left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, len);
}

auto leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, len);
}

auto right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(str.size() - len);
}

auto rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(str.size() - len);
}

auto strip_left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len);
}

auto strip_leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len);
}

auto strip_right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, str.size() - len);
}

auto strip_rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, str.size() - len);
}

auto strip_both(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len, str.size() - len - len);
}

auto strip_bothsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len, str.size() - len - len);
}

auto args_to_vector(int argc, char *argv[]) -> std::vector<std::string>
{
    std::vector<std::string> vec;
    vec.reserve(argc);

    for (int i = 0; i < argc; ++i)
    {
        vec.emplace_back(argv[i]);
    }

    return vec;
}

void replace(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;

    auto start_pos = 0_size_t;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

auto replace_copy(const std::string &str, const std::string &from, const std::string &to) -> std::string
{
    std::string copy = str;
    replace(copy, from, to);
    return copy;
}

auto to_lower(const std::string &str) -> std::string
{
    const auto to_lower_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).tolower(c);
    };

    std::string result;
    std::transform(str.begin(), str.end(), std::back_inserter(result), to_lower_internal);
    return result;
}

auto to_upper(const std::string &str) -> std::string
{
    const auto to_upper_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).toupper(c);
    };

    std::string result;
    std::transform(str.begin(), str.end(), std::back_inserter(result), to_upper_internal);
    return result;
}

auto begins_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return left(str, val.size()) == val;
}

auto begins_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return leftsv(str, val.size()) == val;
}

auto ends_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return right(str, val.size()) == val;
}

auto ends_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return rightsv(str, val.size()) == val;
}

auto contains(const std::string_view &str, const std::string_view &val) -> bool
{
    return str.find(val) != std::string::npos;
}

auto char_to_hex(const char c) -> std::string
{
    std::ostringstream ss;
    ss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<short>(c & 0xff);
    return ss.str();
}

auto hex_to_char(const std::string &str) -> char
{
    if (str.empty())
        return 0;

    std::istringstream in(str);

    short c = 0;
    in >> std::hex >> c;

    if (in.fail())
        throw std::runtime_error("stream decode failure");

    return static_cast<char>(c & 0xff);
}

} // namespace aeon::common::string
