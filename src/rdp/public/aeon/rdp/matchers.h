// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
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
template <common::concepts::string_view_like T>
[[nodiscard]] auto match_regex(
    parser<T> &parser, const typename rdp::parser<T>::string_view_type regex,
    typename std::basic_regex<typename rdp::parser<T>::char_type>::flag_type flags = std::regex_constants::ECMAScript)
    -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Check if there is a whitespace character at the current position (space or tab).
 * Moves the internal index 1 if matched.
 * \return Check result
 */
template <common::concepts::string_view_like T>
inline auto check_whitespace(parser<T> &parser) noexcept -> bool;

/*!
 * Check if there is a newline character (or characters on windows) at the current position
 * Moves the internal index 1 (or 2 on windows) if matched.
 * \return Check result
 */
template <common::concepts::string_view_like T>
inline auto check_newline(parser<T> &parser) noexcept -> bool;

/*!
 * Skip all occurrences of whitespace characters (space and tab) and move the internal index to the
 * first character that does not match that.
 */
template <common::concepts::string_view_like T>
inline void skip_whitespace(parser<T> &parser) noexcept;

/*!
 * Skip all occurrences of whitespace and newline characters (space, tab, \n and \r) and move the
 * internal index to the first character that does not match that.
 */
template <common::concepts::string_view_like T>
inline void skip_whitespace_and_newline(parser<T> &parser) noexcept;

/*!
 * Skip all characters that are not a newline (\n) and move the internal index to the first character
 * right after a newline.
 */
template <common::concepts::string_view_like T>
inline void skip_until_newline(parser<T> &parser) noexcept;

/*!
 * Skip a possible Byte Order Marker (BOM); usually found at the start of Windows UTF-8 files.
 */
template <common::concepts::string_view_like T>
inline void skip_byte_order_marker(parser<T> &parser) noexcept;

/*!
 * Match alpha characters (a-zA-Z) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_alpha(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Match digit characters (0-9) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_digit(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Match digit characters (optionally a '-' character followed by 0-9) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_signed_digit(parser<T> &parser) noexcept
    -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Match alpha and digit characters (a-zA-Z0-9) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_alnum(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Match binary characters (0 or 1) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_binary(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Match hexadecimal characters (0-9a-fA-F) and return the result if any were matched.
 */
template <common::concepts::string_view_like T>
inline auto match_hexadecimal(parser<T> &parser) noexcept -> parse_result<T, typename rdp::parser<T>::string_view_type>;

/*!
 * Parse decimal characters (0-9) to an integer and return the result if any were matched and parsed.
 */
template <common::concepts::string_view_like T>
inline auto parse_decimal_signed(parser<T> &parser) noexcept -> parse_result<T, std::int64_t>;

/*!
 * Parse decimal characters (0-9) to an integer and return the result if any were matched and parsed.
 */
template <common::concepts::string_view_like T>
inline auto parse_decimal_unsigned(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>;

/*!
 * Parse a floating point number to a double and return the result if any were matched and parsed.
 */
template <common::concepts::string_view_like T>
inline auto parse_floating_point(parser<T> &parser) noexcept -> parse_result<T, double>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 */
template <common::concepts::string_view_like T>
inline auto parse_binary(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <common::concepts::string_view_like T>
inline auto parse_binary(parser<T> &parser, const std::string_view prefix) noexcept -> parse_result<T, std::uint64_t>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
template <common::concepts::string_view_like T>
inline auto parse_hexadecimal(parser<T> &parser) noexcept -> parse_result<T, std::uint64_t>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <common::concepts::string_view_like T>
inline auto parse_hexadecimal(parser<T> &parser, const std::string_view prefix) noexcept
    -> parse_result<T, std::uint64_t>;

/*!
 * Parse a boolean value (true or false) case insensitive.
 */
template <common::concepts::string_view_like T>
inline auto parse_boolean(parser<T> &parser) noexcept -> parse_result<T, bool>;

/*!
 * Parse a uuid value
 */
template <common::concepts::string_view_like T>
inline auto parse_uuid(parser<T> &parser) noexcept -> parse_result<T, common::uuid>;

} // namespace aeon::rdp

#include <aeon/rdp/impl/matchers_impl.h>
