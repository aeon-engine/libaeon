// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <system_error>
#include <type_traits>
#include <string_view>
#include <cstdint>

namespace aeon::common
{

struct from_chars_result
{
    const char *ptr;
    std::errc ec;
};

auto from_chars(const char *first, const char *last, std::int32_t &value, const int base = 10) -> from_chars_result;
auto from_chars(const char *first, const char *last, std::int64_t &value, const int base = 10) -> from_chars_result;
auto from_chars(const char *first, const char *last, std::uint32_t &value, const int base = 10) -> from_chars_result;
auto from_chars(const char *first, const char *last, std::uint64_t &value, const int base = 10) -> from_chars_result;

auto from_chars(const char *first, const char *last, float &value) -> from_chars_result;
auto from_chars(const char *first, const char *last, double &value) -> from_chars_result;
auto from_chars(const char *first, const char *last, long double &value) -> from_chars_result;

template <typename T>
inline auto from_chars(const std::string_view str, T &value) -> from_chars_result
{
    return from_chars(std::data(str), std::data(str) + std::size(str), value);
}

template <typename T>
inline auto from_chars(const std::string_view str, T &value, const int base) -> from_chars_result
{
    return from_chars(std::data(str), std::data(str) + std::size(str), value, base);
}

} // namespace aeon::common
