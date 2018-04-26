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

#include <aeon/math/vector3.h>
#include <aeon/math/vector4.h>
#include <cmath>

namespace aeon::math
{

class mat3
{
public:
    static auto zero() noexcept -> mat3;

    static auto indentity() noexcept -> mat3;

    static auto scale(const vector2<float> &vec) noexcept -> mat3;

    static auto translate(const vector2<float> &vec) noexcept -> mat3;

    static auto rotate(const float angle) noexcept -> mat3;

    float m00 = 0.0f;
    float m10 = 0.0f;
    float m20 = 0.0f;
    float m01 = 0.0f;
    float m11 = 0.0f;
    float m21 = 0.0f;
    float m02 = 0.0f;
    float m12 = 0.0f;
    float m22 = 0.0f;
    float m03 = 0.0f;
    float m13 = 0.0f;
    float m23 = 0.0f;
};

inline auto operator*(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3;

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>;

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3;

inline auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

inline auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

inline auto inverse(const mat3 &mat) noexcept -> mat3;

inline auto ptr(mat3 &mat) noexcept -> float *;

inline auto ptr(const mat3 &mat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/mat3_impl.h>
#include <aeon/math/impl/mat3_operators_impl.h>
