// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/rdp/scoped_state.h>
#include <aeon/common/from_chars.h>

#include <cctype>
#include <type_traits>
#include <cstdint>

namespace aeon::rdp
{

inline auto match_regex(parser &parser, const common::string_view regex,
                        std::basic_regex<parser::char_type>::flag_type flags) -> parse_result<common::string_view>
{
    if (eof(parser)) [[unlikely]]
        return unmatched{};

    const std::basic_regex r{std::data(regex), flags};
    std::match_results<common::string_view::const_iterator> match;

    if (!std::regex_search(parser.current_iterator(), std::end(parser.str()), match, r,
                           std::regex_constants::match_not_null | std::regex_constants::match_continuous))
        return unmatched{};

    aeon_assert(!match.empty(), "Bug: expected at least 1 match result.");

    const auto result = common::string_view{match.begin()->first, match.begin()->second};

    parser.advance(std::size(result));

    return matched{result};
}

inline auto check_whitespace(parser &parser) noexcept -> bool
{
    if (eof(parser)) [[unlikely]]
        return false;

    if (current(parser) != ' ' && current(parser) != '\t')
        return false;

    parser.advance();

    return true;
}

inline auto check_newline(parser &parser) noexcept -> bool
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

inline void skip_byte_order_marker(parser &parser) noexcept
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

inline auto match_alpha(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match([](const auto c) { return std::isalpha(c) != 0; });
}

inline auto match_digit(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match([](const auto c) { return std::isdigit(c) != 0; });
}

inline auto match_signed_digit(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match_indexed(
        [](const auto c, const auto i)
        {
            if (i == 0 && c == '-') [[unlikely]]
                return true;

            return std::isdigit(c) != 0;
        });
}

inline auto match_alnum(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match([](const auto c) { return std::isalnum(c) != 0; });
}

inline auto match_binary(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match([](const auto c) { return c == '0' || c == '1'; });
}

inline auto match_hexadecimal(parser &parser) noexcept -> parse_result<common::string_view>
{
    return parser.match([](const auto c) { return std::isxdigit(c) != 0; });
}

template <typename IntTypeT>
inline auto parse_decimal(parser &parser) noexcept -> parse_result<IntTypeT>
{
    scoped_state state{parser};

    parse_result<common::string_view> result;

    if constexpr (std::is_signed_v<IntTypeT>)
        result = match_signed_digit(parser);
    else
        result = match_digit(parser);

    if (!result)
        return unmatched{};

    IntTypeT value;
    auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

inline auto parse_decimal_signed(parser &parser) noexcept -> parse_result<std::int64_t>
{
    return parse_decimal<std::int64_t>(parser);
}

inline auto parse_decimal_unsigned(parser &parser) noexcept -> parse_result<std::uint64_t>
{
    return parse_decimal<std::uint64_t>(parser);
}

inline auto parse_floating_point(parser &parser) noexcept -> parse_result<double>
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

inline auto parse_binary(parser &parser) noexcept -> parse_result<std::uint64_t>
{
    scoped_state state{parser};

    const auto result = match_binary(parser);

    if (!result)
        return unmatched{};

    std::uint64_t value;
    auto [ptr, ec] = common::from_chars(*result, value, 2);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

inline auto parse_binary(parser &parser, const common::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_binary(parser);
}

inline auto parse_hexadecimal(parser &parser) noexcept -> parse_result<std::uint64_t>
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

inline auto parse_hexadecimal(parser &parser, const common::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_hexadecimal(parser);
}

inline auto parse_boolean(parser &parser) noexcept -> parse_result<bool>
{
    if (const auto result = match_regex(parser, "[t][r][u][e]", std::regex_constants::icase); result.result())
        return matched{true};

    if (const auto result = match_regex(parser, "[f][a][l][s][e]", std::regex_constants::icase); result.result())
        return matched{false};

    return unmatched{};
}

inline auto parse_uuid(parser &parser) noexcept -> parse_result<common::uuid>
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
