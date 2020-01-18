// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/rdp/parser.h>
#include <aeon/rdp/cursor.h>
#include <aeon/rdp/parse_result.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/common/compilers.h>
#include <aeon/common/string.h>

namespace aeon::rdp
{

parser::parser(const std::string_view v)
    : parser{v, {}}
{
}

parser::parser(const std::string_view v, const std::string_view filename)
    : view_{v}
    , current_{std::begin(view_)}
    , filename_{filename}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

[[nodiscard]] auto parser::eof() const noexcept -> bool
{
    return current_ == std::end(view_);
}

[[nodiscard]] auto parser::bof() const noexcept -> bool
{
    return current_ == std::begin(view_);
}

auto parser::advance() noexcept -> bool
{
    if (AEON_UNLIKELY(eof()))
        return false;

    ++current_;
    return true;
}

auto parser::advance(const std::size_t count) noexcept -> bool
{
    scoped_state state{*this};

    for (auto i = 0u; i < count; ++i)
    {
        if (!advance())
            return false;
    }

    state.accept();
    return true;
}

auto parser::reverse() noexcept -> bool
{
    if (AEON_UNLIKELY(bof()))
        return false;

    --current_;
    return true;
}

auto parser::current() const noexcept -> char
{
    return *current_;
}

auto parser::operator*() const noexcept -> char
{
    return current();
}

auto parser::offset() const noexcept -> std::size_t
{
    return std::distance(std::begin(view_), current_);
}

auto parser::cursor() const noexcept -> rdp::cursor
{
    // Find beginning of the line
    auto line_begin = current_;

    if (current_ == std::end(view_))
        --line_begin;

    while (line_begin != std::begin(view_))
    {
        if (*line_begin == '\n')
        {
            break;
        }

        --line_begin;
    }

    if (*line_begin == '\n')
        ++line_begin;

    // Find the end of the line
    auto line_end = line_begin;
    while (line_end != std::end(view_) && *line_end != '\n')
    {
        ++line_end;
    }

    if (line_end != std::end(view_))
    {
        if (*line_end == '\r')
            --line_end;
    }

    const auto line = common::string::make_string_view(line_begin, line_end);
    const auto line_number = std::count(std::begin(view_), current_, '\n');
    const auto column = std::distance(line_begin, current_);

    return rdp::cursor{filename(), line, line_number, column};
}

auto parser::filename() const noexcept -> std::string_view
{
    return filename_;
}

auto parser::get_range(const std::size_t begin, const std::size_t end) const noexcept -> parse_result<std::string_view>
{
    if (end <= begin)
        return parse_error{*this, "End <= Begin."};

    if (end >= std::size(view_))
        return parse_error{*this, "Index out of range."};

    return matched{view_.substr(begin, end - begin)};
}

auto parser::check(const char c) noexcept -> bool
{
    if (AEON_UNLIKELY(eof()))
        return false;

    if (current() != c)
        return false;

    ++current_;

    return true;
}

auto parser::check(const std::string_view str) noexcept -> bool
{
    if (AEON_UNLIKELY(eof()))
        return false;

    auto itr = current_;

    for (const auto c : str)
    {
        if (AEON_UNLIKELY(itr == std::end(view_)) || c != *itr++)
            return false;
    }

    current_ = itr;

    return true;
}

void parser::skip(const char c) noexcept
{
    while (!eof() && (current() == c))
        advance();
}

void parser::skip_until(const char c) noexcept
{
    while (!eof() && current() != c)
        advance();
}

auto parser::match_regex(const std::string_view regex, std::basic_regex<char>::flag_type flags)
    -> parse_result<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return unmatched{};

    const std::regex r{std::data(regex), flags};
    std::match_results<std::string_view::const_iterator> match;

    if (!std::regex_search(current_, std::end(view_), match, r,
                           std::regex_constants::match_not_null | std::regex_constants::match_continuous))
        return unmatched{};

    aeon_assert(match.size() >= 1, "Bug: expected at least 1 match result.");

    const auto result = common::string::make_string_view(match.begin()->first, match.begin()->second);
    current_ = match.begin()->second;

    return matched{result};
}

auto parser::match_until(const char c) noexcept -> parse_result<std::string_view>
{
    auto itr = current_;

    do
    {
        ++itr;

        if (AEON_UNLIKELY(itr == std::end(view_)))
            return unmatched{};
    } while (*itr != c);

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

auto parser::match_until(const std::string_view str) noexcept -> parse_result<std::string_view>
{
    auto itr = current_;

    while (itr + std::size(str) <= std::cend(view_))
    {
        if (str == std::string_view{&*itr, std::size(str)})
        {
            const auto result = common::string::make_string_view(current_, itr);
            current_ = itr;
            return matched{result};
        }

        ++itr;
    }

    return unmatched{};
}

auto eof(const parser &parser) noexcept -> bool
{
    return parser.eof();
}

auto bof(const parser &parser) noexcept -> bool
{
    return parser.bof();
}

auto current(const parser &parser) noexcept -> char
{
    return parser.current();
}

auto offset(const parser &parser) noexcept -> std::size_t
{
    return parser.offset();
}

auto filename(const parser &parser) noexcept -> std::string_view
{
    return parser.filename();
}

} // namespace aeon::rdp
