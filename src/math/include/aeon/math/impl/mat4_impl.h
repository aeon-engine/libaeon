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
#include <aeon/math/mat3.h>
#include <aeon/math/quaternion.h>
#include <cmath>

namespace aeon::math
{

inline mat4::mat4() noexcept
    : m00{0.0f}
    , m10{0.0f}
    , m20{0.0f}
    , m30{0.0f}
    , m01{0.0f}
    , m11{0.0f}
    , m21{0.0f}
    , m31{0.0f}
    , m02{0.0f}
    , m12{0.0f}
    , m22{0.0f}
    , m32{0.0f}
    , m03{0.0f}
    , m13{0.0f}
    , m23{0.0f}
    , m33{0.0f}
{
}

inline mat4::mat4(const float m00, const float m10, const float m20, const float m30, const float m01, const float m11,
                  const float m21, const float m31, const float m02, const float m12, const float m22, const float m32,
                  const float m03, const float m13, const float m23, const float m33) noexcept
    : m00{m00}
    , m10{m10}
    , m20{m20}
    , m30{m30}
    , m01{m01}
    , m11{m11}
    , m21{m21}
    , m31{m31}
    , m02{m02}
    , m12{m12}
    , m22{m22}
    , m32{m32}
    , m03{m03}
    , m13{m13}
    , m23{m23}
    , m33{m33}
{
}

inline mat4::mat4(const mat3 &m) noexcept
    : m00{m.m00}
    , m10{m.m10}
    , m20{m.m20}
    , m30{0.0f}
    , m01{m.m01}
    , m11{m.m11}
    , m21{m.m21}
    , m31{0.0f}
    , m02{m.m02}
    , m12{m.m12}
    , m22{m.m22}
    , m32{0.0f}
    , m03{0.0f}
    , m13{0.0f}
    , m23{0.0f}
    , m33{1.0f}
{
}

inline mat4::mat4(const quaternion &q) noexcept
    : mat4{mat3{q}}
{
}

inline auto mat4::at(const int row, const int column) const noexcept -> float
{
    const auto value = ptr(*this);
    return value[(column * 4) + row];
}

inline auto mat4::zero() noexcept -> mat4
{
    return {};
}

inline auto mat4::indentity() noexcept -> mat4
{
    // clang-format off
    return {1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};
    // clang-format on
}

inline auto mat4::scale(const float xyz) noexcept -> mat4
{
    return scale(vector3<float>{xyz});
}

inline auto mat4::scale(const float x, const float y, const float z) noexcept -> mat4
{
    return scale({x, y, z});
}

inline auto mat4::scale(const vector3<float> &vec) noexcept -> mat4
{
    // clang-format off
    return {vec.x, 0.0f,  0.0f,  0.0f,
            0.0f,  vec.y, 0.0f,  0.0f,
            0.0f,  0.0f,  vec.z, 0.0f,
            0.0f,  0.0f,  0.0f,  1.0f};
    // clang-format on
}

template <typename T>
inline auto mat4::scale(const T xyz) noexcept -> mat4
{
    return scale(static_cast<float>(xyz));
}

template <typename T>
inline auto mat4::scale(const T x, const T y, const T z) noexcept -> mat4
{
    return scale(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

template <typename T>
inline auto mat4::scale(const vector3<T> &vec) noexcept -> mat4
{
    return scale(vector3<float>{vec});
}

inline auto mat4::translate(const float x, const float y) noexcept -> mat4
{
    return translate({x, y, 0.0f});
}

inline auto mat4::translate(const float x, const float y, const float z) noexcept -> mat4
{
    return translate({x, y, z});
}

inline auto mat4::translate(const vector3<float> &vec) noexcept -> mat4
{
    // clang-format off
    return {1.0f, 0.0f, 0.0f, vec.x,
            0.0f, 1.0f, 0.0f, vec.y,
            0.0f, 0.0f, 1.0f, vec.z,
            0.0f, 0.0f, 0.0f, 1.0f};
    // clang-format on
}

template <typename T>
inline auto mat4::translate(const T x, const T y) noexcept -> mat4
{
    return translate(static_cast<float>(x), static_cast<float>(y));
}

template <typename T>
inline auto mat4::translate(const T x, const T y, const T z) noexcept -> mat4
{
    return translate(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

template <typename T>
inline auto mat4::translate(const vector3<T> &vec) noexcept -> mat4
{
    return translate(vector3<float>{vec});
}

inline auto mat4::rotate(const float angle, const vector3<float> &vec) noexcept -> mat4
{
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);
    const auto axis = normalized(vec);

    // clang-format off
    return {
        c + (1.0f - c) * axis.x * axis.x,
        (1.0f - c) * axis.x * axis.y + s * axis.z,
        (1.0f - c) * axis.x * axis.z - s * axis.y,
        0.0f,

        (1.0f - c) * axis.y * axis.x - s * axis.z,
        c + (1.0f - c) * axis.y * axis.y,
        (1.0f - c) * axis.y * axis.z + s * axis.x,
        0.0f,

        (1.0f - c) * axis.z * axis.x + s * axis.y,
        (1.0f - c) * axis.z * axis.y - s * axis.x,
        c + (1.0f - c) * axis.z * axis.z,
        0.0f,

        0.0f,
        0.0f,
        0.0f,
        1.0f
    };
    // clang-format on
}

template <typename T, typename U>
inline auto mat4::rotate(const T angle, const vector3<U> &vec) noexcept -> mat4
{
    return rotate(static_cast<float>(angle), vector3<float>{vec});
}

inline auto mat4::ortho(const float left, const float right, const float bottom, const float top) noexcept -> mat4
{
    // clang-format off
    return {
        2.0f / (right - left),
        0.0f,
        0.0f,
        0.0f,

        0.0f,
        2.0f / (top - bottom),
        0.0f,
        0.0f,

        0.0f,
        0.0f,
        -1.0f,
        0.0f,

        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        0.0f,
        1.0f
    };
    // clang-format on
}

inline auto mat4::ortho(const float left, const float right, const float bottom, const float top, const float near,
                        const float far) noexcept -> mat4
{
    // clang-format off
    return {
        2.0f / (right - left),
        0.0f,
        0.0f,
        0.0f,

        0.0f,
        2.0f / (top - bottom),
        0.0f,
        0.0f,

        0.0f,
        0.0f,
        -2.0f / (far - near),
        0.0f,

        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(far + near) / (far - near),
        1.0f
    };
    // clang-format on
}

template <typename T>
inline auto mat4::ortho(const T left, const T right, const T bottom, const T top) noexcept -> mat4
{
    return mat4::ortho(static_cast<float>(left), static_cast<float>(right), static_cast<float>(bottom),
                       static_cast<float>(top));
}

template <typename T, typename U>
inline auto mat4::ortho(const T left, const T right, const T bottom, const T top, const U near, const U far) noexcept
    -> mat4
{
    return mat4::ortho(static_cast<float>(left), static_cast<float>(right), static_cast<float>(bottom),
                       static_cast<float>(top), static_cast<float>(near), static_cast<float>(far));
}

inline auto mat4::projection(const float fov_y, const float aspect_ratio, const float near, const float far) noexcept
    -> mat4
{
    const auto tan_half_fov_y = std::tan(0.5f * fov_y);

    // clang-format off
    return {
        1.0f / (aspect_ratio * tan_half_fov_y),
        0.0f,
        0.0f,
        0.0f,

        0.0f,
        1.0f / tan_half_fov_y,
        0.0f,
        0.0f,

        0.0f,
        0.0f,
        -(far + near) / (far - near),
        1.0f,

        0.0f,
        0.0f,
        -(2.0f * far * near) / (far - near),
        1.0f
    };
    // clang-format on
}

template <typename T, typename U>
inline auto mat4::projection(const T fov_y, const T aspect_ratio, const U near, const U far) noexcept -> mat4
{
    return projection(static_cast<float>(fov_y), static_cast<float>(aspect_ratio), static_cast<float>(near),
                      static_cast<float>(far));
}

inline auto mat4::projection_fov(const float fov, const float width, const float height, const float near,
                                 const float far) noexcept -> mat4
{
    const auto h = std::cos(0.5f * fov) / std::sin(0.5f * fov);
    const auto w = h * height / width;

    // clang-format off
    return {
        w,
        0.0f,
        0.0f,
        0.0f,

        0.0f,
        h,
        0.0f,
        0.0f,

        0.0f,
        0.0f,
        -(far + near) / (far - near),
        -1.0f,

        0.0f,
        0.0f,
        -(2.0f * far * near) / (far - near),
        1.0f
    };
    // clang-format on
}

template <typename T, typename U>
inline auto mat4::projection_fov(const T fov, const T width, const T height, const U near, const U far) noexcept -> mat4
{
    return projection_fov(static_cast<float>(fov), static_cast<float>(width), static_cast<float>(height),
                          static_cast<float>(near), static_cast<float>(far));
}

inline auto inverse(const mat4 &mat) noexcept -> mat4
{
    auto v0 = mat.m20 * mat.m31 - mat.m21 * mat.m30;
    auto v1 = mat.m20 * mat.m32 - mat.m22 * mat.m30;
    auto v2 = mat.m20 * mat.m33 - mat.m23 * mat.m30;
    auto v3 = mat.m21 * mat.m32 - mat.m22 * mat.m31;
    auto v4 = mat.m21 * mat.m33 - mat.m23 * mat.m31;
    auto v5 = mat.m22 * mat.m33 - mat.m23 * mat.m32;

    const auto t00 = +(v5 * mat.m11 - v4 * mat.m12 + v3 * mat.m13);
    const auto t10 = -(v5 * mat.m10 - v2 * mat.m12 + v1 * mat.m13);
    const auto t20 = +(v4 * mat.m10 - v2 * mat.m11 + v0 * mat.m13);
    const auto t30 = -(v3 * mat.m10 - v1 * mat.m11 + v0 * mat.m12);

    const auto inverse_determinant = 1 / (t00 * mat.m00 + t10 * mat.m01 + t20 * mat.m02 + t30 * mat.m03);

    const auto d00 = t00 * inverse_determinant;
    const auto d10 = t10 * inverse_determinant;
    const auto d20 = t20 * inverse_determinant;
    const auto d30 = t30 * inverse_determinant;

    const auto d01 = -(v5 * mat.m01 - v4 * mat.m02 + v3 * mat.m03) * inverse_determinant;
    const auto d11 = +(v5 * mat.m00 - v2 * mat.m02 + v1 * mat.m03) * inverse_determinant;
    const auto d21 = -(v4 * mat.m00 - v2 * mat.m01 + v0 * mat.m03) * inverse_determinant;
    const auto d31 = +(v3 * mat.m00 - v1 * mat.m01 + v0 * mat.m02) * inverse_determinant;

    v0 = mat.m10 * mat.m31 - mat.m11 * mat.m30;
    v1 = mat.m10 * mat.m32 - mat.m12 * mat.m30;
    v2 = mat.m10 * mat.m33 - mat.m13 * mat.m30;
    v3 = mat.m11 * mat.m32 - mat.m12 * mat.m31;
    v4 = mat.m11 * mat.m33 - mat.m13 * mat.m31;
    v5 = mat.m12 * mat.m33 - mat.m13 * mat.m32;

    const auto d02 = +(v5 * mat.m01 - v4 * mat.m02 + v3 * mat.m03) * inverse_determinant;
    const auto d12 = -(v5 * mat.m00 - v2 * mat.m02 + v1 * mat.m03) * inverse_determinant;
    const auto d22 = +(v4 * mat.m00 - v2 * mat.m01 + v0 * mat.m03) * inverse_determinant;
    const auto d32 = -(v3 * mat.m00 - v1 * mat.m01 + v0 * mat.m02) * inverse_determinant;

    v0 = mat.m21 * mat.m10 - mat.m20 * mat.m11;
    v1 = mat.m22 * mat.m10 - mat.m20 * mat.m12;
    v2 = mat.m23 * mat.m10 - mat.m20 * mat.m13;
    v3 = mat.m22 * mat.m11 - mat.m21 * mat.m12;
    v4 = mat.m23 * mat.m11 - mat.m21 * mat.m13;
    v5 = mat.m23 * mat.m12 - mat.m22 * mat.m13;

    const auto d03 = -(v5 * mat.m01 - v4 * mat.m02 + v3 * mat.m03) * inverse_determinant;
    const auto d13 = +(v5 * mat.m00 - v2 * mat.m02 + v1 * mat.m03) * inverse_determinant;
    const auto d23 = -(v4 * mat.m00 - v2 * mat.m01 + v0 * mat.m03) * inverse_determinant;
    const auto d33 = +(v3 * mat.m00 - v1 * mat.m01 + v0 * mat.m02) * inverse_determinant;

    // clang-format off
    return {
        d00, d01, d02, d03,
        d10, d11, d12, d13,
        d20, d21, d22, d23,
        d30, d31, d32, d33
    };
    // clang-format on
}

inline auto is_affine(const mat4 &mat) noexcept -> bool
{
    return (mat.m30 == 0.0f) && (mat.m31 == 0.0f) && (mat.m32 == 0.0f) && (mat.m33 == 1.0f);
}

inline void decompose(const mat4 &mat, vector3<float> &translation, vector3<float> &scale,
                      quaternion &orientation) noexcept
{
    const auto m3 = mat3{mat};

    vector3<float> shear;
    const auto q = qr_decompose(m3, scale, shear);

    orientation = quaternion{q};
    translation.set(mat.m03, mat.m13, mat.m23);
}

inline auto ptr(mat4 &mat) noexcept -> float *
{
    return &mat.m00;
}

inline auto ptr(const mat4 &mat) noexcept -> const float *
{
    return &mat.m00;
}

} // namespace aeon::math
