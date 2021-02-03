// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::unicode::ctypes
{

/*!
 * Determines whether the specified code point is a digit character.
 * True for characters with general category "Nd" (decimal digit numbers). Beginning with Unicode 4, this is the same as
 * testing for the Numeric_Type of Decimal. In order to narrow the definition of hexadecimal digits to only ASCII
 * characters, use is_xdigit_ascii()
 */
[[nodiscard]] auto is_digit(const char32_t c) noexcept -> bool;

/*!
 * Determines whether the specified code point is a digit character (0-9) in ascii.
 */
[[nodiscard]] auto is_digit_ascii(const char32_t c) noexcept -> bool;

/*!
 * Determines whether the specified code point is a hexadecimal digit.
 * True for characters with general category "Nd" (decimal digit numbers) as well as Latin letters a-f and A-F in both
 * ASCII and Fullwidth ASCII. (That is, for letters with code points 0041..0046, 0061..0066, FF21..FF26, FF41..FF46.) In
 * order to narrow the definition of hexadecimal digits to only ASCII characters, use is_xdigit_ascii()
 */
[[nodiscard]] auto is_xdigit(const char32_t c) noexcept -> bool;

/*!
 * Determines whether the specified code point is a hexadecimal digit in ascii.
 */
[[nodiscard]] auto is_xdigit_ascii(const char32_t c) noexcept -> bool;

/*!
 * Determines whether the specified code point is a "graphic" character (printable, excluding spaces).
 * TRUE for all characters except those with general categories "Cc" (control codes), "Cf" (format controls), "Cs"
 * (surrogates), "Cn" (unassigned), and "Z" (separators).
 */
[[nodiscard]] auto is_graph(const char32_t c) noexcept -> bool;

} // namespace aeon::unicode::ctypes
