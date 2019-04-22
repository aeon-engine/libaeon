// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <string_view>

namespace aeon::rdp
{

/*!
 * Class that contains information about the current parser position (line, line number and column).
 * This can be used to display informational messages to the user (ie. displaying parse errors in a user friendly way).
 */
class cursor final
{
    friend class parser;

public:
    ~cursor() = default;

    cursor(const cursor &) noexcept = default;
    auto operator=(const cursor &) noexcept -> cursor & = default;

    cursor(cursor &&) noexcept = default;
    auto operator=(cursor &&) noexcept -> cursor & = default;

    [[nodiscard]] auto filename() const noexcept -> std::string_view;
    [[nodiscard]] auto line() const noexcept -> std::string_view;
    [[nodiscard]] auto line_number() const noexcept -> std::size_t;
    [[nodiscard]] auto column() const noexcept -> std::size_t;

private:
    explicit cursor(const std::string_view filename, const std::string_view line, const std::ptrdiff_t line_number,
                    const std::ptrdiff_t column) noexcept;

    std::string_view filename_;
    std::string_view line_;
    std::size_t line_number_;
    std::size_t column_;
};

auto line(const cursor &cursor) noexcept -> std::string_view;
auto line_number(const cursor &cursor) noexcept -> std::size_t;
auto column(const cursor &cursor) noexcept -> std::size_t;

void print_cursor_info(const cursor &cursor);
void print_cursor_info(const cursor &cursor, std::ostream &stream);

class parser;

void print_parse_error(const cursor &cursor, const std::string_view message);
void print_parse_error(const cursor &cursor, const std::string_view message, std::ostream &stream);

} // namespace aeon::rdp
