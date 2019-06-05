// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/rdp/matchers.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/common/compilers.h>
#include <aeon/common/from_chars.h>

#include <cctype>
#include <type_traits>
#include <cstdint>

namespace aeon::rdp
{

auto check_whitespace(parser &parser) noexcept -> bool
{
    if (AEON_UNLIKELY(eof(parser)))
        return false;

    if (current(parser) != ' ' && current(parser) != '\t')
        return false;

    parser.advance();

    return true;
}

auto check_newline(parser &parser) noexcept -> bool
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

void skip_whitespace(parser &parser) noexcept
{
    while (!eof(parser) && (current(parser) == ' ' || current(parser) == '\t'))
        parser.advance();
}

void skip_whitespace_and_newline(parser &parser) noexcept
{
    while (!eof(parser) &&
           (current(parser) == ' ' || current(parser) == '\t' || current(parser) == '\r' || current(parser) == '\n'))
        parser.advance();
}

void skip_until_newline(parser &parser) noexcept
{
    parser.skip_until('\n');
}

auto match_alpha(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match([](const auto c) { return std::isalpha(c) != 0; });
}

auto match_digit(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match([](const auto c) { return std::isdigit(c) != 0; });
}

auto match_signed_digit(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match_indexed([](const auto c, const auto i) {
        if (AEON_UNLIKELY(i == 0) && c == '-')
            return true;

        return std::isdigit(c) != 0;
    });
}

auto match_alnum(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match([](const auto c) { return std::isalnum(c) != 0; });
}

auto match_binary(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match([](const auto c) { return c == '0' || c == '1'; });
}

auto match_hexadecimal(parser &parser) noexcept -> parse_result<std::string_view>
{
    return parser.match([](const auto c) { return std::isxdigit(c) != 0; });
}

template <typename T>
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
    const auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

auto parse_decimal_signed(parser &parser) noexcept -> parse_result<std::int64_t>
{
    return parse_decimal<std::int64_t>(parser);
}

auto parse_decimal_unsigned(parser &parser) noexcept -> parse_result<std::uint64_t>
{
    return parse_decimal<std::uint64_t>(parser);
}

auto parse_binary(parser &parser) noexcept -> parse_result<std::uint64_t>
{
    const auto result = match_binary(parser);

    if (!result)
        return unmatched{};

    std::uint64_t value;
    const auto [ptr, ec] = common::from_chars(*result, value, 2);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

auto parse_binary(parser &parser, const std::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_binary(parser);
}

auto parse_hexadecimal(parser &parser) noexcept -> parse_result<std::uint64_t>
{
    const auto result = match_hexadecimal(parser);

    if (!result)
        return unmatched{};

    std::uint64_t value;
    const auto [ptr, ec] = common::from_chars(*result, value, 16);

    if (ec != std::errc{})
        return unmatched{};

    return matched{value};
}

auto parse_hexadecimal(parser &parser, const std::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_hexadecimal(parser);
}

} // namespace aeon::rdp
