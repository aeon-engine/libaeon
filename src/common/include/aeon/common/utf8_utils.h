/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/string.h>
#include <string>
#include <string_view>

namespace aeon::common::utf8
{

class utf8_exception : public std::exception
{
};

inline auto bom() -> std::string;

template <typename iterator_t>
inline auto has_bom(const iterator_t itr, const iterator_t end);

inline auto has_bom(const std::string &str);

template <typename iterator_t>
inline auto skip_bom(const iterator_t itr, const iterator_t end);

inline auto strip_bom(std::string &str);

template <typename iterator_t>
inline auto codepoint_length(const iterator_t itr) noexcept;

template <typename iterator_t>
inline void advance_to_next_codepoint(iterator_t &itr, const iterator_t end) noexcept;

template <typename iterator_t>
inline auto read_codepoint(const iterator_t itr, const iterator_t end, char32_t &value);

template <typename iterator_t>
inline auto utf8_strlen(const iterator_t itr, const iterator_t end) -> std::size_t;

inline auto utf8_strlen(const std::string &str) -> std::size_t;

inline auto utf8_strlensv(const std::string_view &str) -> std::size_t;

template <typename iterator_t>
inline auto utf8_append(iterator_t itr, const char32_t c) -> iterator_t;

inline void utf8_append(std::string &str, const char32_t c);

inline auto utf8_to_string(const char32_t c) -> std::string;

} // namespace aeon::common::utf8

#include <aeon/common/impl/utf8_utils_impl.h>