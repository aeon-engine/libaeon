// Copyright (c) 2012-2019 Robin Degen

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

[[nodiscard]] auto split(const std::string &str, const char delim, std::vector<std::string> &elements)
    -> std::vector<std::string> &
{
    std::stringstream ss{str};
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elements.emplace_back(item);
    }

    return elements;
}

[[nodiscard]] auto split(const std::string &str, const char delim) -> std::vector<std::string>
{
    std::vector<std::string> elements;
    split(str, delim, elements);
    return elements;
}

[[nodiscard]] auto splitsv(const std::string_view &str, const char delim, std::vector<std::string_view> &elements)
    -> std::vector<std::string_view>
{
    auto start = 0_size_t;
    auto pos = str.find_first_of(delim, start);

    while (pos != std::string_view::npos)
    {
        elements.emplace_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }

    if (start < str.length())
        elements.emplace_back(str.substr(start, str.length() - start));

    return elements;
}

[[nodiscard]] auto splitsv(const std::string_view &str, const char delim) -> std::vector<std::string_view>
{
    std::vector<std::string_view> elements;
    splitsv(str, delim, elements);
    return elements;
}

void ltrim(std::string &str)
{
    str.erase(std::begin(str),
              std::find_if(std::begin(str), std::end(str), [](const int c) { return !std::isspace(c); }));
}

void ltrimsv(std::string_view &str)
{
    str.remove_prefix(
        container::count_until(std::begin(str), std::end(str), [](const int c) { return !std::isspace(c); }));
}

void rtrim(std::string &str)
{
    str.erase(std::find_if(std::rbegin(str), std::rend(str), [](const int c) { return !std::isspace(c); }).base(),
              std::end(str));
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

[[nodiscard]] auto ltrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    ltrim(trimstr);
    return trimstr;
}

[[nodiscard]] auto ltrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    ltrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] auto rtrimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    rtrim(trimstr);
    return trimstr;
}

[[nodiscard]] auto rtrimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    rtrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] auto trimmed(const std::string &str) -> std::string
{
    auto trimstr = str;
    trim(trimstr);
    return trimstr;
}

[[nodiscard]] auto trimmedsv(const std::string_view &str) -> std::string_view
{
    auto trimstr = str;
    trimsv(trimstr);
    return trimstr;
}

[[nodiscard]] auto left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, len);
}

[[nodiscard]] auto leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, len);
}

[[nodiscard]] auto right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(str.size() - len);
}

[[nodiscard]] auto rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(str.size() - len);
}

[[nodiscard]] auto stripped_left(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len);
}

[[nodiscard]] auto stripped_leftsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len);
}

[[nodiscard]] auto stripped_right(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(0, str.size() - len);
}

[[nodiscard]] auto stripped_rightsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(0, str.size() - len);
}

[[nodiscard]] auto stripped_both(const std::string &str, const std::size_t len) -> std::string
{
    return str.substr(len, str.size() - len - len);
}

[[nodiscard]] auto stripped_bothsv(const std::string_view &str, const std::size_t len) -> std::string_view
{
    return str.substr(len, str.size() - len - len);
}

void strip_left(std::string &str, const std::size_t len)
{
    str = stripped_left(str, len);
}

void strip_leftsv(std::string_view &str, const std::size_t len)
{
    str = stripped_leftsv(str, len);
}

void strip_right(std::string &str, const std::size_t len)
{
    str = stripped_right(str, len);
}

void strip_rightsv(std::string_view &str, const std::size_t len)
{
    str = stripped_rightsv(str, len);
}

void strip_both(std::string &str, const std::size_t len)
{
    str = stripped_both(str, len);
}

void strip_bothsv(std::string_view &str, const std::size_t len)
{
    str = stripped_bothsv(str, len);
}

[[nodiscard]] auto args_to_vector(int argc, char *argv[]) -> std::vector<std::string>
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

[[nodiscard]] auto replace_copy(const std::string &str, const std::string &from, const std::string &to) -> std::string
{
    std::string copy = str;
    replace(copy, from, to);
    return copy;
}

void to_lower(std::string &str)
{
    const auto to_lower_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).tolower(c);
    };

    std::transform(std::begin(str), std::end(str), std::begin(str), to_lower_internal);
}

[[nodiscard]] auto to_lower_copy(const std::string &str) -> std::string
{
    std::string result = str;
    to_lower(result);
    return result;
}

void to_upper(std::string &str)
{
    const auto to_upper_internal = [](const char c) {
        return std::use_facet<std::ctype<char>>(std::locale()).toupper(c);
    };

    std::transform(std::begin(str), std::end(str), std::begin(str), to_upper_internal);
}

[[nodiscard]] auto to_upper_copy(const std::string &str) -> std::string
{
    std::string result = str;
    to_upper(result);
    return result;
}

[[nodiscard]] auto begins_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return left(str, val.size()) == val;
}

[[nodiscard]] auto begins_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return leftsv(str, val.size()) == val;
}

[[nodiscard]] auto ends_with(const std::string &str, const std::string &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return right(str, val.size()) == val;
}

[[nodiscard]] auto ends_withsv(const std::string_view &str, const std::string_view &val) -> bool
{
    if (str.size() < val.size())
        return false;

    return rightsv(str, val.size()) == val;
}

[[nodiscard]] auto contains(const std::string_view &str, const std::string_view &val) -> bool
{
    return str.find(val) != std::string::npos;
}

[[nodiscard]] auto contains(const std::string_view &str, const char c) -> bool
{
    return str.find(c) != std::string::npos;
}

[[nodiscard]] auto char_to_hex(const char c) -> std::string
{
    std::ostringstream ss;
    ss << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << static_cast<short>(c & 0xff);
    return ss.str();
}

[[nodiscard]] auto hex_to_char(const std::string &str) -> char
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
