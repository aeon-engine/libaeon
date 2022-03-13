// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/rdp/scoped_state.h>
#include <aeon/common/from_chars.h>

#include <cctype>
#include <type_traits>
#include <cstdint>

namespace aeon::rdp
{

template <common::concepts::string_view_like T>
inline auto match_regex(parser<T> &parser, const typename rdp::parser<T>::string_view_type regex,
                        typename std::basic_regex<typename rdp::parser<T>::char_type>::flag_type flags)
    -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    if (eof(parser)) [[unlikely]]
        return unmatched{};

    const std::basic_regex<typename rdp::parser<T>::char_type> r{std::data(regex), flags};
    std::match_results<typename rdp::parser<T>::string_view_type::const_iterator> match;

    if (!std::regex_search(parser.current_iterator(), std::end(parser.str()), match, r,
                           std::regex_constants::match_not_null | std::regex_constants::match_continuous))
        return unmatched{};

    aeon_assert(!match.empty(), "Bug: expected at least 1 match result.");

    const auto result = common::string_utils::make_string_view(match.begin()->first, match.begin()->second);

    parser.advance(std::size(result));

    return matched{result};
}

template <common::concepts::string_view_like T>
inline auto check_whitespace(parser<T> &parser) noexcept -> bool
{
    if (eof(parser)) [[unlikely]]
        return false;

    if (current(parser) != ' ' && current(parser) != '\t')
        return false;

    parser.advance();

    return true;
}

template <common::concepts::string_view_like T>
inline auto check_newline(parser<T> &parser) noexcept -> bool
{
    if (eof(parser)) [[unlikely]]
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

template <common::concepts::string_view_like T>
inline void skip_whitespace(parser<T> &parser) noexcept
{
    while (!eof(parser) && (current(parser) == ' ' || current(parser) == '\t'))
        parser.advance();
}

template <common::concepts::string_view_like T>
inline void skip_whitespace_and_newline(parser<T> &parser) noexcept
{
    while (!eof(parser) &&
           (current(parser) == ' ' || current(parser) == '\t' || current(parser) == '\r' || current(parser) == '\n'))
        parser.advance();
}

template <common::concepts::string_view_like T>
inline void skip_until_newline(parser<T> &parser) noexcept
{
    parser.skip_until('\n');
}

template <common::concepts::string_view_like T>
inline void skip_byte_order_marker(parser<T> &parser) noexcept
{
    scoped_state state{parser};

    static constexpr std::array bom{static_cast<char>(0xEF), static_cast<char>(0xBB), static_cast<char>(0xBF)};

    for (const auto c : bom)
    {
        if (!parser.check(c))
            return;
    }

    state.accept();
}

template <common::concepts::string_view_like T>
inline auto match_alpha(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match([](const auto c) { return std::isalpha(c) != 0; });
}

template <common::concepts::string_view_like T>
inline auto match_digit(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match([](const auto c) { return std::isdigit(c) != 0; });
}

template <common::concepts::string_view_like T>
inline auto match_signed_digit(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match_indexed(
        [](const auto c, const auto i)
        {
            if (i == 0 && c == '-') [[unlikely]]
                return true;

            return std::isdigit(c) != 0;
        });
}

template <common::concepts::string_view_like T>
inline auto match_alnum(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match([](const auto c) { return std::isalnum(c) != 0; });
}

template <common::concepts::string_view_like T>
inline auto match_binary(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match([](const auto c) { return c == '0' || c == '1'; });
}

template <common::concepts::string_view_like T>
inline auto match_hexadecimal(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>
{
    return parser.match([](const auto c) { return std::isxdigit(c) != 0; });
}

template <common::concepts::string_view_like T, typename IntTypeT>
inline auto parse_decimal(parser<T> &parser) noexcept -> parse_result<T, IntTypeT>
{
    scoped_state state{parser};

    parse_result<T, std::string_view> result;

    if constexpr (std::is_signed_v<IntTypeT>)
        result = match_signed_digit<T>(parser);
    else
        result = match_digit<T>(parser);

    if (!result)
        return unmatched{};

    IntTypeT value;
    auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

template <common::concepts::string_view_like T>
inline auto parse_decimal_signed(parser<T> &parser) noexcept -> parse_result<T, std::int64_t>
{
    return parse_decimal<T, std::int64_t>(parser);
}

template <common::concepts::string_view_like T>
inline auto parse_decimal_unsigned(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>
{
    return parse_decimal<T, std::uint64_t>(parser);
}

template <common::concepts::string_view_like T>
inline auto parse_floating_point(parser<T> &parser) noexcept -> parse_result<T, double>
{
    scoped_state state{parser};

    const auto result = match_regex(parser, R"([-+]?\d+(\.\d+|([eE][-+]?\d+)))");

    if (!result)
        return unmatched{};

    double value;
    auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

template <common::concepts::string_view_like T>
inline auto parse_binary(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>
{
    scoped_state state{parser};

    const auto result = match_binary<T>(parser);

    if (!result)
        return unmatched{};

    std::uint64_t value;
    auto [ptr, ec] = common::from_chars(*result, value, 2);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

template <common::concepts::string_view_like T>
inline auto parse_binary(parser<T> &parser, const std::string_view prefix) noexcept -> parse_result<T, std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_binary(parser);
}

template <common::concepts::string_view_like T>
inline auto parse_hexadecimal(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>
{
    scoped_state state{parser};

    const auto result = match_hexadecimal(parser);

    if (!result)
        return unmatched{};

    std::uint64_t value;
    auto [ptr, ec] = common::from_chars(*result, value, 16);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

template <common::concepts::string_view_like T>
inline auto parse_hexadecimal(parser<T> &parser, const std::string_view prefix) noexcept
    -> parse_result<T, std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_hexadecimal(parser);
}

template <common::concepts::string_view_like T>
inline auto parse_boolean(parser<T> &parser) noexcept -> parse_result<T, bool>
{
    if (const auto result = match_regex(parser, "[t][r][u][e]", std::regex_constants::icase); result.result())
        return matched{true};

    if (const auto result = match_regex(parser, "[f][a][l][s][e]", std::regex_constants::icase); result.result())
        return matched{false};

    return unmatched{};
}

template <common::concepts::string_view_like T>
inline auto parse_uuid(parser<T> &parser) noexcept -> parse_result<T, common::uuid>
{
    scoped_state state{parser};

    const auto result =
        match_regex(parser, R"([0-9A-Fa-f]{8}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{12})");

    if (!result)
        return unmatched{};

    const auto uuid_value = common::uuid::try_parse(result.value());

    if (!uuid_value)
        return unmatched{};

    state.accept();
    return matched{*uuid_value};
}

} // namespace aeon::rdp
