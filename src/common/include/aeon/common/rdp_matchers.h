// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/rdp.h>
#include <type_traits>

namespace aeon::common
{

/*!
 * Check if there is a whitespace character at the current position (space or tab).
 * Moves the internal index 1 if matched.
 * \return True if possible, false on eof
 */
inline auto check_whitespace(rdp &rdp) noexcept -> bool;

/*!
 * Skip all occurrences of whitespace characters (space and tab) and move the internal index to the
 * first character that does not match that.
 */
inline void skip_whitespace(rdp &rdp) noexcept;

/*!
 * Skip all occurrences of whitespace and newline characters (space, tab, \n and \r) and move the
 * internal index to the first character that does not match that.
 */
inline void skip_whitespace_and_newline(rdp &rdp) noexcept;

/*!
 * Skip all characters that are not a newline (\n) and move the internal index to the first character
 * right after a newline.
 */
inline void skip_until_newline(rdp &rdp) noexcept;

/*!
 * Match alpha characters (a-zA-Z) and return the result if any were matched.
 */
inline auto match_alpha(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Match digit characters (0-9) and return the result if any were matched.
 */
inline auto match_digit(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Match digit characters (optionally a '-' character followed by 0-9) and return the result if any were matched.
 */
inline auto match_signed_digit(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Match alpha and digit characters (a-zA-Z0-9) and return the result if any were matched.
 */
inline auto match_alnum(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Match binary characters (0 or 1) and return the result if any were matched.
 */
inline auto match_binary(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Match hexadecimal characters (0-9a-fA-F) and return the result if any were matched.
 */
inline auto match_hexadecimal(rdp &rdp) noexcept -> std::optional<std::string_view>;

/*!
 * Parse decimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_integral_v<T>>::type * = nullptr>
inline auto parse_decimal(rdp &rdp) noexcept -> std::optional<T>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type * = nullptr>
inline auto parse_binary(rdp &rdp) noexcept -> std::optional<T>;

/*!
 * Parse binary characters (0 or 1) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <typename T>
inline auto parse_binary(rdp &rdp, const std::string_view prefix) noexcept -> std::optional<T>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 */
template <typename T, typename std::enable_if<std::is_unsigned_v<T>>::type * = nullptr>
inline auto parse_hexadecimal(rdp &rdp) noexcept -> std::optional<T>;

/*!
 * Parse hexadecimal characters (0-9a-fA-F) to an integer and return the result if any were matched and parsed.
 * The result is only matched if the binary value is prefixed with the given prefix.
 */
template <typename T>
inline auto parse_hexadecimal(rdp &rdp, const std::string_view prefix) noexcept -> std::optional<T>;

} // namespace aeon::common

#include <aeon/common/impl/rdp_matchers_impl.h>
