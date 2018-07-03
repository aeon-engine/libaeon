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

inline auto operator+(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline auto operator-(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline auto operator*(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
            lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x};
}

inline auto operator*(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

inline auto operator/(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w / rhs.w, lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

inline auto operator/(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return {lhs.w / rhs, lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

inline auto operator+=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return lhs + rhs;
}

inline auto operator-=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return lhs - rhs;
}

inline auto operator*=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return lhs * rhs;
}

inline auto operator*=(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return lhs * rhs;
}

inline auto operator/=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return lhs / rhs;
}

inline auto operator/=(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return lhs / rhs;
}

inline auto operator==(const quaternion &lhs, const quaternion &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

inline auto operator!=(const quaternion &lhs, const quaternion &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
