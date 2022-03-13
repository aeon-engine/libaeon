// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <cstdint>
#include <array>
#include <locale>

namespace aeon::common::string_utils
{

template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto iequals(const T &str1, const U &str2) noexcept -> bool
{
    const auto str1_view = basic_string_view_type<T>{str1};
    const auto str2_view = basic_string_view_type<U>{str2};

    return std::equal(std::cbegin(str1_view), std::cend(str1_view), std::cbegin(str2_view), std::cend(str2_view),
                      [](const auto a, const auto b) { return std::tolower(a) == std::tolower(b); });
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto split(const T &str, const char_type<T> delim, std::vector<basic_string_type<T>> &elements)
    -> std::vector<basic_string_type<T>> &
{
    std::basic_stringstream ss{str};
    basic_string_type<T> item;

    while (std::getline(ss, item, delim))
    {
        elements.emplace_back(item);
    }

    return elements;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto split(const T &str, const char_type<T> delim) -> std::vector<basic_string_type<T>>
{
    std::vector<basic_string_type<T>> elements;
    return split(str, delim, elements);
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto splitsv(const T &str, const char_type<T> delim,
                                  std::vector<basic_string_view_type<T>> &elements)
    -> std::vector<basic_string_view_type<T>>
{
    auto start = size_type<T>{};
    auto str_view = basic_string_view_type<T>{str};
    auto pos = str_view.find_first_of(delim, start);

    while (pos != basic_string_view_type<T>::npos)
    {
        elements.emplace_back(str_view.substr(start, pos - start));
        start = pos + 1;
        pos = str_view.find_first_of(delim, start);
    }

    if (start < str.length())
        elements.emplace_back(str_view.substr(start, str_view.length() - start));

    return elements;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto splitsv(const T &str, const char_type<T> delim) -> std::vector<basic_string_view_type<T>>
{
    std::vector<basic_string_view_type<T>> elements;
    return splitsv(str, delim, elements);
}

template <concepts::basic_string T>
inline void ltrim(T &str)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str),
                                            [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

template <concepts::string_view_like T>
inline void ltrimsv(T &str)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

template <concepts::basic_string T>
inline void rtrim(T &str)
{
    str.erase(std::find_if(std::crbegin(str), std::crend(str),
                           [](const auto c) { return !std::isspace(static_cast<int>(c)); })
                  .base(),
              std::end(str));
}

template <concepts::string_view_like T>
inline void rtrimsv(T &str)
{
    str.remove_suffix(container::count_until(std::crbegin(str), std::crend(str),
                                             [](const auto c) { return !std::isspace(static_cast<int>(c)); }));
}

template <concepts::basic_string T>
inline void trim(T &str)
{
    ltrim(str);
    rtrim(str);
}

template <concepts::string_view_like T>
inline void trimsv(T &str)
{
    ltrimsv(str);
    rtrimsv(str);
}

template <concepts::string_like T>
[[nodiscard]] inline auto ltrimmed(const T &str) -> basic_string_type<T>
{
    auto trimstr = basic_string_type<T>{str};
    ltrim(trimstr);
    return trimstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto ltrimmedsv(const T &str) -> basic_string_view_type<T>
{
    auto trimstr = basic_string_view_type<T>{str};
    ltrimsv(trimstr);
    return trimstr;
}

template <concepts::string_like T>
[[nodiscard]] inline auto rtrimmed(const T &str) -> basic_string_type<T>
{
    auto trimstr = basic_string_type<T>{str};
    rtrim(trimstr);
    return trimstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto rtrimmedsv(const T &str) -> basic_string_view_type<T>
{
    auto trimstr = basic_string_view_type<T>{str};
    rtrimsv(trimstr);
    return trimstr;
}

template <concepts::string_like T>
[[nodiscard]] inline auto trimmed(const T &str) -> basic_string_type<T>
{
    auto trimstr = basic_string_type<T>{str};
    trim(trimstr);
    return trimstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto trimmedsv(const T &str) -> basic_string_view_type<T>
{
    auto trimstr = basic_string_view_type<T>{str};
    trimsv(trimstr);
    return trimstr;
}

template <concepts::string_like T>
[[nodiscard]] inline auto left(const T &str, const size_type<T> len) -> basic_string_type<T>
{
    return basic_string_type<T>{leftsv(str, len)};
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto leftsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>
{
    return basic_string_view_type<T>{str}.substr(0, len);
}

template <concepts::string_like T>
[[nodiscard]] inline auto right(const T &str, const size_type<T> len) -> basic_string_type<T>
{
    return basic_string_type<T>{rightsv(str, len)};
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto rightsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>
{
    return basic_string_view_type<T>{str}.substr(std::size(basic_string_view_type<T>{str}) - len);
}

template <concepts::string_like T>
[[nodiscard]] inline auto stripped_left(const T &str, const size_type<T> len) -> basic_string_type<T>
{
    return basic_string_type<T>{stripped_leftsv(str, len)};
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_leftsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>
{
    return basic_string_view_type<T>{str}.substr(len);
}

template <concepts::string_like T>
[[nodiscard]] inline auto stripped_right(const T &str, const size_type<T> len) -> basic_string_type<T>
{
    return basic_string_type<T>{stripped_rightsv(str, len)};
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_rightsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>
{
    const auto str_view = basic_string_view_type<T>{str};
    return str_view.substr(0, std::size(str_view) - len);
}

template <concepts::string_like T>
[[nodiscard]] inline auto stripped_both(const T &str, const size_type<T> len) -> basic_string_type<T>
{
    return basic_string_type<T>{stripped_bothsv(str, len)};
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto stripped_bothsv(const T &str, const size_type<T> len) -> basic_string_view_type<T>
{
    const auto str_view = basic_string_view_type<T>{str};
    return str_view.substr(len, std::size(str_view) - len - len);
}

template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_left(const T &str, const char_type<T> c) -> basic_string_type<T>
{
    auto stripstr = basic_string_type<T>{str};
    char_strip_left(stripstr, c);
    return stripstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_leftsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>
{
    auto stripstr = basic_string_view_type<T>{str};
    char_strip_leftsv(stripstr, c);
    return stripstr;
}

template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_right(const T &str, const char_type<T> c) -> basic_string_type<T>
{
    auto stripstr = basic_string_type<T>{str};
    char_strip_right(stripstr, c);
    return stripstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_rightsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>
{
    auto stripstr = basic_string_view_type<T>{str};
    char_strip_rightsv(stripstr, c);
    return stripstr;
}

template <concepts::string_like T>
[[nodiscard]] inline auto char_stripped_both(const T &str, const char_type<T> c) -> basic_string_type<T>
{
    auto stripstr = basic_string_type<T>{str};
    char_strip_both(stripstr, c);
    return stripstr;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto char_stripped_bothsv(const T &str, const char_type<T> c) -> basic_string_view_type<T>
{
    auto stripstr = basic_string_view_type<T>{str};
    char_strip_bothsv(stripstr, c);
    return stripstr;
}

template <concepts::basic_string T>
inline void strip_left(T &str, const size_type<T> len)
{
    str = stripped_left(str, len);
}

template <concepts::basic_string_view T>
inline void strip_leftsv(T &str, const size_type<T> len)
{
    str = stripped_leftsv(str, len);
}

template <concepts::basic_string T>
inline void strip_right(T &str, const size_type<T> len)
{
    str = stripped_right(str, len);
}

template <concepts::basic_string_view T>
inline void strip_rightsv(T &str, const size_type<T> len)
{
    str = stripped_rightsv(str, len);
}

template <concepts::basic_string T>
inline void strip_both(T &str, const size_type<T> len)
{
    str = stripped_both(str, len);
}

template <concepts::basic_string_view T>
inline void strip_bothsv(T &str, const size_type<T> len)
{
    str = stripped_bothsv(str, len);
}

template <concepts::basic_string T>
inline void char_strip_left(T &str, const char_type<T> c)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

template <concepts::basic_string_view T>
inline void char_strip_leftsv(T &str, const char_type<T> c)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

template <concepts::basic_string T>
inline void char_strip_right(T &str, const char_type<T> c)
{
    str.erase(std::find_if(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }).base(),
              std::end(str));
}

template <concepts::basic_string_view T>
inline void char_strip_rightsv(T &str, const char_type<T> c)
{
    str.remove_suffix(
        container::count_until(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }));
}

template <concepts::basic_string T>
inline void char_strip_both(T &str, const char_type<T> c)
{
    char_strip_left(str, c);
    char_strip_right(str, c);
}

template <concepts::basic_string_view T>
inline void char_strip_bothsv(T &str, const char_type<T> c)
{
    char_strip_leftsv(str, c);
    char_strip_rightsv(str, c);
}

template <concepts::basic_string T, concepts::string_view_like U, concepts::string_view_like V>
inline void replace(T &str, const U &from, const V &to)
{
    const auto from_view = basic_string_view_type<U>{from};

    if (std::empty(from_view))
        return;

    const auto to_view = basic_string_view_type<U>{to};

    auto start_pos = size_type<T>{};
    while ((start_pos = str.find(from_view, start_pos)) != basic_string_type<T>::npos)
    {
        str.replace(start_pos, std::size(from_view), to_view);
        start_pos += std::size(to_view);
    }
}

template <concepts::string_view_like T, concepts::string_view_like U, concepts::string_view_like V>
[[nodiscard]] inline auto replace_copy(const T &str, const U &from, const V &to) -> basic_string_type<T>
{
    auto copy = basic_string_type<T>{str};
    replace(copy, from, to);
    return copy;
}

template <concepts::basic_string T>
inline void to_lower(T &str)
{
    const auto to_lower_internal = [](const auto c)
    { return std::use_facet<std::ctype<char_type<T>>>(std::locale()).tolower(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_lower_internal);
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto to_lower_copy(const T &str) -> basic_string_type<T>
{
    auto result = basic_string_type<T>{str};
    to_lower(result);
    return result;
}

template <concepts::basic_string T>
inline void to_upper(T &str)
{
    const auto to_upper_internal = [](const auto c)
    { return std::use_facet<std::ctype<char_type<T>>>(std::locale()).toupper(c); };
    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_upper_internal);
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto to_upper_copy(const T &str) -> basic_string_type<T>
{
    auto result = basic_string_type<T>{str};
    to_upper(result);
    return result;
}

template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto begins_with(const T &str, const U &val) -> bool
{
    const auto str_view = basic_string_view_type<T>{str};
    const auto val_view = basic_string_view_type<T>{val};

    if (std::size(str_view) < std::size(val_view))
        return false;

    return leftsv(str_view, std::size(val_view)) == val_view;
}

template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto ends_with(const T &str, const U &val) -> bool
{
    const auto str_view = basic_string_view_type<T>{str};
    const auto val_view = basic_string_view_type<T>{val};

    if (std::size(str_view) < std::size(val_view))
        return false;

    return rightsv(str_view, std::size(val_view)) == val_view;
}

template <concepts::string_view_like T, concepts::string_view_like U>
[[nodiscard]] inline auto contains(const T &str, const U &val) -> bool
{
    const auto str_view = basic_string_view_type<T>{str};
    return str_view.find(val) != basic_string_view_type<T>::npos;
}

template <concepts::string_view_like T>
[[nodiscard]] inline auto contains(const T &str, const char_type<T> c) -> bool
{
    const auto str_view = basic_string_view_type<T>{str};
    return str_view.find(c) != basic_string_view_type<T>::npos;
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
