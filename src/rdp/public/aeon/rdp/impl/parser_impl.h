// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/rdp/parse_result.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/common/string.h>

namespace aeon::rdp
{

inline parser::parser(const std::string_view v)
    : parser{v, {}}
{
}

inline parser::parser(const std::string_view v, const std::string_view filename)
    : view_{v}
    , current_{std::begin(view_)}
    , filename_{filename}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

[[nodiscard]] inline auto parser::eof() const noexcept -> bool
{
    return current_ == std::end(view_);
}

[[nodiscard]] inline auto parser::bof() const noexcept -> bool
{
    return current_ == std::begin(view_);
}

inline auto parser::advance() noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    ++current_;
    return true;
}

inline auto parser::advance(const std::size_t count) noexcept -> bool
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

inline void parser::advance_to_end() noexcept
{
    current_ = std::end(view_);
}

inline auto parser::reverse() noexcept -> bool
{
    if (bof()) [[unlikely]]
        return false;

    --current_;
    return true;
}

[[nodiscard]] inline auto parser::current() const noexcept -> char
{
    return *current_;
}

[[nodiscard]] inline auto parser::operator*() const noexcept -> char
{
    return current();
}

[[nodiscard]] inline auto parser::offset() const noexcept -> std::size_t
{
    return std::distance(std::begin(view_), current_);
}

inline auto parser::size() const noexcept -> std::size_t
{
    return std::size(view_);
}

inline auto parser::remaining_size() const noexcept -> std::size_t
{
    return std::distance(current_, std::end(view_));
}

[[nodiscard]] inline auto parser::cursor() const noexcept -> rdp::cursor
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

[[nodiscard]] inline auto parser::filename() const noexcept -> std::string_view
{
    return filename_;
}

[[nodiscard]] inline auto parser::get_range(const std::size_t begin, const std::size_t end) const noexcept
    -> parse_result<std::string_view>
{
    if (end <= begin)
        return parse_error{*this, "End <= Begin."};

    if (end >= std::size(view_))
        return parse_error{*this, "Index out of range."};

    return matched{view_.substr(begin, end - begin)};
}

inline auto parser::peek(const std::string_view str) noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    auto itr = current_;

    for (const auto c : str)
    {
        if (itr == std::end(view_)) [[unlikely]]
            return false;

        if (c != *itr++)
            return false;
    }

    return true;
}

[[nodiscard]] inline auto parser::check(const char c) noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    if (current() != c)
        return false;

    ++current_;

    return true;
}

[[nodiscard]] inline auto parser::check(const std::string_view str) noexcept -> bool
{
    if (!peek(str))
        return false;

    current_ += std::size(str);

    return true;
}

inline auto parser::check(const std::initializer_list<char> c) noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    if (!common::container::contains(std::begin(c), std::end(c), current()))
        return false;

    ++current_;

    return true;
}

inline void parser::skip(const char c) noexcept
{
    while (!eof() && (current() == c))
        advance();
}

inline void parser::skip(const std::initializer_list<char> c) noexcept
{
    while (!eof() && common::container::contains(std::begin(c), std::end(c), current()))
        advance();
}

inline void parser::skip_until(const char c) noexcept
{
    while (!eof() && current() != c)
        advance();
}

inline void parser::skip_until(const std::initializer_list<char> c) noexcept
{
    while (!eof() && !common::container::contains(std::begin(c), std::end(c), current()))
        advance();
}

inline auto parser::match_each(const std::initializer_list<char> c) noexcept -> parse_result<std::string_view>
{
    return match([&c](const char ch) { return common::container::contains(std::begin(c), std::end(c), ch); });
}

[[nodiscard]] inline auto parser::match_regex(const std::string_view regex, std::basic_regex<char>::flag_type flags)
    -> parse_result<std::string_view>
{
    if (eof()) [[unlikely]]
        return unmatched{};

    const std::regex r{std::data(regex), flags};
    std::match_results<std::string_view::const_iterator> match;

    if (!std::regex_search(current_, std::end(view_), match, r,
                           std::regex_constants::match_not_null | std::regex_constants::match_continuous))
        return unmatched{};

    aeon_assert(!match.empty(), "Bug: expected at least 1 match result.");

    const auto result = common::string::make_string_view(match.begin()->first, match.begin()->second);
    current_ = match.begin()->second;

    return matched{result};
}

[[nodiscard]] inline auto parser::match_until(const char c, const eof_mode mode) noexcept
    -> parse_result<std::string_view>
{
    auto itr = current_;

    do
    {
        ++itr;

        if (itr == std::end(view_)) [[unlikely]]
        {
            if (mode == eof_mode::fail)
                return unmatched{};
            else
                break;
        }
    } while (*itr != c);

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

[[nodiscard]] inline auto parser::match_until(const std::string_view str) noexcept -> parse_result<std::string_view>
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

inline auto parser::match_until(const std::initializer_list<char> c, const eof_mode mode) noexcept
    -> parse_result<std::string_view>
{
    auto itr = current_;

    do
    {
        ++itr;

        if (itr == std::end(view_)) [[unlikely]]
        {
            if (mode == eof_mode::fail)
                return unmatched{};
            else
                break;
        }
    } while (!common::container::contains(std::begin(c), std::end(c), *itr));

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

template <typename iterator_t>
inline parser::parser(iterator_t begin, iterator_t end)
    : view_{common::string::make_string_view(begin, end)}
    , current_{std::begin(view_)}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <typename matcher_t>
inline auto parser::match(matcher_t pred) noexcept -> parse_result<std::string_view>
{
    if (eof()) [[unlikely]]
        return unmatched{};

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr))
        ++itr;

    if (itr == current_)
        return unmatched{};

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

template <typename matcher_t>
inline auto parser::match_indexed(matcher_t pred) noexcept -> parse_result<std::string_view>
{
    if (eof()) [[unlikely]]
        return unmatched{};

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr, std::distance(current_, itr)))
        ++itr;

    if (itr == current_)
        return unmatched{};

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

[[nodiscard]] inline auto eof(const parser &parser) noexcept -> bool
{
    return parser.eof();
}

[[nodiscard]] inline auto bof(const parser &parser) noexcept -> bool
{
    return parser.bof();
}

[[nodiscard]] inline auto current(const parser &parser) noexcept -> char
{
    return parser.current();
}

[[nodiscard]] inline auto offset(const parser &parser) noexcept -> std::size_t
{
    return parser.offset();
}

[[nodiscard]] inline auto filename(const parser &parser) noexcept -> std::string_view
{
    return parser.filename();
}

} // namespace aeon::rdp
