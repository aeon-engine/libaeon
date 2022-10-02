// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <aeon/common/u8_stream.h>
#include <iostream>

namespace aeon::rdp
{

template <common::concepts::string_view_like T>
inline auto cursor<T>::filename() const noexcept -> std::u8string_view
{
    return filename_;
}

template <common::concepts::string_view_like T>
inline auto cursor<T>::line() const noexcept -> string_view_type
{
    return line_;
}

template <common::concepts::string_view_like T>
inline auto cursor<T>::line_number() const noexcept -> size_type
{
    return line_number_;
}

template <common::concepts::string_view_like T>
inline auto cursor<T>::column() const noexcept -> size_type
{
    return column_;
}

template <common::concepts::string_view_like T>
inline cursor<T>::cursor(const std::u8string_view filename, const string_view_type line,
                         const difference_type line_number, const difference_type column) noexcept
    : filename_{filename}
    , line_{line}
    , line_number_{static_cast<std::size_t>(line_number)}
    , column_{static_cast<std::size_t>(column)}
{
}

template <common::concepts::string_view_like T>
inline auto line(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::string_view_type
{
    return cursor.line();
}

template <common::concepts::string_view_like T>
inline auto line_number(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::size_type
{
    return cursor.line_number();
}

template <common::concepts::string_view_like T>
inline auto column(const cursor<T> &cursor) noexcept -> typename rdp::cursor<T>::size_type
{
    return cursor.column();
}

template <common::concepts::string_view_like T>
inline void print_cursor_info(const cursor<T> &cursor)
{
    print_cursor_info(cursor, std::cout);
}

template <common::concepts::string_view_like T>
inline void print_cursor_info(const cursor<T> &cursor, std::ostream &stream)
{
    const auto minimum_column_for_left_arrow = 8;

    stream << cursor.line();
    stream << '\n';

    if (cursor.column() < minimum_column_for_left_arrow)
    {
        if (cursor.column() > 1)
            stream << std::string(cursor.column() - 1, ' ');

        stream << "^~~~\n\n";
    }
    else
    {
        stream << std::string(cursor.column() - 1, '~') << '^' << '\n' << '\n';
    }
}

template <common::concepts::string_view_like T>
inline void print_parse_error(const cursor<T> &cursor, const std::u8string_view message)
{
    print_parse_error<T>(cursor, message, std::cerr);
}

template <common::concepts::string_view_like T>
inline void print_parse_error(const cursor<T> &cursor, const std::u8string_view message, std::ostream &stream)
{
    if (!cursor.filename().empty())
        stream << cursor.filename() << ':';

    stream << cursor.line_number() << ':' << cursor.column() << ": error: " << message << '\n';
    print_cursor_info(cursor, stream);
}

} // namespace aeon::rdp
