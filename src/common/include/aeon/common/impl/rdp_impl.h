// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/string.h>
#include <aeon/common/assert.h>
#include <aeon/common/compilers.h>
#include <regex>

namespace aeon::common
{

inline rdp::rdp(const std::string_view v)
    : view_{v}
    , current_{std::begin(view_)}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <typename iterator_t>
inline rdp::rdp(iterator_t begin, iterator_t end)
    : view_{string::make_string_view(begin, end)}
    , current_{std::begin(view_)}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

[[nodiscard]] inline auto rdp::eof() const noexcept
{
    return current_ == std::end(view_);
}

[[nodiscard]] inline auto rdp::bof() const noexcept
{
    return current_ == std::begin(view_);
}

inline auto rdp::advance() noexcept -> bool
{
    if (AEON_UNLIKELY(eof()))
        return false;

    ++current_;
    return true;
}

inline auto rdp::reverse() noexcept -> bool
{
    if (AEON_UNLIKELY(bof()))
        return false;

    --current_;
    return true;
}

inline auto rdp::current() const noexcept -> char
{
    return *current_;
}

inline auto rdp::operator*() const noexcept -> char
{
    return current();
}

inline auto rdp::offset() const noexcept -> std::size_t
{
    return std::distance(std::begin(view_), current_);
}

inline auto rdp::check(const char c) noexcept -> bool
{
    if (AEON_UNLIKELY(eof()))
        return false;

    if (current() != c)
        return false;

    ++current_;

    return true;
}

inline auto rdp::check(const std::string_view str) noexcept -> bool
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

inline void rdp::skip(const char c) noexcept
{
    while (!eof() && (current() == c))
        advance();
}

inline void rdp::skip_until(const char c) noexcept
{
    while (!eof() && current() != c)
        advance();
}

template <typename matcher_t>
inline auto rdp::match(matcher_t pred) noexcept -> std::optional<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return std::nullopt;

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr))
        ++itr;

    if (itr == current_)
        return std::nullopt;

    const auto result = string::make_string_view(current_, itr);
    current_ = itr;
    return result;
}

template <typename matcher_t>
inline auto rdp::match_indexed(matcher_t pred) noexcept -> std::optional<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return std::nullopt;

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr, std::distance(current_, itr)))
        ++itr;

    if (itr == current_)
        return std::nullopt;

    const auto result = string::make_string_view(current_, itr);
    current_ = itr;
    return result;
}

inline auto rdp::match_regex(const std::string_view regex) -> std::optional<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return std::nullopt;

    const std::regex r{std::data(regex)};
    std::match_results<std::string_view::const_iterator> match;

    if (!std::regex_search(current_, std::end(view_), match, r,
                           std::regex_constants::match_not_null | std::regex_constants::match_continuous))
        return std::nullopt;

    aeon_assert(match.size() == 1, "Bug: expected only 1 match result.");

    const auto result = string::make_string_view(match.begin()->first, match.begin()->second);
    current_ = match.begin()->second;

    return result;
}

inline auto rdp::match_until(const char c) noexcept -> std::optional<std::string_view>
{
    auto itr = current_;

    do
    {
        ++itr;

        if (AEON_UNLIKELY(itr == std::end(view_)))
            return std::nullopt;
    } while (*itr != c);

    const auto result = string::make_string_view(current_, itr);
    current_ = itr;
    return result;
}

inline auto eof(const rdp &rdp) noexcept -> bool
{
    return rdp.eof();
}

inline auto bof(const rdp &rdp) noexcept -> bool
{
    return rdp.bof();
}

inline auto current(const rdp &rdp) noexcept -> char
{
    return rdp.current();
}

inline auto offset(const rdp &rdp) noexcept -> std::size_t
{
    return rdp.offset();
}

} // namespace aeon::common
