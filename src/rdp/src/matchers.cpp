// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

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

void skip_byte_order_marker(parser &parser) noexcept
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
    scoped_state state{parser};

    parse_result<std::string_view> result;

    if constexpr (std::is_signed_v<T>)
        result = match_signed_digit(parser);
    else
        result = match_digit(parser);

    if (!result)
        return unmatched{};

    T value;
    auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
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

auto parse_floating_point(parser &parser) noexcept -> parse_result<double>
{
    scoped_state state{parser};

    const auto result = parser.match_regex(R"([-+]?\d+(\.\d+|([eE][-+]?\d+)))");

    if (!result)
        return unmatched{};

    double value;
    auto [ptr, ec] = common::from_chars(*result, value);

    if (ec != std::errc{})
        return unmatched{};

    state.accept();
    return matched{value};
}

auto parse_binary(parser &parser) noexcept -> parse_result<std::uint64_t>
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

auto parse_binary(parser &parser, const std::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_binary(parser);
}

auto parse_hexadecimal(parser &parser) noexcept -> parse_result<std::uint64_t>
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

auto parse_hexadecimal(parser &parser, const std::string_view prefix) noexcept -> parse_result<std::uint64_t>
{
    if (!parser.check(prefix))
        return unmatched{};

    return parse_hexadecimal(parser);
}

auto parse_boolean(parser &parser) noexcept -> parse_result<bool>
{
    if (const auto result = parser.match_regex("[t][r][u][e]", std::regex_constants::icase); result.result())
        return matched{true};

    if (const auto result = parser.match_regex("[f][a][l][s][e]", std::regex_constants::icase); result.result())
        return matched{false};

    return unmatched{};
}

auto parse_uuid(parser &parser) noexcept -> parse_result<common::uuid>
{
    scoped_state state{parser};

    const auto result =
        parser.match_regex(R"([0-9A-Fa-f]{8}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{4}[-][0-9A-Fa-f]{12})");

    if (!result)
        return unmatched{};

    const auto uuid_value = common::uuid::try_parse(result.value());

    if (!uuid_value)
        return unmatched{};

    state.accept();
    return matched{*uuid_value};
}

} // namespace aeon::rdp
