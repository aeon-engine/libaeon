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

#include <aeon/types/size2d.h>
#include <aeon/math/vector2.h>

namespace aeon::types
{

template <typename T>
class rectangle
{
public:
    rectangle() noexcept
        : left{}
        , top{}
        , right{}
        , bottom{}
    {
    }

    rectangle(T left, T top, T right, T bottom) noexcept
        : left{left}
        , top{top}
        , right{right}
        , bottom{bottom}
    {
    }

    ~rectangle() noexcept = default;

    rectangle(const rectangle &) noexcept = default;
    auto operator=(const rectangle &) noexcept -> rectangle & = default;

    rectangle(rectangle &&) noexcept = default;
    auto operator=(rectangle &&) noexcept -> rectangle & = default;

    T left;
    T top;
    T right;
    T bottom;
};

template <typename T>
inline auto left(const rectangle<T> &rect) noexcept -> T
{
    return rect.left;
}

template <typename T>
inline auto top(const rectangle<T> &rect) noexcept -> T
{
    return rect.top;
}

template <typename T>
inline auto right(const rectangle<T> &rect) noexcept -> T
{
    return rect.right;
}

template <typename T>
inline auto bottom(const rectangle<T> &rect) noexcept -> T
{
    return rect.bottom;
}

template <typename T>
inline auto width(const rectangle<T> &rect) noexcept -> T
{
    return right(rect) - left(rect);
}

template <typename T>
inline auto height(const rectangle<T> &rect) noexcept -> T
{
    return bottom(rect) - top(rect);
}

template <typename T>
inline auto empty(const rectangle<T> &rect) noexcept -> bool
{
    return right(rect) == left(rect) || bottom(rect) == top(rect);
}

template <typename T>
inline auto size(const rectangle<T> &rect) noexcept -> size2d<T>
{
    return {width(rect), height(rect)};
}

template <typename T>
inline auto translate(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>
{
    return {rect.left + x, rect.top + y, rect.right + x, rect.bottom + y};
}

template <typename T>
inline auto translate(const rectangle<T> &rect, const math::vector2<T> &vec) noexcept -> rectangle<T>
{
    return translate(rect, vec.x, vec.y);
}

template <typename T>
inline auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool
{
    return left(lhs) == left(rhs) && top(lhs) == top(rhs) && right(lhs) == right(rhs) && bottom(lhs) == bottom(rhs);
}

template <typename T>
inline auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) * -rhs, top(lhs) * -rhs, right(lhs) * rhs, bottom(lhs) * rhs};
}

template <typename T>
inline auto operator*=(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return lhs * rhs;
}

} // namespace aeon::types
