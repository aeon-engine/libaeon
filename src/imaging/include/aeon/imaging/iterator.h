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

#include <aeon/imaging/dimension.h>
#include <cstdint>
#include <iterator>

namespace aeon::imaging
{

template <typename pixel_type_t>
class iterator
{
public:
    using value_type = pixel_type_t;
    using pointer = pixel_type_t *;
    using reference = pixel_type_t &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit iterator(std::uint8_t *current, const difference_type skip);

    ~iterator() = default;

    iterator(const iterator &) noexcept = default;
    auto operator=(const iterator &) noexcept -> iterator & = default;

    iterator(iterator &&o) noexcept = default;
    auto operator=(iterator &&other) noexcept -> iterator & = default;

    auto operator*() const noexcept -> reference;
    auto operator-> () const noexcept -> pointer;

    auto operator++() noexcept -> iterator &;
    auto operator++(int)noexcept -> iterator;

    auto operator==(const iterator &other) const noexcept -> bool;
    auto operator!=(const iterator &other) const noexcept -> bool;

    template <typename T>
    auto as() noexcept -> T *;

private:
    std::uint8_t *current_;
    difference_type skip_;
};

template <typename pixel_type_t>
inline iterator<pixel_type_t>::iterator(std::uint8_t *current, const difference_type skip)
    : current_(current)
    , skip_(skip)
{
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator*() const noexcept -> reference
{
    return *reinterpret_cast<pixel_type_t *>(current_);
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator-> () const noexcept -> pointer
{
    return &**this;
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator++() noexcept -> iterator &
{
    current_ += skip_;
    return *this;
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator++(int)noexcept -> iterator
{
    const auto temp(*this);
    ++*this;
    return temp;
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator==(const iterator &other) const noexcept -> bool
{
    return current_ == other.current_;
}

template <typename pixel_type_t>
inline auto iterator<pixel_type_t>::operator!=(const iterator &other) const noexcept -> bool
{
    return !(*this == other);
}

template <typename pixel_type_t>
template <typename T>
auto iterator<pixel_type_t>::as() noexcept -> T *
{
    return reinterpret_cast<T *>(current_);
}

} // namespace aeon::imaging
