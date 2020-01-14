// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <stdexcept>
#include <string_view>
#include <variant>
#include <cstdint>

namespace aeon::common::lexical_parse
{

class lexical_parse_exception : public std::exception
{
};

class lexical_parse_result final
{
public:
    lexical_parse_result(const std::int64_t value, const std::size_t offset) noexcept
        : value_{value}
        , offset_{offset}
    {
    }

    lexical_parse_result(const double value, const std::size_t offset) noexcept
        : value_{value}
        , offset_{offset}
    {
    }

    ~lexical_parse_result() = default;

    lexical_parse_result(const lexical_parse_result &) = default;
    auto operator=(const lexical_parse_result &) -> lexical_parse_result & = default;

    lexical_parse_result(lexical_parse_result &&) noexcept = default;
    auto operator=(lexical_parse_result &&) noexcept -> lexical_parse_result & = default;

    /*!
     * Get the type of the parsed value. T must be either std::int64_t or double.
     * Returns true of the parsed value is of the given type T.
     */
    template <typename T>
    [[nodiscard]] auto is_type() const noexcept
    {
        return std::holds_alternative<T>(value_);
    }

    /*!
     * Get the parsed value. T must be either std::int64_t or double.
     * If the parsed value is of a different type, an exception will be thrown.
     */
    template <typename T>
    [[nodiscard]] auto value() const
    {
        return std::get<T>(value_);
    }

    /*!
     * Returns true of the parsed value is an integer.
     */
    [[nodiscard]] auto is_integer() const noexcept
    {
        return is_type<std::int64_t>();
    }

    /*!
     * Returns true of the parsed value is a double.
     */
    [[nodiscard]] auto is_double() const noexcept
    {
        return is_type<double>();
    }

    /*!
     * The offset of the first character within the parsed string that was not evaluated
     * as part of the number.
     */
    [[nodiscard]] auto offset() const noexcept
    {
        return offset_;
    }

    /*!
     * Get the parsed value. If the parsed value is of a different type, an exception will be thrown.
     */
    [[nodiscard]] auto integer_value() const
    {
        return value<std::int64_t>();
    }

    /*!
     * Get the parsed value. If the parsed value is of a different type, an exception will be thrown.
     */
    [[nodiscard]] auto double_value() const
    {
        return value<double>();
    }

private:
    std::variant<std::int64_t, double> value_;
    std::size_t offset_;
};

/*!
 * Convert a decimal number string to a double or int64. The resulting value depends on the parsed string.
 * For example 123 will be parsed to int64, while 1.23 will be parsed to a double.
 * Scientific notation in the form of 3e2 or 3E2 is also supported and will be parsed to a double.
 *
 * Will throw an exception if no number could be parsed.
 */
auto number(const std::string_view &str) -> lexical_parse_result;

/*!
 * Extract a possible number string from a given longer string. The string is split where the first character
 * does not equal 0-9, e, E or .
 *
 * This function can be used as a pre-sanitization for the number function.
 *
 * Examples:
 *     "1234abc" will return "1234"
 *     "1234.123abc" will return "1234.123"
 *     "1234,12" will return "1234"
 */
auto extract_number_string(const std::string_view &str) noexcept -> std::string_view;

} // namespace aeon::common::lexical_parse
