// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string_view.h>
#include <system_error>
#include <cstdint>

namespace aeon::common
{

template <typename char_t>
struct from_chars_result
{
    const char_t *ptr;
    std::errc ec;
};

auto from_chars(const char *first, const char *last, std::int32_t &value, const int base = 10)
    -> from_chars_result<char>;
auto from_chars(const char *first, const char *last, std::int64_t &value, const int base = 10)
    -> from_chars_result<char>;
auto from_chars(const char *first, const char *last, std::uint32_t &value, const int base = 10)
    -> from_chars_result<char>;
auto from_chars(const char *first, const char *last, std::uint64_t &value, const int base = 10)
    -> from_chars_result<char>;

auto from_chars(const char8_t *first, const char8_t *last, std::int32_t &value, const int base = 10)
    -> from_chars_result<char8_t>;
auto from_chars(const char8_t *first, const char8_t *last, std::int64_t &value, const int base = 10)
    -> from_chars_result<char8_t>;
auto from_chars(const char8_t *first, const char8_t *last, std::uint32_t &value, const int base = 10)
    -> from_chars_result<char8_t>;
auto from_chars(const char8_t *first, const char8_t *last, std::uint64_t &value, const int base = 10)
    -> from_chars_result<char8_t>;

auto from_chars(const char *first, const char *last, float &value) -> from_chars_result<char>;
auto from_chars(const char *first, const char *last, double &value) -> from_chars_result<char>;
auto from_chars(const char *first, const char *last, long double &value) -> from_chars_result<char>;

auto from_chars(const char8_t *first, const char8_t *last, float &value) -> from_chars_result<char8_t>;
auto from_chars(const char8_t *first, const char8_t *last, double &value) -> from_chars_result<char8_t>;
auto from_chars(const char8_t *first, const char8_t *last, long double &value) -> from_chars_result<char8_t>;

template <typename T>
inline auto from_chars(const string_view str, T &value) -> from_chars_result<char>
{
    return from_chars(std::data(str), std::data(str) + std::size(str), value);
}

template <typename T>
inline auto from_chars(const string_view str, T &value, const int base) -> from_chars_result<char>
{
    return from_chars(std::data(str), std::data(str) + std::size(str), value, base);
}

} // namespace aeon::common
