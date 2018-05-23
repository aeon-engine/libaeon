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

#include <aeon/math/vector2.h>
#include <aeon/types/size2d.h>

namespace aeon::types
{

template <typename T>
class coordinate
{
public:
    coordinate() noexcept
        : x{}
        , y{}
    {
    }

    coordinate(const T x, const T y) noexcept
        : x{x}
        , y{y}
    {
    }

    explicit coordinate(const math::vector2<T> &vec) noexcept
        : x{vec.x}
        , y{vec.y}
    {
    }

    ~coordinate() noexcept = default;

    coordinate(const coordinate<T> &) noexcept = default;
    auto operator=(const coordinate<T> &) noexcept -> coordinate<T> & = default;

    coordinate(coordinate<T> &&) noexcept = default;
    auto operator=(coordinate<T> &&) noexcept -> coordinate<T> & = default;

    T x;
    T y;
};

template <typename T>
inline auto operator==(const coordinate<T> &lhs, const coordinate<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
inline auto operator!=(const coordinate<T> &lhs, const coordinate<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto contains(const coordinate<T> coord, const size2d<T> size) noexcept -> bool
{
    return (coord.x < width(size) && coord.y < height(size));
}

} // namespace aeon::types
