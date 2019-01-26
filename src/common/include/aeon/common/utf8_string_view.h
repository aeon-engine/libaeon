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

#include <aeon/common/utf8_utils.h>
#include <string_view>

namespace aeon::common::utf8
{

class utf8_string_iterator final
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit utf8_string_iterator(const char *begin, const char *end);
    explicit utf8_string_iterator(const char *begin, const char *end, const char *offset);

    ~utf8_string_iterator() = default;

    utf8_string_iterator(const utf8_string_iterator &) noexcept = default;
    auto operator=(const utf8_string_iterator &) noexcept -> utf8_string_iterator & = default;

    utf8_string_iterator(utf8_string_iterator &&) noexcept = default;
    auto operator=(utf8_string_iterator &&) noexcept -> utf8_string_iterator & = default;

    auto operator*() noexcept -> reference;
    auto operator-> () noexcept -> pointer;

    auto operator++() -> utf8_string_iterator &;
    auto operator++(int) -> utf8_string_iterator;

    auto operator==(const utf8_string_iterator &other) const noexcept -> bool;
    auto operator!=(const utf8_string_iterator &other) const noexcept -> bool;

private:
    void consume_bom();

    const char *begin_;
    const char *end_;
    const char *offset_;
    char32_t current_;
};

class utf8_string_view final
{
public:
    explicit utf8_string_view(const std::string_view view) noexcept;

    ~utf8_string_view() = default;

    utf8_string_view(const utf8_string_view &) noexcept = default;
    auto operator=(const utf8_string_view &) noexcept -> utf8_string_view & = default;

    utf8_string_view(utf8_string_view &&) noexcept = default;
    auto operator=(utf8_string_view &&) noexcept -> utf8_string_view & = default;

    auto begin() const noexcept;

    auto end() const noexcept;

private:
    std::string_view view_;
};

} // namespace aeon::common::utf8

#include <aeon/common/impl/utf8_string_view_impl.h>
