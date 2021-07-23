// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/rdp/parse_result.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/common/string.h>

namespace aeon::rdp
{

template <common::concepts::string_view_like T>
inline parser<T>::parser(const T &v)
    : view_{string_view_type{v}}
    , current_{std::begin(view_)}
    , filename_{}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <common::concepts::string_view_like T>
inline parser<T>::parser(const T &v, const std::u8string_view filename)
    : view_{string_view_type{v}}
    , current_{std::begin(view_)}
    , filename_{filename}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::eof() const noexcept -> bool
{
    return current_ == std::end(view_);
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::bof() const noexcept -> bool
{
    return current_ == std::begin(view_);
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::str() const noexcept -> const string_view_type &
{
    return view_;
}

template <common::concepts::string_view_like T>
inline auto parser<T>::advance() noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    ++current_;
    return true;
}

template <common::concepts::string_view_like T>
inline auto parser<T>::advance(const size_type count) noexcept -> bool
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

template <common::concepts::string_view_like T>
inline void parser<T>::advance_to_end() noexcept
{
    current_ = std::end(view_);
}

template <common::concepts::string_view_like T>
inline auto parser<T>::reverse() noexcept -> bool
{
    if (bof()) [[unlikely]]
        return false;

    --current_;
    return true;
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::current() const noexcept -> char_type
{
    return *current_;
}

template <common::concepts::string_view_like T>
auto parser<T>::current_iterator() const noexcept -> iterator
{
    return current_;
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::operator*() const noexcept -> char_type
{
    return current();
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::offset() const noexcept -> size_type
{
    return std::distance(std::begin(view_), current_);
}

template <common::concepts::string_view_like T>
inline auto parser<T>::size() const noexcept -> size_type
{
    return std::size(view_);
}

template <common::concepts::string_view_like T>
inline auto parser<T>::remaining_size() const noexcept -> size_type
{
    return std::distance(current_, std::end(view_));
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::cursor() const noexcept -> rdp::cursor<T>
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

    return rdp::cursor<T>{filename(), line, line_number, column};
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::filename() const noexcept -> std::u8string_view
{
    return filename_;
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::get_range(const size_type begin, const size_type end) const noexcept
    -> parse_result<T, string_view_type>
{
    if (end <= begin)
        return parse_error{*this, "End <= Begin."};

    if (end >= std::size(view_))
        return parse_error{*this, "Index out of range."};

    return matched{view_.substr(begin, end - begin)};
}

template <common::concepts::string_view_like T>
inline auto parser<T>::peek(const string_view_type str) noexcept -> bool
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

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::check(const char_type c) noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    if (current() != c)
        return false;

    ++current_;

    return true;
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::check(const string_view_type str) noexcept -> bool
{
    if (!peek(str))
        return false;

    current_ += std::size(str);

    return true;
}

template <common::concepts::string_view_like T>
inline auto parser<T>::check(const std::initializer_list<char_type> c) noexcept -> bool
{
    if (eof()) [[unlikely]]
        return false;

    if (!common::container::contains(std::begin(c), std::end(c), current()))
        return false;

    ++current_;

    return true;
}

template <common::concepts::string_view_like T>
inline void parser<T>::skip(const char_type c) noexcept
{
    while (!eof() && (current() == c))
        advance();
}

template <common::concepts::string_view_like T>
inline void parser<T>::skip(const std::initializer_list<char_type> c) noexcept
{
    while (!eof() && common::container::contains(std::begin(c), std::end(c), current()))
        advance();
}

template <common::concepts::string_view_like T>
inline void parser<T>::skip_until(const char_type c) noexcept
{
    while (!eof() && current() != c)
        advance();
}

template <common::concepts::string_view_like T>
inline void parser<T>::skip_until(const std::initializer_list<char_type> c) noexcept
{
    while (!eof() && !common::container::contains(std::begin(c), std::end(c), current()))
        advance();
}

template <common::concepts::string_view_like T>
inline auto parser<T>::match_each(const std::initializer_list<char_type> c) noexcept
    -> parse_result<T, string_view_type>
{
    return match([&c](const auto ch) { return common::container::contains(std::begin(c), std::end(c), ch); });
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::match_until(const char_type c, const eof_mode mode) noexcept
    -> parse_result<T, string_view_type>
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

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto parser<T>::match_until(const string_view_type str) noexcept
    -> parse_result<T, string_view_type>
{
    auto itr = current_;

    while (itr + std::size(str) <= std::cend(view_))
    {
        if (str == string_view_type{&*itr, std::size(str)})
        {
            const auto result = common::string::make_string_view(current_, itr);
            current_ = itr;
            return matched{result};
        }

        ++itr;
    }

    return unmatched{};
}

template <common::concepts::string_view_like T>
inline auto parser<T>::match_until(const std::initializer_list<char_type> c, const eof_mode mode) noexcept
    -> parse_result<T, string_view_type>
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

template <common::concepts::string_view_like T>
template <std::contiguous_iterator iterator_t>
inline parser<T>::parser(iterator_t begin, iterator_t end)
    : view_{common::string::make_string_view(begin, end)}
    , current_{std::begin(view_)}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <common::concepts::string_view_like T>
template <typename matcher_t>
inline auto parser<T>::match(matcher_t pred) noexcept -> parse_result<T, string_view_type>
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

template <common::concepts::string_view_like T>
template <typename matcher_t>
inline auto parser<T>::match_indexed(matcher_t pred) noexcept -> parse_result<T, string_view_type>
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

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto eof(const rdp::parser<T> &parser) noexcept -> bool
{
    return parser.eof();
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto bof(const rdp::parser<T> &parser) noexcept -> bool
{
    return parser.bof();
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto current(const rdp::parser<T> &parser) noexcept -> typename rdp::parser<T>::char_type
{
    return parser.current();
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto offset(const rdp::parser<T> &parser) noexcept -> typename rdp::parser<T>::size_type
{
    return parser.offset();
}

template <common::concepts::string_view_like T>
[[nodiscard]] inline auto filename(const rdp::parser<T> &parser) noexcept -> std::u8string_view
{
    return parser.filename();
}

} // namespace aeon::rdp
