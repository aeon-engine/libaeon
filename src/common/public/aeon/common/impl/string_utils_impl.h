// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <cstdint>
#include <array>
#include <locale>

namespace aeon::common::string_utils
{

[[nodiscard]] inline auto iequals(const string_view &str1, const string_view &str2) noexcept -> bool
{
    return std::equal(std::cbegin(str1), std::cend(str1), std::cbegin(str2), std::cend(str2),
                      [](const auto a, const auto b) { return std::tolower(a) == std::tolower(b); });
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto split(const string &str, const T delim, std::vector<string> &elements)
    -> std::vector<string> &
{
    std::basic_stringstream ss{str.str()};
    string item;

    while (std::getline(ss, item.str(), static_cast<char>(delim)))
    {
        elements.emplace_back(item);
    }

    return elements;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto split(const string &str, const T delim) -> std::vector<string>
{
    std::vector<string> elements;
    return split(str, delim, elements);
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto splitsv(const string_view &str, const T delim, std::vector<string_view> &elements)
    -> std::vector<string_view>
{
    auto start = string_view::size_type{};
    auto pos = str.find_first_of(delim, start);

    while (pos != string_view::npos)
    {
        elements.emplace_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }

    if (start < std::size(str))
        elements.emplace_back(str.substr(start, std::size(str) - start));

    return elements;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto splitsv(const string_view &str, const T delim) -> std::vector<string_view>
{
    std::vector<string_view> elements;
    return splitsv(str, delim, elements);
}

inline void ltrim(string &str)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str),
                                            [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void ltrimsv(string_view &str)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void rtrim(string &str)
{
    str.erase(
        std::find_if(std::rbegin(str), std::rend(str), [](const auto c) { return !std::isspace(static_cast<int>(c)); })
            .base(),
        std::end(str));
}

inline void rtrimsv(string_view &str)
{
    str.remove_suffix(container::count_until(std::crbegin(str), std::crend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

inline void trim(string &str)
{
    ltrim(str);
    rtrim(str);
}

inline void trimsv(string_view &str)
{
    ltrimsv(str);
    rtrimsv(str);
}

[[nodiscard]] inline auto ltrimmed(const string_view &str) -> string
{
    auto trimstr = string{str};
    ltrim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto ltrimmedsv(const string_view &str) -> string_view
{
    auto trimstr = string_view{str};
    ltrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto rtrimmed(const string_view &str) -> string
{
    auto trimstr = string{str};
    rtrim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto rtrimmedsv(const string_view &str) -> string_view
{
    auto trimstr = string_view{str};
    rtrimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto trimmed(const string_view &str) -> string
{
    auto trimstr = string{str};
    trim(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto trimmedsv(const string_view &str) -> string_view
{
    auto trimstr = string_view{str};
    trimsv(trimstr);
    return trimstr;
}

[[nodiscard]] inline auto left(const string_view &str, const string_view::size_type len) -> string
{
    return string{leftsv(str, len)};
}

[[nodiscard]] inline auto leftsv(const string_view &str, const string_view::size_type len) -> string_view
{
    return str.substr(0, len);
}

[[nodiscard]] inline auto right(const string_view &str, const string_view::size_type len) -> string
{
    return string{rightsv(str, len)};
}

[[nodiscard]] inline auto rightsv(const string_view &str, const string_view::size_type len) -> string_view
{
    return str.substr(std::size(str) - len);
}

[[nodiscard]] inline auto stripped_left(const string_view &str, const string_view::size_type len) -> string
{
    return string{stripped_leftsv(str, len)};
}

[[nodiscard]] inline auto stripped_leftsv(const string_view &str, const string_view::size_type len) -> string_view
{
    return str.substr(len);
}

[[nodiscard]] inline auto stripped_right(const string_view &str, const string_view::size_type len) -> string
{
    return string{stripped_rightsv(str, len)};
}

[[nodiscard]] inline auto stripped_rightsv(const string_view &str, const string_view::size_type len) -> string_view
{
    return str.substr(0, std::size(str) - len);
}

[[nodiscard]] inline auto stripped_both(const string_view &str, const string_view::size_type len) -> string
{
    return string{stripped_bothsv(str, len)};
}

[[nodiscard]] inline auto stripped_bothsv(const string_view &str, const string_view::size_type len) -> string_view
{
    return str.substr(len, std::size(str) - len - len);
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_left(const string_view &str, const T c) -> string
{
    auto stripstr = string{str};
    char_strip_left(stripstr, c);
    return stripstr;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_leftsv(const string_view &str, const T c) -> string_view
{
    auto stripstr = string_view{str};
    char_strip_leftsv(stripstr, c);
    return stripstr;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_right(const string_view &str, const T c) -> string
{
    auto stripstr = string{str};
    char_strip_right(stripstr, c);
    return stripstr;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_rightsv(const string_view &str, const T c) -> string_view
{
    auto stripstr = string_view{str};
    char_strip_rightsv(stripstr, c);
    return stripstr;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_both(const string_view &str, const T c) -> string
{
    auto stripstr = string{str};
    char_strip_both(stripstr, c);
    return stripstr;
}

template <concepts::utf8_character_types T>
[[nodiscard]] inline auto char_stripped_bothsv(const string_view &str, const T c) -> string_view
{
    auto stripstr = string_view{str};
    char_strip_bothsv(stripstr, c);
    return stripstr;
}

inline void strip_left(string &str, const string::size_type len)
{
    str = stripped_left(str, len);
}

inline void strip_leftsv(string_view &str, const string_view::size_type len)
{
    str = stripped_leftsv(str, len);
}

inline void strip_right(string &str, const string::size_type len)
{
    str = stripped_right(str, len);
}

inline void strip_rightsv(string_view &str, const string_view::size_type len)
{
    str = stripped_rightsv(str, len);
}

inline void strip_both(string &str, const string::size_type len)
{
    str = stripped_both(str, len);
}

inline void strip_bothsv(string_view &str, const string_view::size_type len)
{
    str = stripped_bothsv(str, len);
}

inline void char_strip_left(string &str, const string::value_type c)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

inline void char_strip_leftsv(string_view &str, const string_view::value_type c)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

inline void char_strip_right(string &str, const string::value_type c)
{
    str.erase(std::find_if(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }).base(),
              std::end(str));
}

inline void char_strip_rightsv(string_view &str, const string_view::value_type c)
{
    str.remove_suffix(
        container::count_until(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }));
}

inline void char_strip_both(string &str, const string::value_type c)
{
    char_strip_left(str, c);
    char_strip_right(str, c);
}

inline void char_strip_bothsv(string_view &str, const string_view::value_type c)
{
    char_strip_leftsv(str, c);
    char_strip_rightsv(str, c);
}

inline void replace(string &str, const string_view &from, const string_view &to)
{
    if (std::empty(from))
        return;

    auto start_pos = string::size_type{};
    while ((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, std::size(from), to);
        start_pos += std::size(to);
    }
}

[[nodiscard]] inline auto replace_copy(const string_view &str, const string_view &from, const string_view &to) -> string
{
    auto copy = string{str};
    replace(copy, from, to);
    return copy;
}

inline void to_lower(string &str)
{
    const auto to_lower_internal = [](const auto c)
    { return std::use_facet<std::ctype<string::value_type>>(std::locale()).tolower(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_lower_internal);
}

[[nodiscard]] inline auto to_lower_copy(const string_view &str) -> string
{
    auto result = string{str};
    to_lower(result);
    return result;
}

inline void to_upper(string &str)
{
    const auto to_upper_internal = [](const auto c)
    { return std::use_facet<std::ctype<string::value_type>>(std::locale()).toupper(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_upper_internal);
}

[[nodiscard]] inline auto to_upper_copy(const string_view &str) -> string
{
    auto result = string{str};
    to_upper(result);
    return result;
}

[[nodiscard]] inline auto begins_with(const string_view &str, const string_view &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return leftsv(str, std::size(val)) == val;
}

[[nodiscard]] inline auto ends_with(const string_view &str, const string_view &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return rightsv(str, std::size(val)) == val;
}

[[nodiscard]] inline auto contains(const string_view &str, const string_view &val) -> bool
{
    return str.find(val) != string_view::npos;
}

[[nodiscard]] inline auto contains(const string_view &str, const string_view::value_type c) -> bool
{
    return str.find(c) != string_view::npos;
}

[[nodiscard]] inline auto uint8_to_hex_string(const std::uint8_t value) noexcept -> const char *
{
    static const std::array<const char *, 256> hex_lookup{
        "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f", "10", "11",
        "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20", "21", "22", "23",
        "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f", "30", "31", "32", "33", "34", "35",
        "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f", "40", "41", "42", "43", "44", "45", "46", "47",
        "48", "49", "4a", "4b", "4c", "4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
        "5a", "5b", "5c", "5d", "5e", "5f", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b",
        "6c", "6d", "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d",
        "7e", "7f", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
        "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f", "a0", "a1",
        "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af", "b0", "b1", "b2", "b3",
        "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf", "c0", "c1", "c2", "c3", "c4", "c5",
        "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
        "d8", "d9", "da", "db", "dc", "dd", "de", "df", "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9",
        "ea", "eb", "ec", "ed", "ee", "ef", "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb",
        "fc", "fd", "fe", "ff"};
    return hex_lookup[value];
}

} // namespace aeon::common::string_utils
