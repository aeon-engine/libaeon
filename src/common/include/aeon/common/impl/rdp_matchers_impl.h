// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <charconv>
#include <cctype>

namespace aeon::common
{

inline auto check_whitespace(rdp &rdp) noexcept -> bool
{
    if (AEON_UNLIKELY(eof(rdp)))
        return false;

    if (current(rdp) != ' ' && current(rdp) != '\t')
        return false;

    rdp.advance();

    return true;
}

inline void skip_whitespace(rdp &rdp) noexcept
{
    while (!eof(rdp) && (current(rdp) == ' ' || current(rdp) == '\t'))
        rdp.advance();
}

inline void skip_whitespace_and_newline(rdp &rdp) noexcept
{
    while (!eof(rdp) && (current(rdp) == ' ' || current(rdp) == '\t' || current(rdp) == '\r' || current(rdp) == '\n'))
        rdp.advance();
}

inline void skip_until_newline(rdp &rdp) noexcept
{
    rdp.skip_until('\n');
}

inline auto match_alpha(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match([](const auto c) { return std::isalpha(c) != 0; });
}

inline auto match_digit(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match([](const auto c) { return std::isdigit(c) != 0; });
}

inline auto match_signed_digit(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match_indexed([](const auto c, const auto i) {
        if (AEON_UNLIKELY(i == 0) && c == '-')
            return true;

        return std::isdigit(c) != 0;
    });
}

inline auto match_alnum(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match([](const auto c) { return std::isalnum(c) != 0; });
}

inline auto match_binary(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match([](const auto c) { return c == '0' || c == '1'; });
}

inline auto match_hexadecimal(rdp &rdp) noexcept -> std::optional<std::string_view>
{
    return rdp.match([](const auto c) { return std::isxdigit(c) != 0; });
}

template <typename T, typename std::enable_if<std::is_integral_v<T>>::type *>
auto parse_decimal(rdp &rdp) noexcept -> std::optional<T>
{
    std::optional<std::string_view> result;

    if constexpr (std::is_signed_v<T>)
        result = match_signed_digit(rdp);
    else
        result = match_digit(rdp);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_binary(rdp &rdp) noexcept -> std::optional<T>
{
    auto result = match_binary(rdp);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 2);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T>
inline auto parse_binary(rdp &rdp, const std::string_view prefix) noexcept -> std::optional<T>
{
    if (!rdp.check(prefix))
        return std::nullopt;

    return parse_binary<T>(rdp);
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_hexadecimal(rdp &rdp) noexcept -> std::optional<T>
{
    auto result = match_hexadecimal(rdp);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 16);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T>
inline auto parse_hexadecimal(rdp &rdp, const std::string_view prefix) noexcept -> std::optional<T>
{
    if (!rdp.check(prefix))
        return std::nullopt;

    return parse_hexadecimal<T>(rdp);
}

} // namespace aeon::common
