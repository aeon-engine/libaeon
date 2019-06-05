// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/unicode/utf_string_view.h>
#include <aeon/unicode/exception.h>
#include <string_view>
#include <string>

namespace aeon::unicode::stringutils
{

/*!
 * Escape a utf-8 string (ie. a newline '\n' will get translated into "\n").
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 */
[[nodiscard]] auto escape(const std::string_view &str) -> std::string;

/*!
 * Escape a utf-8 string (ie. a newline '\n' will get translated into "\n").
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 */
[[nodiscard]] auto escape(const utf_string_view<std::string_view>::iterator begin,
                          const utf_string_view<std::string_view>::iterator end) -> std::string;

class unescape_exception : public std::exception
{
};

enum class unescape_mode
{
    skip_unknown,
    error_on_unknown
};

/*!
 * Unescape a utf-8 string (ie. "abc\n123" will become an actual newline character).
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 *
 * The error mode determines what to do with unknown escape characters (ie. '\u1234'): skip or throw an exception
 */
[[nodiscard]] auto unescape(const std::string_view &str, const unescape_mode mode = unescape_mode::error_on_unknown)
    -> std::string;

/*!
 * Unescape a utf-8 string (ie. "abc\n123" will become an actual newline character).
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 *
 * The error mode determines what to do with unknown escape characters (ie. '\u1234'): skip or throw an exception
 */
[[nodiscard]] auto unescape(const utf_string_view<std::string_view>::iterator begin,
                            const utf_string_view<std::string_view>::iterator end,
                            const unescape_mode mode = unescape_mode::error_on_unknown) -> std::string;

} // namespace aeon::unicode::stringutils
