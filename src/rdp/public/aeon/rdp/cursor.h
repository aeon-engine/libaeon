// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string_utils.h>

namespace aeon::rdp
{

/*!
 * Class that contains information about the current parser position (line, line number and column).
 * This can be used to display informational messages to the user (ie. displaying parse errors in a user friendly way).
 */
template <common::concepts::string_view_like T>
class cursor final
{
    template <common::concepts::string_view_like U>
    friend class parser;

public:
    using string_view_type = typename parser<T>::string_view_type;
    using char_type = typename parser<T>::char_type;
    using size_type = typename parser<T>::size_type;
    using difference_type = typename parser<T>::difference_type;

    ~cursor() = default;

    cursor(const cursor &) noexcept = default;
    auto operator=(const cursor &) noexcept -> cursor & = default;

    cursor(cursor &&) noexcept = default;
    auto operator=(cursor &&) noexcept -> cursor & = default;

    [[nodiscard]] auto filename() const noexcept -> std::u8string_view;
    [[nodiscard]] auto line() const noexcept -> string_view_type;
    [[nodiscard]] auto line_number() const noexcept -> size_type;
    [[nodiscard]] auto column() const noexcept -> size_type;

private:
    explicit cursor(const std::u8string_view filename, const string_view_type line, const difference_type line_number,
                    const difference_type column) noexcept;

    std::u8string_view filename_;
    string_view_type line_;
    size_type line_number_;
    size_type column_;
};

template <common::concepts::string_view_like T>
auto line(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::string_view_type;

template <common::concepts::string_view_like T>
auto line_number(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::size_type;

template <common::concepts::string_view_like T>
auto column(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::size_type;

template <common::concepts::string_view_like T>
void print_cursor_info(const cursor<T> &cursor);

template <common::concepts::string_view_like T>
void print_cursor_info(const cursor<T> &cursor, std::ostream &stream);

template <common::concepts::string_view_like T>
void print_parse_error(const cursor<T> &cursor, const std::u8string_view message);

template <common::concepts::string_view_like T>
void print_parse_error(const cursor<T> &cursor, const std::u8string_view message, std::ostream &stream);

} // namespace aeon::rdp

#include <aeon/rdp/impl/cursor_impl.h>
