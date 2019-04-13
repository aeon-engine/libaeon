// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/rdp.h>
#include <iostream>

namespace aeon::common::rdp
{

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

inline cursor::cursor(const std::string_view line, const std::ptrdiff_t line_number,
                      const std::ptrdiff_t column) noexcept
    : line_{line}
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

inline void print_parse_error(const parser &parser, const std::string_view message)
{
    print_parse_error(parser, message, std::cerr);
}

inline void print_parse_error(const parser &parser, const std::string_view message, std::ostream &stream)
{
    const auto file = filename(parser);

    if (!file.empty())
        stream << file << ':';

    const auto c = parser.cursor();

    stream << c.line_number() << ':' << c.column() << ": error: " << message << '\n';
    print_cursor_info(c, stream);
}

} // namespace aeon::common::rdp
