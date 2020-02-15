// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/from_chars.h>
#include <aeon_cpp_support.h>

#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER) || defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
#include <charconv>
#endif

#if (!defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
#define _USE_MATH_DEFINES
#include <cmath>
#endif

#include <climits>

namespace aeon::common
{

namespace internal
{

template <typename T, typename FuncT>
auto from_chars_internal(const char *first, const char *last, T &value, FuncT &&func) -> from_chars_result<char>
{
    auto end = const_cast<char *>(last);
    value = func(first, &end);

    if (value == HUGE_VAL)
        return {first, std::errc::invalid_argument};

    return {end, {}};
}

template <typename T, typename FuncT>
auto from_chars_internal(const char *first, const char *last, T &value, FuncT &&func, const int base)
    -> from_chars_result<char>
{
    if (*first == '0')
        return {first + 1, {}};

    auto end = const_cast<char *>(last);
    value = func(first, &end, base);

    if (value == 0)
        return {first, std::errc::invalid_argument};

    return {end, {}};
}

} // namespace internal

auto from_chars(const char *first, const char *last, std::int32_t &value, const int base) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::int32_t val = 0;
    const auto result = internal::from_chars_internal(first, last, val, strtol, base);

    if (val == LONG_MIN || val == LONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto from_chars(const char *first, const char *last, std::int64_t &value, const int base) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::int64_t val = 0;
    const auto result = internal::from_chars_internal(first, last, val, strtoll, base);

    if (val == LLONG_MIN || val == LLONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto from_chars(const char *first, const char *last, std::uint32_t &value, const int base) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::uint32_t val = 0;
    const auto result = internal::from_chars_internal(first, last, val, strtoul, base);

    if (val == ULONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto from_chars(const char *first, const char *last, std::uint64_t &value, const int base) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_INTEGER))
    auto [ptr, ec] = std::from_chars(first, last, value, base);
    return {ptr, ec};
#else
    std::uint64_t val = 0;
    const auto result = internal::from_chars_internal(first, last, val, strtoull, base);

    if (val == ULLONG_MAX)
        return {first, std::errc::result_out_of_range};

    value = val;

    return result;
#endif
}

auto from_chars(const char8_t *first, const char8_t *last, std::int32_t &value, const int base)
    -> from_chars_result<char8_t>
{
    const auto result =
        from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char8_t *first, const char8_t *last, std::int64_t &value, const int base)
    -> from_chars_result<char8_t>
{
    const auto result =
        from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char8_t *first, const char8_t *last, std::uint32_t &value, const int base)
    -> from_chars_result<char8_t>
{
    const auto result =
        from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char8_t *first, const char8_t *last, std::uint64_t &value, const int base)
    -> from_chars_result<char8_t>
{
    const auto result =
        from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value, base);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char *first, const char *last, float &value) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_FLOAT))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return internal::from_chars_internal(first, last, value, strtof);
#endif
}

auto from_chars(const char *first, const char *last, double &value) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_DOUBLE))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return internal::from_chars_internal(first, last, value, strtod);
#endif
}

auto from_chars(const char *first, const char *last, long double &value) -> from_chars_result<char>
{
#if (defined(AEON_COMPILER_HAS_FROM_CHARS_LONG_DOUBLE))
    auto [ptr, ec] = std::from_chars(first, last, value);
    return {ptr, ec};
#else
    return internal::from_chars_internal(first, last, value, strtold);
#endif
}

auto from_chars(const char8_t *first, const char8_t *last, float &value) -> from_chars_result<char8_t>
{
    const auto result = from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char8_t *first, const char8_t *last, double &value) -> from_chars_result<char8_t>
{
    const auto result = from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

auto from_chars(const char8_t *first, const char8_t *last, long double &value) -> from_chars_result<char8_t>
{
    const auto result = from_chars(reinterpret_cast<const char *>(first), reinterpret_cast<const char *>(last), value);
    return {reinterpret_cast<const char8_t *>(result.ptr), result.ec};
}

} // namespace aeon::common
