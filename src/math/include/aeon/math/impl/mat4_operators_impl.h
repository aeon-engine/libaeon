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

inline auto operator*(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    // clang-format off
    return {
        (lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10) + (lhs.m02 * rhs.m20) + (lhs.m03 * rhs.m30),
        (lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11) + (lhs.m02 * rhs.m21) + (lhs.m03 * rhs.m31),
        (lhs.m00 * rhs.m02) + (lhs.m01 * rhs.m12) + (lhs.m02 * rhs.m22) + (lhs.m03 * rhs.m32),
        (lhs.m00 * rhs.m03) + (lhs.m01 * rhs.m13) + (lhs.m02 * rhs.m23) + (lhs.m03 * rhs.m33),
        (lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10) + (lhs.m12 * rhs.m20) + (lhs.m13 * rhs.m30),
        (lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31),
        (lhs.m10 * rhs.m02) + (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32),
        (lhs.m10 * rhs.m03) + (lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33),
        (lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + (lhs.m22 * rhs.m20) + (lhs.m23 * rhs.m30),
        (lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31),
        (lhs.m20 * rhs.m02) + (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32),
        (lhs.m20 * rhs.m03) + (lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33),
        (lhs.m30 * rhs.m00) + (lhs.m31 * rhs.m10) + (lhs.m32 * rhs.m20) + (lhs.m33 * rhs.m30),
        (lhs.m30 * rhs.m01) + (lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31),
        (lhs.m30 * rhs.m02) + (lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32),
        (lhs.m30 * rhs.m03) + (lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33)};
    // clang-format on
}

inline auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>
{
    // clang-format off
    return {
        (lhs.m00 * rhs.x) + (lhs.m01 * rhs.y) + (lhs.m02 * rhs.z) + (lhs.m03 * rhs.w),
        (lhs.m10 * rhs.x) + (lhs.m11 * rhs.y) + (lhs.m12 * rhs.z) + (lhs.m13 * rhs.w),
        (lhs.m20 * rhs.x) + (lhs.m21 * rhs.y) + (lhs.m22 * rhs.z) + (lhs.m23 * rhs.w),
        (lhs.m30 * rhs.x) + (lhs.m31 * rhs.y) + (lhs.m32 * rhs.z) + (lhs.m33 * rhs.w)};
    // clang-format on
}

inline auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4
{
    // clang-format off
    return {
        lhs.m00 * rhs, lhs.m01 * rhs, lhs.m02 * rhs, lhs.m03 * rhs,
        lhs.m10 * rhs, lhs.m11 * rhs, lhs.m12 * rhs, lhs.m13 * rhs,
        lhs.m20 * rhs, lhs.m21 * rhs, lhs.m22 * rhs, lhs.m23 * rhs,
        lhs.m30 * rhs, lhs.m31 * rhs, lhs.m32 * rhs, lhs.m33 * rhs};
    // clang-format on
}

inline auto operator*=(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    return lhs * rhs;
}

inline auto operator*=(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>
{
    return lhs * rhs;
}

inline auto operator*=(const mat4 &lhs, const float rhs) noexcept -> mat4
{
    return lhs * rhs;
}

inline auto operator==(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    // clang-format off
    return
        lhs.m00 == rhs.m00 &&
        lhs.m10 == rhs.m10 &&
        lhs.m20 == rhs.m20 &&
        lhs.m30 == rhs.m30 &&
        lhs.m01 == rhs.m01 &&
        lhs.m11 == rhs.m11 &&
        lhs.m21 == rhs.m21 &&
        lhs.m31 == rhs.m31 &&
        lhs.m02 == rhs.m02 &&
        lhs.m12 == rhs.m12 &&
        lhs.m22 == rhs.m22 &&
        lhs.m32 == rhs.m32 &&
        lhs.m03 == rhs.m03 &&
        lhs.m13 == rhs.m13 &&
        lhs.m23 == rhs.m23 &&
        lhs.m33 == rhs.m33;
    // clang-format on
}

inline auto operator!=(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
