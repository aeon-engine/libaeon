// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/unicode/utf_string_view.h>
#include <aeon/unicode/exception.h>
#include <aeon/common/string.h>
#include <aeon/common/string_view.h>

namespace aeon::unicode::stringutils
{

/*!
 * Escape a utf-8 string (ie. a newline '\n' will get translated into "\n").
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 */
[[nodiscard]] auto escape(const common::string_view &str) -> common::string;

/*!
 * Escape a utf-8 string (ie. a newline '\n' will get translated into "\n").
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 */
[[nodiscard]] auto escape(const utf_string_view<common::string_view>::iterator begin,
                          const utf_string_view<common::string_view>::iterator end) -> common::string;

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
[[nodiscard]] auto unescape(const common::string_view &str, const unescape_mode mode = unescape_mode::error_on_unknown)
    -> common::string;

/*!
 * Unescape a utf-8 string (ie. "abc\n123" will become an actual newline character).
 * This function is utf-8 aware, which means that it escape properly on character codepoint boundaries.
 *
 * The error mode determines what to do with unknown escape characters (ie. '\u1234'): skip or throw an exception
 */
[[nodiscard]] auto unescape(const utf_string_view<common::string_view>::iterator begin,
                            const utf_string_view<common::string_view>::iterator end,
                            const unescape_mode mode = unescape_mode::error_on_unknown) -> common::string;

} // namespace aeon::unicode::stringutils
