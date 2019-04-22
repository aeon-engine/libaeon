// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <type_traits>

namespace aeon::rdp
{

/*!
 * Check if there is a whitespace character at the current position (space or tab).
 * Moves the internal index 1 if matched.
 * \return Check result
 */
auto check_whitespace(parser &parser) noexcept -> bool;

/*!
 * Check if there is a newline character (or characters on windows) at the current position
 * Moves the internal index 1 (or 2 on windows) if matched.
 * \return Check result
 */
auto check_newline(parser &parser) noexcept -> bool;

/*!
 * Skip all occurrences of whitespace characters (space and tab) and move the internal index to the
 * first character that does not match that.
 */
void skip_whitespace(parser &parser) noexcept;

/*!
 * Skip all occurrences of whitespace and newline characters (space, tab, \n and \r) and move the
 * internal index to the first character that does not match that.
 */
void skip_whitespace_and_newline(parser &parser) noexcept;

/*!
 * Skip all characters that are not a newline (\n) and move the internal index to the first character
 * right after a newline.
 */
void skip_until_newline(parser &parser) noexcept;

/*!
 * Match alpha characters (a-zA-Z) and return the result if any were matched.
 */
auto match_alpha(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Match digit characters (0-9) and return the result if any were matched.
 */
auto match_digit(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Match digit characters (optionally a '-' character followed by 0-9) and return the result if any were matched.
 */
auto match_signed_digit(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Match alpha and digit characters (a-zA-Z0-9) and return the result if any were matched.
 */
auto match_alnum(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Match binary characters (0 or 1) and return the result if any were matched.
 */
auto match_binary(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Match hexadecimal characters (0-9a-fA-F) and return the result if any were matched.
 */
auto match_hexadecimal(parser &parser) noexcept -> parse_result<std::string_view>;

/*!
 * Parse decimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_integral_v<T>>::type * = nullptr>
inline auto parse_decimal(parser &parser) noexcept -> parse_result<T>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type * = nullptr>
inline auto parse_binary(parser &parser) noexcept -> parse_result<T>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <typename T>
inline auto parse_binary(parser &parser, const std::string_view prefix) noexcept -> parse_result<T>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type * = nullptr>
inline auto parse_hexadecimal(parser &parser) noexcept -> parse_result<T>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <typename T>
inline auto parse_hexadecimal(parser &parser, const std::string_view prefix) noexcept -> parse_result<T>;

} // namespace aeon::rdp

#include <aeon/rdp/impl/matchers_impl.h>
