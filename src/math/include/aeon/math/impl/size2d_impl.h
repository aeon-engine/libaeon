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

#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <algorithm>

namespace aeon::math
{

template <typename T>
inline size2d<T>::size2d() noexcept
    : width{}
    , height{}
{
}

template <typename T>
inline size2d<T>::size2d(const T width, const T height) noexcept
    : width{width}
    , height{height}
{
}

template <typename T>
template <typename U>
inline size2d<T>::size2d(const U width, const U height) noexcept
    : width{static_cast<T>(width)}
    , height{static_cast<T>(height)}
{
}

template <typename T>
template <typename U>
inline size2d<T>::size2d(const convert_type, const U &t) noexcept
    : width{static_cast<T>(t.width)}
    , height{static_cast<T>(t.height)}
{
}

template <typename T>
template <typename U>
auto size2d<T>::convert_to() const noexcept -> U
{
    return U{width, height};
}

template <typename T>
inline auto width(const size2d<T> &size) noexcept -> T
{
    return size.width;
}

template <typename T>
inline auto height(const size2d<T> &size) noexcept -> T
{
    return size.height;
}

template <typename T>
inline auto area(const size2d<T> &size) noexcept -> T
{
    return width(size) * height(size);
}

template <typename T>
inline auto empty(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) || height(size) == T(0);
}

template <typename T>
inline auto null(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) && height(size) == T(0);
}

template <typename T>
inline auto valid(const size2d<T> &size) noexcept -> bool
{
    return width(size) >= T(0) && height(size) >= T(0);
}

template <typename T>
inline auto rect(const size2d<T> &size) noexcept -> rectangle<T>
{
    return {0, 0, width(size), height(size)};
}

template <typename T>
inline auto contains(const vector2<T> &vec, const size2d<T> size) noexcept -> bool
{
    return (vec.x < width(size) && vec.y < height(size));
}

template <typename T>
inline constexpr void inflate(size2d<T> &size, const T val) noexcept
{
    size = inflated(size, val);
}

template <typename T>
inline constexpr auto inflated(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size + val;
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const T val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const T x, const T y) noexcept
{
    size = scaled(size, x, y);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const vector2<T> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const size2d<T> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T x, const T y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const vector2<T> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const size2d<T> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U x, const U y) noexcept
{
    size = scaled(size, x, y);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const vector2<U> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const size2d<U> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U x, const U y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const vector2<U> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <typename T>
constexpr auto min(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::min(a.width, b.width), std::min(a.height, b.height)};
}

template <typename T>
constexpr auto max(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::max(a.width, b.width), std::max(a.height, b.height)};
}

template <typename T>
constexpr auto clamp(const size2d<T> &val, const size2d<T> &min_size, const size2d<T> &max_size) noexcept -> size2d<T>
{
    return max(min_size, min(max_size, val));
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const size2d<U> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T>
inline auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return lhs.width == rhs.width && lhs.height == rhs.height;
}

template <typename T>
inline auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width + rhs.width, lhs.height + rhs.height};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width + rhs, lhs.height + rhs};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width - rhs.width, lhs.height - rhs.height};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width - rhs, lhs.height - rhs};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width * rhs.width, lhs.height * rhs.height};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width * rhs.x, lhs.height * rhs.y};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width * rhs, lhs.height * rhs};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(lhs.width) * rhs.width),
            static_cast<T>(static_cast<U>(lhs.height) * rhs.height)};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(lhs.width) * rhs.x), static_cast<T>(static_cast<U>(lhs.height) * rhs.y)};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(lhs.width) * rhs), static_cast<T>(static_cast<U>(lhs.height) * rhs)};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::math
