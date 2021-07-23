// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <iostream>

namespace aeon::rdp
{

inline auto cursor::filename() const noexcept -> std::string_view
{
    return filename_;
}

inline auto cursor::line() const noexcept -> std::string_view
{
    return line_;
}

inline auto cursor::line_number() const noexcept -> std::size_t
{
    return line_number_;
}

inline auto cursor::column() const noexcept -> std::size_t
{
    return column_;
}

inline cursor::cursor(const std::string_view filename, const std::string_view line, const std::ptrdiff_t line_number,
                      const std::ptrdiff_t column) noexcept
    : filename_{filename}
    , line_{line}
    , line_number_{static_cast<std::size_t>(line_number)}
    , column_{static_cast<std::size_t>(column)}
{
}

inline auto line(const cursor &cursor) noexcept -> std::string_view
{
    return cursor.line();
}

inline auto line_number(const cursor &cursor) noexcept -> std::size_t
{
    return cursor.line_number();
}

inline auto column(const cursor &cursor) noexcept -> std::size_t
{
    return cursor.column();
}

inline void print_cursor_info(const cursor &cursor)
{
    print_cursor_info(cursor, std::cout);
}

inline void print_cursor_info(const cursor &cursor, std::ostream &stream)
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

inline void print_parse_error(const cursor &cursor, const std::string_view message)
{
    print_parse_error(cursor, message, std::cerr);
}

inline void print_parse_error(const cursor &cursor, const std::string_view message, std::ostream &stream)
{
    if (!cursor.filename().empty())
        stream << cursor.filename() << ':';

    stream << cursor.line_number() << ':' << cursor.column() << ": error: " << message << '\n';
    print_cursor_info(cursor, stream);
}

} // namespace aeon::rdp
