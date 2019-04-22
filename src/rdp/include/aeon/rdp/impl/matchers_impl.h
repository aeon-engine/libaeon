// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <charconv>

namespace aeon::rdp
{

template <typename T, typename std::enable_if<std::is_integral_v<T>>::type *>
auto parse_decimal(parser &parser) noexcept -> parse_result<T>
{
    parse_result<std::string_view> result;

    if constexpr (std::is_signed_v<T>)
        result = match_signed_digit(parser);
    else
        result = match_digit(parser);

    if (!result)
        return unmatched{};

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_binary(parser &parser) noexcept -> parse_result<T>
{
    auto result = match_binary(parser);

    if (!result)
        return unmatched{};

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 2);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

template <typename T>
inline auto parse_binary(parser &parser, const std::string_view prefix) noexcept -> parse_result<T>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_binary<T>(parser);
}

template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type *>
inline auto parse_hexadecimal(parser &parser) noexcept -> parse_result<T>
{
    auto result = match_hexadecimal(parser);

    if (!result)
        return unmatched{};

    T value;
    const auto [ptr, ec] = std::from_chars(std::data(*result), std::data(*result) + std::size(*result), value, 16);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

template <typename T>
inline auto parse_hexadecimal(parser &parser, const std::string_view prefix) noexcept -> parse_result<T>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_hexadecimal<T>(parser);
}

} // namespace aeon::rdp
