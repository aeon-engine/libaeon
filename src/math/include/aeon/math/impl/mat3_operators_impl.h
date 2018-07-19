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
        lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
        lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
        lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],

        lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
        lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
        lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],

        lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2],
        lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2],
        lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]};
    // clang-format on
}

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>
{
    // clang-format off
    return {
        lhs[0][0] * rhs.x + lhs[0][1] * rhs.y + lhs[0][2] * rhs.z,
        lhs[1][0] * rhs.x + lhs[1][1] * rhs.y + lhs[1][2] * rhs.z,
        lhs[2][0] * rhs.x + lhs[2][1] * rhs.y + lhs[2][2] * rhs.z};
    // clang-format on
}

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3
{
    // clang-format off
    return {
        lhs[0][0] * rhs, lhs[0][1] * rhs, lhs[0][2] * rhs,
        lhs[1][0] * rhs, lhs[1][1] * rhs, lhs[1][2] * rhs,
        lhs[2][0] * rhs, lhs[2][1] * rhs, lhs[2][2] * rhs};
    // clang-format on
}

inline auto operator-(const mat3 &mat) noexcept -> mat3
{
    // clang-format off
    return {
        -mat[0][0], -mat[0][1], -mat[0][2],
        -mat[1][0], -mat[1][1], -mat[1][2],
        -mat[2][0], -mat[2][1], -mat[2][2]};
    // clang-format on
}

inline auto operator*=(mat3 &lhs, const mat3 &rhs) noexcept -> mat3 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*=(mat3 &lhs, const float rhs) noexcept -> mat3 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

inline auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
