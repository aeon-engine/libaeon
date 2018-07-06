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

#include <aeon/math/vector4.h>

namespace aeon::math
{

inline auto operator*(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    // clang-format off
    return {
        (rhs.m00 * lhs.m00) + (rhs.m10 * lhs.m01) + (rhs.m20 * lhs.m02) + (rhs.m30 * lhs.m03),
        (rhs.m01 * lhs.m00) + (rhs.m11 * lhs.m01) + (rhs.m21 * lhs.m02) + (rhs.m31 * lhs.m03),
        (rhs.m02 * lhs.m00) + (rhs.m12 * lhs.m01) + (rhs.m22 * lhs.m02) + (rhs.m32 * lhs.m03),
        (rhs.m03 * lhs.m00) + (rhs.m13 * lhs.m01) + (rhs.m23 * lhs.m02) + (rhs.m33 * lhs.m03),

        (rhs.m00 * lhs.m10) + (rhs.m10 * lhs.m11) + (rhs.m20 * lhs.m12) + (rhs.m30 * lhs.m13),
        (rhs.m01 * lhs.m10) + (rhs.m11 * lhs.m11) + (rhs.m21 * lhs.m12) + (rhs.m31 * lhs.m13),
        (rhs.m02 * lhs.m10) + (rhs.m12 * lhs.m11) + (rhs.m22 * lhs.m12) + (rhs.m32 * lhs.m13),
        (rhs.m03 * lhs.m10) + (rhs.m13 * lhs.m11) + (rhs.m23 * lhs.m12) + (rhs.m33 * lhs.m13),

        (rhs.m00 * lhs.m20) + (rhs.m10 * lhs.m21) + (rhs.m20 * lhs.m22) + (rhs.m30 * lhs.m23),
        (rhs.m01 * lhs.m20) + (rhs.m11 * lhs.m21) + (rhs.m21 * lhs.m22) + (rhs.m31 * lhs.m23),
        (rhs.m02 * lhs.m20) + (rhs.m12 * lhs.m21) + (rhs.m22 * lhs.m22) + (rhs.m32 * lhs.m23),
        (rhs.m03 * lhs.m20) + (rhs.m13 * lhs.m21) + (rhs.m23 * lhs.m22) + (rhs.m33 * lhs.m23),

        (rhs.m00 * lhs.m30) + (rhs.m10 * lhs.m31) + (rhs.m20 * lhs.m32) + (rhs.m30 * lhs.m33),
        (rhs.m01 * lhs.m30) + (rhs.m11 * lhs.m31) + (rhs.m21 * lhs.m32) + (rhs.m31 * lhs.m33),
        (rhs.m02 * lhs.m30) + (rhs.m12 * lhs.m31) + (rhs.m22 * lhs.m32) + (rhs.m32 * lhs.m33),
        (rhs.m03 * lhs.m30) + (rhs.m13 * lhs.m31) + (rhs.m23 * lhs.m32) + (rhs.m33 * lhs.m33)};
    // clang-format on
}

inline auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>
{
    // clang-format off
    return {
        (lhs.m00 * rhs.x) + (lhs.m10 * rhs.y) + (lhs.m20 * rhs.z) + (lhs.m30 * rhs.w),
        (lhs.m01 * rhs.x) + (lhs.m11 * rhs.y) + (lhs.m21 * rhs.z) + (lhs.m31 * rhs.w),
        (lhs.m02 * rhs.x) + (lhs.m12 * rhs.y) + (lhs.m22 * rhs.z) + (lhs.m32 * rhs.w),
        (lhs.m03 * rhs.x) + (lhs.m13 * rhs.y) + (lhs.m23 * rhs.z) + (lhs.m33 * rhs.w)};
    // clang-format on
}

inline auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4
{
    // clang-format off
    return {
        lhs.m00 * rhs, lhs.m10 * rhs, lhs.m20 * rhs, lhs.m30 * rhs,
        lhs.m01 * rhs, lhs.m11 * rhs, lhs.m21 * rhs, lhs.m31 * rhs,
        lhs.m02 * rhs, lhs.m12 * rhs, lhs.m22 * rhs, lhs.m32 * rhs,
        lhs.m03 * rhs, lhs.m13 * rhs, lhs.m23 * rhs, lhs.m33 * rhs};
    // clang-format on
}

inline auto operator*=(mat4 &lhs, const mat4 &rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*=(mat4 &lhs, const float rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
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
