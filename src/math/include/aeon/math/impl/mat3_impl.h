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

#include <aeon/math/quaternion.h>
#include <aeon/math/vector2.h>
#include <aeon/math/vector3.h>
#include <aeon/math/mat4.h>
#include <aeon/common/assert.h>

namespace aeon::math
{

inline mat3::mat3() noexcept = default;

inline mat3::mat3(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12,
                  const float m20, const float m21, const float m22) noexcept
{
    column[0] = vector3{m00, m10, m20};
    column[1] = vector3{m01, m11, m21};
    column[2] = vector3{m02, m12, m22};
}

inline mat3::mat3(const mat4 &m) noexcept
{
    column[0] = vector3{m[0][0], m[0][1], m[0][2]};
    column[1] = vector3{m[1][0], m[1][1], m[1][2]};
    column[2] = vector3{m[2][0], m[2][1], m[2][2]};
}

inline mat3::mat3(const quaternion &q) noexcept
{
    const auto qxx = q.x * q.x;
    const auto qyy = q.y * q.y;
    const auto qzz = q.z * q.z;
    const auto qxz = q.x * q.z;
    const auto qxy = q.x * q.y;
    const auto qyz = q.y * q.z;
    const auto qwx = q.w * q.x;
    const auto qwy = q.w * q.y;
    const auto qwz = q.w * q.z;

    column[0].set(1.0f - 2.0f * (qyy + qzz), 2.0f * (qxy + qwz), 2.0f * (qxz - qwy));
    column[1].set(2.0f * (qxy - qwz), 1.0f - 2.0f * (qxx + qzz), 2.0f * (qyz + qwx));
    column[2].set(2.0f * (qxz + qwy), 2.0f * (qyz - qwx), 1.0f - 2.0f * (qxx + qyy));
}

inline auto mat3::operator[](const std::size_t i) noexcept -> vector3<float> &
{
    aeon_assert_array_bounds(column, i);
    return column[i];
}

inline auto mat3::operator[](const std::size_t i) const noexcept -> const vector3<float> &
{
    aeon_assert_array_bounds(column, i);
    return column[i];
}

inline auto mat3::at(const int column, const int row) const noexcept -> float
{
    return operator[](column)[row];
}

inline auto mat3::zero() noexcept -> mat3
{
    return {};
}

inline auto mat3::indentity() noexcept -> mat3
{
    // clang-format off
    return {1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};
    // clang-format on
}

inline auto mat3::scale(const float xy) noexcept -> mat3
{
    return scale(vector2{xy});
}

inline auto mat3::scale(const float x, const float y) noexcept -> mat3
{
    return scale({x, y});
}

inline auto mat3::scale(const vector2<float> &vec) noexcept -> mat3
{
    // clang-format off
    return {vec.x, 0.0f,  0.0f,
            0.0f,  vec.y, 0.0f,
            0.0f,  0.0f,  1.0f};
    // clang-format on
}

template <typename T>
inline auto mat3::scale(const T xy) noexcept -> mat3
{
    return scale(static_cast<float>(xy));
}

template <typename T>
inline auto mat3::scale(const T x, const T y) noexcept -> mat3
{
    return scale(static_cast<float>(x), static_cast<float>(y));
}

template <typename T>
inline auto mat3::scale(const vector2<T> &vec) noexcept -> mat3
{
    return scale(vector2<float>{vec});
}

inline auto mat3::translate(const float x, const float y) noexcept -> mat3
{
    return translate({x, y});
}

inline auto mat3::translate(const vector2<float> &vec) noexcept -> mat3
{
    // clang-format off
    return {1.0f, 0.0f, vec.x,
            0.0f, 1.0f, vec.y,
            0.0f, 0.0f, 1.0f};
    // clang-format on
}

template <typename T>
inline auto mat3::translate(const T x, const T y) noexcept -> mat3
{
    return translate(static_cast<float>(x), static_cast<float>(y));
}

template <typename T>
inline auto mat3::translate(const vector2<T> &vec) noexcept -> mat3
{
    return translate(vector2{vec});
}

inline auto mat3::rotate(const float angle) noexcept -> mat3
{
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);

    // clang-format off
    return {
        c,    -s,   0.0f,
        s,    c,    0.0f,
        0.0f, 0.0f, 1.0f
    };
    // clang-format on
}

template <typename T>
inline auto mat3::rotate(const T angle) noexcept -> mat3
{
    return rotate(static_cast<float>(angle));
}

inline auto determinant(const mat3 &mat) noexcept -> float
{
    return (mat[0][0] * mat[1][1] * mat[2][2]) + (mat[1][0] * mat[2][1] * mat[0][2]) +
           (mat[2][0] * mat[0][1] * mat[1][2]) - (mat[2][0] * mat[1][1] * mat[0][2]) -
           (mat[1][0] * mat[0][1] * mat[2][2]) - (mat[0][0] * mat[2][1] * mat[1][2]);
}

inline auto qr_decompose(const mat3 &mat, vector3<float> &scale, vector3<float> &shear) noexcept -> mat3
{
    mat3 q;

    q[0] = mat[0] * (1.0f / length(mat[0]));

    q[1] = mat[1] - dot(q[0], mat[1]) * q[0];
    q[1] *= (1.0f / length(mat[1]));

    q[2] = mat[2] - dot(q[0], mat[2]) * q[0];
    q[2] -= dot(q[1], mat[2]) * q[1];
    q[2] *= (1.0f / length(mat[2]));

    if (determinant(q) < 0.0f)
        q = -q;

    mat3 r;

    r[0][0] = q[0][0] * mat[0][0] + q[0][1] * mat[0][1] + q[0][2] * mat[0][2];
    r[1][0] = q[0][0] * mat[1][0] + q[0][1] * mat[1][1] + q[0][2] * mat[1][2];
    r[1][1] = q[1][0] * mat[1][0] + q[1][1] * mat[1][1] + q[1][2] * mat[1][2];
    r[2][0] = q[0][0] * mat[2][0] + q[0][1] * mat[2][1] + q[0][2] * mat[2][2];
    r[2][1] = q[1][0] * mat[2][0] + q[1][1] * mat[2][1] + q[1][2] * mat[2][2];
    r[2][2] = q[2][0] * mat[2][0] + q[2][1] * mat[2][1] + q[2][2] * mat[2][2];

    scale.set(r[0][0], r[1][1], r[2][2]);

    const auto inv_rm00 = 1.0f / r[0][0];
    shear.set(r[1][0] * inv_rm00, r[2][0] * inv_rm00, r[2][1] / r[1][1]);

    return q;
}

inline auto ptr(mat3 &mat) noexcept -> float *
{
    return &mat[0][0];
}

inline auto ptr(const mat3 &mat) noexcept -> const float *
{
    return &mat[0][0];
}

} // namespace aeon::math
