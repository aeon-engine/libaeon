// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <charconv>
#include <cctype>

namespace aeon::common::rdp
{

inline auto check_whitespace(parser &parser) noexcept -> bool
{
    if (AEON_UNLIKELY(eof(parser)))
        return false;

    if (current(parser) != ' ' && current(parser) != '\t')
        return false;

    parser.advance();

    return true;
}

inline auto check_newline(parser &parser) noexcept -> bool
{
    if (AEON_UNLIKELY(eof(parser)))
        return false;

    scoped_state state{parser};

    if (rdp::current(parser) == '\r')
        parser.advance();

    if (rdp::current(parser) != '\n')
        return false;

    parser.advance();
    state.accept();

    return true;
}

inline void skip_whitespace(parser &parser) noexcept
{
    while (!eof(parser) && (current(parser) == ' ' || current(parser) == '\t'))
        parser.advance();
}

inline void skip_whitespace_and_newline(parser &parser) noexcept
{
    while (!eof(parser) &&
           (current(parser) == ' ' || current(parser) == '\t' || current(parser) == '\r' || current(parser) == '\n'))
        parser.advance();
}

inline void skip_until_newline(parser &parser) noexcept
{
    parser.skip_until('\n');
}

inline auto match_alpha(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isalpha(c) != 0; });
}

inline auto match_digit(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isdigit(c) != 0; });
}

inline auto match_signed_digit(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match_indexed([](const auto c, const auto i) {
        if (AEON_UNLIKELY(i == 0) && c == '-')
            return true;

        return std::isdigit(c) != 0;
    });
}

inline auto match_alnum(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isalnum(c) != 0; });
}

inline auto match_binary(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return c == '0' || c == '1'; });
}

inline auto match_hexadecimal(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isxdigit(c) != 0; });
}

template <typename T, typename std::enable_if<std::is_integral_v<T>>::type *>
auto parse_decimal(parser &parser) noexcept -> std::optional<T>
{
    std::optional<std::string_view> result;

    if constexpr (std::is_signed_v<T>)
        result = match_signed_digit(parser);
    else
        result = match_digit(parser);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_binary(parser &parser) noexcept -> std::optional<T>
{
    auto result = match_binary(parser);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 2);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T>
inline auto parse_binary(parser &parser, const std::string_view prefix) noexcept -> std::optional<T>
{
    if (!parser.check(prefix))
        return std::nullopt;

    return parse_binary<T>(parser);
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_hexadecimal(parser &parser) noexcept -> std::optional<T>
{
    auto result = match_hexadecimal(parser);

    if (!result)
        return std::nullopt;

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 16);

    if (ec != std::errc{})
        return std::nullopt;

    return value;
}

template <typename T>
inline auto parse_hexadecimal(parser &parser, const std::string_view prefix) noexcept -> std::optional<T>
{
    if (!parser.check(prefix))
        return std::nullopt;

    return parse_hexadecimal<T>(parser);
}

} // namespace aeon::common::rdp
