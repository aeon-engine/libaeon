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

inline auto mat4::scale(const vector3<float> &vec) noexcept -> mat4
{
    // clang-format off
    return {vec.x, 0.0f,  0.0f,  0.0f,
            0.0f,  vec.y, 0.0f,  0.0f,
            0.0f,  0.0f,  vec.z, 0.0f,
            0.0f,  0.0f,  0.0f,  1.0f};
    // clang-format on
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

inline auto mat4::projection_fov(float fov, float width, float height, float near, float far) noexcept -> mat4
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

inline auto ptr(mat4 &mat) noexcept -> float *
{
    return &mat.m00;
}

inline auto ptr(const mat4 &mat) noexcept -> const float *
{
    return &mat.m00;
}

} // namespace aeon::math
