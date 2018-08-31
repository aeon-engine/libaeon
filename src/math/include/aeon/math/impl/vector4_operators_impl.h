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

namespace aeon::math
{

template <typename T>
inline auto operator+(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

template <typename T>
inline auto operator+(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs};
}

template <typename T>
inline auto operator+(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w};
}

template <typename T>
inline auto operator-(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z, rhs.z, lhs.w - rhs.w};
}

template <typename T>
inline auto operator-(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs};
}

template <typename T>
inline auto operator-(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w};
}

template <typename T>
inline auto operator-(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {-vec.x, -vec.y, -vec.z, -vec.w};
}

template <typename T>
inline auto operator*(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w};
}

template <typename T>
inline auto operator*(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
}

template <typename T>
inline auto operator*(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w};
}

template <typename T>
inline auto operator/(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
}

template <typename T, typename U>
inline auto operator*(const vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) * rhs.z), static_cast<T>(static_cast<U>(lhs.w) * rhs.w)};
}

template <typename T, typename U>
inline auto operator*(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs),
            static_cast<T>(static_cast<U>(lhs.z) * rhs), static_cast<T>(static_cast<U>(lhs.w) * rhs)};
}

template <typename T, typename U>
inline auto operator/(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs),
            static_cast<T>(static_cast<U>(lhs.z) / rhs), static_cast<T>(static_cast<U>(lhs.w) / rhs)};
}

template <typename T>
inline auto operator+=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator/=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator/=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline auto operator==(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

template <typename T>
inline auto operator!=(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w);
}

template <typename T>
inline auto operator>(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w);
}

} // namespace aeon::math
