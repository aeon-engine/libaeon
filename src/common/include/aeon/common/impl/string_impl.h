// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <cstdint>
#include <array>

namespace aeon::common::string
{

template <typename T>
[[nodiscard]] inline auto split(const std::basic_string<T> &str, const T delim,
                                std::vector<std::basic_string<T>> &elements) -> std::vector<std::basic_string<T>> &
{
    std::basic_stringstream<T, std::char_traits<T>, std::allocator<T>> ss{str};
    std::basic_string<T> item;

    while (std::getline(ss, item, delim))
    {
        elements.emplace_back(item);
    }

    return elements;
}

template <typename T>
[[nodiscard]] inline auto split(const std::basic_string<T> &str, const T delim) -> std::vector<std::basic_string<T>>
{
    std::vector<std::basic_string<T>> elements;
    return split(str, delim, elements);
}

template <typename T>
[[nodiscard]] inline auto splitsv(const std::basic_string_view<T> &str, const T delim,
                                  std::vector<std::basic_string_view<T>> &elements)
    -> std::vector<std::basic_string_view<T>>
{
    auto start = typename std::basic_string_view<T>::size_type{};
    auto pos = str.find_first_of(delim, start);

    while (pos != std::basic_string_view<T>::npos)
    {
        elements.emplace_back(str.substr(start, pos - start));
        start = pos + 1;
        pos = str.find_first_of(delim, start);
    }

    if (start < str.length())
        elements.emplace_back(str.substr(start, str.length() - start));

    return elements;
}

template <typename T>
[[nodiscard]] inline auto splitsv(const std::basic_string_view<T> &str, const T delim)
    -> std::vector<std::basic_string_view<T>>
{
    std::vector<std::basic_string_view<T>> elements;
    return splitsv(str, delim, elements);
}

template <typename T>
inline void ltrim(std::basic_string<T> &str)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str),
                                            [](const T c) { return !std::isspace(static_cast<int>(c)); }));
}

template <typename T>
inline void ltrimsv(std::basic_string_view<T> &str)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str),
                                             [](const T c) { return !std::isspace(static_cast<int>(c)); }));
}

template <typename T>
inline void rtrim(std::basic_string<T> &str)
{
    str.erase(
        std::find_if(std::crbegin(str), std::crend(str), [](const T c) { return !std::isspace(static_cast<int>(c)); })
            .base(),
        std::end(str));
}

template <typename T>
inline void rtrimsv(std::basic_string_view<T> &str)
{
    str.remove_suffix(container::count_until(std::crbegin(str), std::crend(str),
                                             [](const T c) { return !std::isspace(static_cast<int>(c)); }));
}

template <typename T>
inline void trim(std::basic_string<T> &str)
{
    ltrim(str);
    rtrim(str);
}

template <typename T>
inline void trimsv(std::basic_string_view<T> &str)
{
    ltrimsv(str);
    rtrimsv(str);
}

template <typename T>
[[nodiscard]] inline auto ltrimmed(const std::basic_string<T> &str) -> std::basic_string<T>
{
    auto trimstr = str;
    ltrim(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto ltrimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>
{
    auto trimstr = str;
    ltrimsv(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto rtrimmed(const std::basic_string<T> &str) -> std::basic_string<T>
{
    auto trimstr = str;
    rtrim(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto rtrimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>
{
    auto trimstr = str;
    rtrimsv(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto trimmed(const std::basic_string<T> &str) -> std::basic_string<T>
{
    auto trimstr = str;
    trim(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto trimmedsv(const std::basic_string_view<T> &str) -> std::basic_string_view<T>
{
    auto trimstr = str;
    trimsv(trimstr);
    return trimstr;
}

template <typename T>
[[nodiscard]] inline auto left(const std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
    -> std::basic_string<T>
{
    return str.substr(0, len);
}

template <typename T>
[[nodiscard]] inline auto leftsv(const std::basic_string_view<T> &str,
                                 const typename std::basic_string_view<T>::size_type len) -> std::basic_string_view<T>
{
    return str.substr(0, len);
}

template <typename T>
[[nodiscard]] inline auto right(const std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
    -> std::basic_string<T>
{
    return str.substr(std::size(str) - len);
}

template <typename T>
[[nodiscard]] inline auto rightsv(const std::basic_string_view<T> &str,
                                  const typename std::basic_string_view<T>::size_type len) -> std::basic_string_view<T>
{
    return str.substr(std::size(str) - len);
}

template <typename T>
[[nodiscard]] inline auto stripped_left(const std::basic_string<T> &str,
                                        const typename std::basic_string<T>::size_type len) -> std::basic_string<T>
{
    return str.substr(len);
}

template <typename T>
[[nodiscard]] inline auto stripped_leftsv(const std::basic_string_view<T> &str,
                                          const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>
{
    return str.substr(len);
}

template <typename T>
[[nodiscard]] inline auto stripped_right(const std::basic_string<T> &str,
                                         const typename std::basic_string<T>::size_type len) -> std::basic_string<T>
{
    return str.substr(0, std::size(str) - len);
}

template <typename T>
[[nodiscard]] inline auto stripped_rightsv(const std::basic_string_view<T> &str,
                                           const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>
{
    return str.substr(0, std::size(str) - len);
}

template <typename T>
[[nodiscard]] inline auto stripped_both(const std::basic_string<T> &str,
                                        const typename std::basic_string<T>::size_type len) -> std::basic_string<T>
{
    return str.substr(len, std::size(str) - len - len);
}

template <typename T>
[[nodiscard]] inline auto stripped_bothsv(const std::basic_string_view<T> &str,
                                          const typename std::basic_string_view<T>::size_type len)
    -> std::basic_string_view<T>
{
    return str.substr(len, std::size(str) - len - len);
}

template <typename T>
[[nodiscard]] inline auto char_stripped_left(const std::basic_string<T> &str, const T c) -> std::basic_string<T>
{
    auto stripstr = str;
    char_strip_left(stripstr, c);
    return stripstr;
}

template <typename T>
[[nodiscard]] inline auto char_stripped_leftsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>
{
    auto stripstr = str;
    char_strip_leftsv(stripstr, c);
    return stripstr;
}

template <typename T>
[[nodiscard]] inline auto char_stripped_right(const std::basic_string<T> &str, const T c) -> std::basic_string<T>
{
    auto stripstr = str;
    char_strip_right(stripstr, c);
    return stripstr;
}

template <typename T>
[[nodiscard]] inline auto char_stripped_rightsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>
{
    auto stripstr = str;
    char_strip_rightsv(stripstr, c);
    return stripstr;
}

template <typename T>
[[nodiscard]] inline auto char_stripped_both(const std::basic_string<T> &str, const T c) -> std::basic_string<T>
{
    auto stripstr = str;
    char_strip_both(stripstr, c);
    return stripstr;
}

template <typename T>
[[nodiscard]] inline auto char_stripped_bothsv(const std::basic_string_view<T> &str, const T c)
    -> std::basic_string_view<T>
{
    auto stripstr = str;
    char_strip_bothsv(stripstr, c);
    return stripstr;
}

template <typename T>
inline void strip_left(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
{
    str = stripped_left(str, len);
}

template <typename T>
inline void strip_leftsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len)
{
    str = stripped_leftsv(str, len);
}

template <typename T>
inline void strip_right(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
{
    str = stripped_right(str, len);
}

template <typename T>
inline void strip_rightsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len)
{
    str = stripped_rightsv(str, len);
}

template <typename T>
inline void strip_both(std::basic_string<T> &str, const typename std::basic_string<T>::size_type len)
{
    str = stripped_both(str, len);
}

template <typename T>
inline void strip_bothsv(std::basic_string_view<T> &str, const typename std::basic_string_view<T>::size_type len)
{
    str = stripped_bothsv(str, len);
}

template <typename T>
inline void char_strip_left(std::basic_string<T> &str, const T c)
{
    str.erase(std::begin(str), std::find_if(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

template <typename T>
inline void char_strip_leftsv(std::basic_string_view<T> &str, const T c)
{
    str.remove_prefix(container::count_until(std::cbegin(str), std::cend(str), [c](const auto ch) { return c != ch; }));
}

template <typename T>
inline void char_strip_right(std::basic_string<T> &str, const T c)
{
    str.erase(std::find_if(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }).base(),
              std::end(str));
}

template <typename T>
inline void char_strip_rightsv(std::basic_string_view<T> &str, const T c)
{
    str.remove_suffix(
        container::count_until(std::crbegin(str), std::crend(str), [c](const auto ch) { return c != ch; }));
}

template <typename T>
inline void char_strip_both(std::basic_string<T> &str, const T c)
{
    char_strip_left(str, c);
    char_strip_right(str, c);
}

template <typename T>
inline void char_strip_bothsv(std::basic_string_view<T> &str, const T c)
{
    char_strip_leftsv(str, c);
    char_strip_rightsv(str, c);
}

template <typename T>
inline void replace(std::basic_string<T> &str, const std::basic_string<T> &from, const std::basic_string<T> &to)
{
    if (std::empty(from))
        return;

    auto start_pos = typename std::basic_string<T>::size_type{};
    while ((start_pos = str.find(from, start_pos)) != std::basic_string<T>::npos)
    {
        str.replace(start_pos, std::size(from), to);
        start_pos += std::size(to);
    }
}

template <typename T>
[[nodiscard]] inline auto replace_copy(const std::basic_string<T> &str, const std::basic_string<T> &from,
                                       const std::basic_string<T> &to) -> std::basic_string<T>
{
    auto copy = str;
    replace(copy, from, to);
    return copy;
}

template <typename T>
inline void to_lower(std::basic_string<T> &str)
{
    const auto to_lower_internal = [](const T c) { return std::use_facet<std::ctype<T>>(std::locale()).tolower(c); };

    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_lower_internal);
}

template <typename T>
[[nodiscard]] inline auto to_lower_copy(const std::basic_string<T> &str) -> std::basic_string<T>
{
    auto result = str;
    to_lower(result);
    return result;
}

template <typename T>
inline void to_upper(std::basic_string<T> &str)
{
    const auto to_upper_internal = [](const T c) { return std::use_facet<std::ctype<T>>(std::locale()).toupper(c); };

    std::transform(std::cbegin(str), std::cend(str), std::begin(str), to_upper_internal);
}

template <typename T>
[[nodiscard]] inline auto to_upper_copy(const std::basic_string<T> &str) -> std::basic_string<T>
{
    auto result = str;
    to_upper(result);
    return result;
}

template <typename T>
[[nodiscard]] inline auto begins_with(const std::basic_string<T> &str, const std::basic_string<T> &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return left(str, std::size(val)) == val;
}

template <typename T>
[[nodiscard]] inline auto begins_withsv(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val)
    -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return leftsv(str, std::size(val)) == val;
}

template <typename T>
[[nodiscard]] inline auto ends_with(const std::basic_string<T> &str, const std::basic_string<T> &val) -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return right(str, std::size(val)) == val;
}

template <typename T>
[[nodiscard]] inline auto ends_withsv(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val)
    -> bool
{
    if (std::size(str) < std::size(val))
        return false;

    return rightsv(str, std::size(val)) == val;
}

template <typename T>
[[nodiscard]] inline auto contains(const std::basic_string_view<T> &str, const std::basic_string_view<T> &val) -> bool
{
    return str.find(val) != std::basic_string_view<T>::npos;
}

template <typename T>
[[nodiscard]] inline auto contains(const std::basic_string_view<T> &str, const T c) -> bool
{
    return str.find(c) != std::basic_string_view<T>::npos;
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

} // namespace aeon::common::string
