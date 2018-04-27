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

namespace aeon::math
{

inline mat3::mat3() noexcept
    : m00{0.0f}
    , m10{0.0f}
    , m20{0.0f}
    , m01{0.0f}
    , m11{0.0f}
    , m21{0.0f}
    , m02{0.0f}
    , m12{0.0f}
    , m22{0.0f}
{
}

inline mat3::mat3(const float m00, const float m10, const float m20, const float m01, const float m11, const float m21,
                  const float m02, const float m12, const float m22) noexcept
    : m00{m00}
    , m10{m10}
    , m20{m20}
    , m01{m01}
    , m11{m11}
    , m21{m21}
    , m02{m02}
    , m12{m12}
    , m22{m22}
{
}

inline auto mat3::at(const int row, const int column) const noexcept -> float
{
    const auto value = ptr(*this);
    return value[(column * 3) + row];
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
    return scale(vector2<float>{xy});
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

inline auto determinant(const mat3 &mat) noexcept -> float
{
    return (mat.m00 * mat.m11 * mat.m22) + (mat.m01 * mat.m12 * mat.m20) + (mat.m02 * mat.m10 * mat.m21) -
           (mat.m02 * mat.m11 * mat.m20) - (mat.m01 * mat.m10 * mat.m22) - (mat.m00 * mat.m12 * mat.m21);
}

inline auto qr_decompose(const mat3 &mat, vector3<float> &scale, vector3<float> &shear) noexcept -> mat3
{
    auto inv_length = 1.0f / std::sqrt(mat.m00 * mat.m00 + mat.m10 * mat.m10 + mat.m20 * mat.m20);

    mat3 q;

    q.m00 = mat.m00 * inv_length;
    q.m10 = mat.m10 * inv_length;
    q.m20 = mat.m20 * inv_length;

    auto dot = q.m00 * mat.m01 + q.m10 * mat.m11 + q.m20 * mat.m21;

    q.m01 = mat.m01 - dot * q.m00;
    q.m11 = mat.m11 - dot * q.m10;
    q.m21 = mat.m21 - dot * q.m20;

    inv_length = 1.0f / std::sqrt(q.m01 * q.m01 + q.m11 * q.m11 + q.m21 * q.m21);

    q.m01 *= inv_length;
    q.m11 *= inv_length;
    q.m21 *= inv_length;

    dot = q.m00 * mat.m02 + q.m10 * mat.m12 + q.m20 * mat.m22;
    q.m02 = mat.m02 - dot * q.m00;
    q.m12 = mat.m12 - dot * q.m10;
    q.m22 = mat.m22 - dot * q.m20;

    dot = q.m01 * mat.m02 + q.m11 * mat.m12 + q.m21 * mat.m22;
    q.m02 -= dot * q.m01;
    q.m12 -= dot * q.m11;
    q.m22 -= dot * q.m21;

    inv_length = 1.0f / std::sqrt(q.m02 * q.m02 + q.m12 * q.m12 + q.m22 * q.m22);

    q.m02 *= inv_length;
    q.m12 *= inv_length;
    q.m22 *= inv_length;

    if (determinant(q) < 0.0f)
        q = -q;

    mat3 r;
    r.m00 = q.m00 * mat.m00 + q.m10 * mat.m10 + q.m20 * mat.m20;
    r.m01 = q.m00 * mat.m01 + q.m10 * mat.m11 + q.m20 * mat.m21;
    r.m11 = q.m01 * mat.m01 + q.m11 * mat.m11 + q.m21 * mat.m21;
    r.m02 = q.m00 * mat.m02 + q.m10 * mat.m12 + q.m20 * mat.m22;
    r.m12 = q.m01 * mat.m02 + q.m11 * mat.m12 + q.m21 * mat.m22;
    r.m22 = q.m02 * mat.m02 + q.m12 * mat.m12 + q.m22 * mat.m22;

    scale.set(r.m00, r.m11, r.m22);

    const auto inv_rm00 = 1.0f / r.m00;
    shear.set(r.m01 * inv_rm00, r.m02 * inv_rm00, r.m12 / r.m11);

    return q;
}

inline auto ptr(mat3 &mat) noexcept -> float *
{
    return &mat.m00;
}

inline auto ptr(const mat3 &mat) noexcept -> const float *
{
    return &mat.m00;
}

} // namespace aeon::math
