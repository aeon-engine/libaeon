// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <aeon/common/string_view.h>
#include <aeon/common/uuid.h>

namespace aeon::rdp
{

/*!
 * Match with regular expressions. The expression is only matched when it starts at the current index.
 * Note that while using a Kleene star, empty sequences are not matched and will return unmatched.
 *
 * Examples:
 * "[a-zA-Z]+"
 * "[0-9]+"
 */
[[nodiscard]] auto match_regex(parser &parser, const common::string_view regex,
                               typename std::basic_regex<common::string_view::value_type>::flag_type flags =
                                   std::regex_constants::ECMAScript) -> parse_result<common::string_view>;

/*!
 * Check if there is a whitespace character at the current position (space or tab).
 * Moves the internal index 1 if matched.
 * \return Check result
 */
inline auto check_whitespace(parser &parser) noexcept -> bool;

/*!
 * Check if there is a newline character (or characters on windows) at the current position
 * Moves the internal index 1 (or 2 on windows) if matched.
 * \return Check result
 */
inline auto check_newline(parser &parser) noexcept -> bool;

/*!
 * Skip all occurrences of whitespace characters (space and tab) and move the internal index to the
 * first character that does not match that.
 */
inline void skip_whitespace(parser &parser) noexcept;

/*!
 * Skip all occurrences of whitespace and newline characters (space, tab, \n and \r) and move the
 * internal index to the first character that does not match that.
 */
inline void skip_whitespace_and_newline(parser &parser) noexcept;

/*!
 * Skip all characters that are not a newline (\n) and move the internal index to the first character
 * right after a newline.
 */
inline void skip_until_newline(parser &parser) noexcept;

/*!
 * Skip a possible Byte Order Marker (BOM); usually found at the start of Windows UTF-8 files.
 */
inline void skip_byte_order_marker(parser &parser) noexcept;

/*!
 * Match alpha characters (a-zA-Z) and return the result if any were matched.
 */
inline auto match_alpha(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Match digit characters (0-9) and return the result if any were matched.
 */
inline auto match_digit(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Match digit characters (optionally a '-' character followed by 0-9) and return the result if any were matched.
 */

inline auto match_signed_digit(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Match alpha and digit characters (a-zA-Z0-9) and return the result if any were matched.
 */
inline auto match_alnum(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Match binary characters (0 or 1) and return the result if any were matched.
 */
inline auto match_binary(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Match hexadecimal characters (0-9a-fA-F) and return the result if any were matched.
 */
inline auto match_hexadecimal(parser &parser) noexcept -> parse_result<common::string_view>;

/*!
 * Parse decimal characters (0-9) to an integer and return the result if any were matched and parsed.
 */
inline auto parse_decimal_signed(parser &parser) noexcept -> parse_result<std::int64_t>;

/*!
 * Parse decimal characters (0-9) to an integer and return the result if any were matched and parsed.
 */
inline auto parse_decimal_unsigned(parser &parser) noexcept -> parse_result<std::uint64_t>;

/*!
 * Parse a floating point number to a double and return the result if any were matched and parsed.
 */
inline auto parse_floating_point(parser &parser) noexcept -> parse_result<double>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 */
inline auto parse_binary(parser &parser) noexcept -> parse_result<std::uint64_t>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
inline auto parse_binary(parser &parser, const common::string_view prefix) noexcept -> parse_result<std::uint64_t>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
inline auto parse_hexadecimal(parser &parser) noexcept -> parse_result<std::uint64_t>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
inline auto parse_hexadecimal(parser &parser, const common::string_view prefix) noexcept -> parse_result<std::uint64_t>;

/*!
 * Parse a boolean value (true or false) case insensitive.
 */
inline auto parse_boolean(parser &parser) noexcept -> parse_result<bool>;

/*!
 * Parse a uuid value
 */
inline auto parse_uuid(parser &parser) noexcept -> parse_result<common::uuid>;

} // namespace aeon::rdp

#include <aeon/rdp/impl/matchers_impl.h>
