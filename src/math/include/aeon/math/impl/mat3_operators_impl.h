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

inline auto operator*(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
{
    // clang-format off
    return {
		lhs.m00 * rhs.m00 + lhs.m10 * rhs.m01 + lhs.m20 * rhs.m02,
		lhs.m01 * rhs.m00 + lhs.m11 * rhs.m01 + lhs.m21 * rhs.m02,
		lhs.m02 * rhs.m00 + lhs.m12 * rhs.m01 + lhs.m22 * rhs.m02,
		lhs.m00 * rhs.m10 + lhs.m10 * rhs.m11 + lhs.m20 * rhs.m12,
		lhs.m01 * rhs.m10 + lhs.m11 * rhs.m11 + lhs.m21 * rhs.m12,
		lhs.m02 * rhs.m10 + lhs.m12 * rhs.m11 + lhs.m22 * rhs.m12,
		lhs.m00 * rhs.m20 + lhs.m10 * rhs.m21 + lhs.m20 * rhs.m22,
		lhs.m01 * rhs.m20 + lhs.m11 * rhs.m21 + lhs.m21 * rhs.m22,
		lhs.m02 * rhs.m20 + lhs.m12 * rhs.m21 + lhs.m22 * rhs.m22};
    // clang-format on
}

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>
{
    // clang-format off
    return {
        lhs.m00 * rhs.x + lhs.m10 * rhs.y + lhs.m20 * rhs.z,
		lhs.m01 * rhs.x + lhs.m11 * rhs.y + lhs.m21 * rhs.z,
		lhs.m02 * rhs.x + lhs.m12 * rhs.y + lhs.m22 * rhs.z};
    // clang-format on
}

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3
{
    // clang-format off
    return {
        lhs.m00 * rhs, lhs.m10 * rhs, lhs.m20 * rhs,
        lhs.m01 * rhs, lhs.m11 * rhs, lhs.m21 * rhs,
        lhs.m02 * rhs, lhs.m12 * rhs, lhs.m22 * rhs};
    // clang-format on
}

inline auto operator-(const mat3 &mat) noexcept -> mat3
{
    // clang-format off
    return {
        -mat.m00, -mat.m10, -mat.m20,
        -mat.m01, -mat.m11, -mat.m21,
        -mat.m02, -mat.m12, -mat.m22};
    // clang-format on
}

inline auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    // clang-format off
    return
        lhs.m00 == rhs.m00 &&
        lhs.m10 == rhs.m10 &&
        lhs.m20 == rhs.m20 &&
        lhs.m01 == rhs.m01 &&
        lhs.m11 == rhs.m11 &&
        lhs.m21 == rhs.m21 &&
        lhs.m02 == rhs.m02 &&
        lhs.m12 == rhs.m12 &&
        lhs.m22 == rhs.m22;
    // clang-format on
}

inline auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
