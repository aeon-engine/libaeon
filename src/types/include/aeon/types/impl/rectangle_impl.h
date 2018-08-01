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
#include <aeon/types/coordinate.h>
#include <aeon/math/vector2.h>
#include <aeon/math/math.h>
#include <algorithm>

namespace aeon::types
{

template <typename T>
inline rectangle<T>::rectangle() noexcept
    : left{}
    , top{}
    , right{}
    , bottom{}
{
}

template <typename T>
inline rectangle<T>::rectangle(const T left, const T top, const T right, const T bottom) noexcept
    : left{left}
    , top{top}
    , right{right}
    , bottom{bottom}
{
}

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
inline auto left_top(const rectangle<T> &rect) noexcept -> coordinate<T>
{
    return {left(rect), top(rect)};
}

template <typename T>
inline auto right_top(const rectangle<T> &rect) noexcept -> coordinate<T>
{
    return {right(rect), top(rect)};
}

template <typename T>
inline auto left_bottom(const rectangle<T> &rect) noexcept -> coordinate<T>
{
    return {left(rect), bottom(rect)};
}

template <typename T>
inline auto right_bottom(const rectangle<T> &rect) noexcept -> coordinate<T>
{
    return {right(rect), bottom(rect)};
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
inline auto translate(const rectangle<T> &rect, const coordinate<T> &coord) noexcept -> rectangle<T>
{
    return translate(rect, coord.x, coord.y);
}

template <typename T>
inline auto contains(const rectangle<T> &inner, const rectangle<T> &outer) noexcept -> bool
{
    return (left(inner) >= left(outer) && top(inner) >= top(outer) && right(inner) <= right(outer) &&
            bottom(inner) <= bottom(outer));
}

template <typename T>
inline auto contains(const math::vector2<T> &vec, const rectangle<T> &rect) noexcept -> bool
{
    return (vec.x >= left(rect) && vec.y >= top(rect) && vec.x <= right(rect) && vec.y <= bottom(rect));
}

template <typename T>
inline auto contains(const coordinate<T> &coord, const rectangle<T> &rect) noexcept -> bool
{
    return (coord.x >= left(rect) && coord.y >= top(rect) && coord.x <= right(rect) && coord.y <= bottom(rect));
}

template <typename T>
inline auto overlaps(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> bool
{
    return left(rect1) < right(rect2) && left(rect2) < right(rect1) && top(rect1) < bottom(rect2) &&
           top(rect2) < bottom(rect1);
}

template <typename T>
inline auto intersection(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> rectangle<T>
{
    // clang-format off
    return {
        std::max(left(rect1), left(rect2)),
        std::max(top(rect1), top(rect2)),
        std::min(right(rect1), right(rect2)),
        std::min(bottom(rect1), bottom(rect2))};
    // clang-format on
}

template <typename T, typename... U>
inline auto bounding_box(const rectangle<T> &first, const rectangle<U> &... rectangles) noexcept -> rectangle<T>
{
    // clang-format off
    return {
        math::min(left(first), left(rectangles)...),
        math::min(top(first), top(rectangles)...),
        math::max(right(first), right(rectangles)...),
        math::max(bottom(first), bottom(rectangles)...)};
    // clang-format on
}

template <typename T>
inline auto inflate(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>
{
    return rect + val;
}

template <typename T>
inline auto scale(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>
{
    return rect * val;
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
inline auto operator+(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) - rhs, top(lhs) - rhs, right(lhs) + rhs, bottom(lhs) + rhs};
}

template <typename T>
inline auto operator+=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) + rhs, top(lhs) + rhs, right(lhs) - rhs, bottom(lhs) - rhs};
}

template <typename T>
inline auto operator-=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    return {left(lhs) * -rhs, top(lhs) * -rhs, right(lhs) * rhs, bottom(lhs) * rhs};
}

template <typename T>
inline auto operator*=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::types
