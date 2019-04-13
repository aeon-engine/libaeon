// Copyright (c) 2012-2019 Robin Degen

#include <aeon/rdp/matchers.h>
#include <aeon/common/compilers.h>
#include <charconv>
#include <cctype>

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

auto match_alpha(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isalpha(c) != 0; });
}

auto match_digit(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isdigit(c) != 0; });
}

auto match_signed_digit(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match_indexed([](const auto c, const auto i) {
        if (AEON_UNLIKELY(i == 0) && c == '-')
            return true;

        return std::isdigit(c) != 0;
    });
}

auto match_alnum(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isalnum(c) != 0; });
}

auto match_binary(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return c == '0' || c == '1'; });
}

auto match_hexadecimal(parser &parser) noexcept -> std::optional<std::string_view>
{
    return parser.match([](const auto c) { return std::isxdigit(c) != 0; });
}

} // namespace aeon::rdp
