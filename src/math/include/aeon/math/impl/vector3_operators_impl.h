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
inline auto operator+(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <typename T>
inline auto operator+(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

template <typename T>
inline auto operator+(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z, rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
}

template <typename T>
inline auto operator-(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs - rhs.x, lhs - rhs.y, lhs - rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {-vec.x, -vec.y, -vec.z};
}

template <typename T>
inline auto operator*(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template <typename T>
inline auto operator*(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

template <typename T>
inline auto operator*(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

template <typename T>
inline auto operator/(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template <typename T>
inline auto operator/(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

template <typename T>
inline auto operator==(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T>
inline auto operator!=(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);
}

template <typename T>
inline auto operator>(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z);
}

} // namespace aeon::math
