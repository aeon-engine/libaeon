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

#include <aeon/math/math.h>
#include <aeon/math/vector2.h>
#include <aeon/types/size2d.h>
#include <aeon/types/rectangle.h>

namespace aeon::types
{

template <typename T>
circle<T>::circle(const T radius) noexcept
    : position{}
    , radius{radius}
{
}

template <typename T>
circle<T>::circle(const math::vector2<T> position, const T radius) noexcept
    : position{position}
    , radius{radius}
{
}

template <typename T>
inline auto position(const circle<T> &c) noexcept -> math::vector2<T>
{
    return c.position;
}

template <typename T>
inline auto center(const circle<T> &c) noexcept -> math::vector2<T>
{
    return position(c);
}

template <typename T>
inline auto empty(const circle<T> &c) noexcept -> bool
{
    return c.radius == T(0);
}

template <typename T>
inline auto size(const circle<T> &c) noexcept -> size2d<T>
{
    const auto d = diameter(c);
    return {d, d};
}

template <typename T>
inline auto radius(const circle<T> &c) noexcept -> T
{
    return c.radius;
}

template <typename T>
inline auto diameter(const circle<T> &c) noexcept -> T
{
    return radius(c) * T(2);
}

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type *>
inline auto circumference(const circle<T> &c) noexcept -> float
{
    return static_cast<float>(diameter(c)) * math::constants<float>::pi;
}

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type *>
inline auto circumference(const circle<T> &c) noexcept -> T
{
    return diameter(c) * math::constants<T>::pi;
}

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type *>
inline auto area(const circle<T> &c) noexcept -> float
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return math::constants<float>::pi * static_cast<float>(r2);
}

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type *>
inline auto area(const circle<T> &c) noexcept -> T
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return math::constants<T>::pi * r2;
}

template <typename T>
inline auto set_position(const circle<T> &c, const T x, const T y) noexcept -> circle<T>
{
    return set_position(c, math::vector2{x, y});
}

template <typename T>
inline auto set_position(const circle<T> &c, const math::vector2<T> &vec) noexcept -> circle<T>
{
    return {vec, radius(c)};
}

template <typename T>
inline auto inflate(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) + val};
}

template <typename T>
inline auto scale(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) * val};
}

template <typename T>
inline auto rect(const circle<T> &c) noexcept -> rectangle<T>
{
    const auto r = radius(c);
    const auto d = diameter(c);
    const auto pos = position(c);
    const auto left = pos.x - r;
    const auto top = pos.y - r;
    return {left, top, left + d, top + d};
}

template <typename T>
inline auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return position(lhs) == position(rhs) && radius(lhs) == radius(rhs);
}

template <typename T>
inline auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::types
