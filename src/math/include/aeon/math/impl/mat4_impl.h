// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <aeon/math/mat3.h>
#include <aeon/math/quaternion.h>
#include <aeon/math/rectangle.h>
#include <aeon/common/assert.h>
#include <cmath>

namespace aeon::math
{

inline mat4::mat4() noexcept = default;

inline mat4::mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
                  const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
                  const float m30, const float m31, const float m32, const float m33) noexcept
{
    column[0] = vector4{m00, m10, m20, m30};
    column[1] = vector4{m01, m11, m21, m31};
    column[2] = vector4{m02, m12, m22, m32};
    column[3] = vector4{m03, m13, m23, m33};
}

inline mat4::mat4(const mat3 &m) noexcept
{
    column[0] = vector4{m[0]};
    column[1] = vector4{m[1]};
    column[2] = vector4{m[2]};
    column[3] = vector4{0.0f, 0.0f, 0.0f, 1.0f};
}

inline mat4::mat4(const quaternion &q) noexcept
    : mat4{mat3{q}}
{
}

[[nodiscard]] inline auto mat4::operator[](const std::size_t i) noexcept -> vector4<float> &
{
    aeon_assert_array_bounds(column, i);
    return column[i];
}

[[nodiscard]] inline auto mat4::operator[](const std::size_t i) const noexcept -> const vector4<float> &
{
    aeon_assert_array_bounds(column, i);
    return column[i];
}

[[nodiscard]] inline auto mat4::at(const int column_index, const int row_index) const noexcept -> float
{
    return operator[](column_index)[row_index];
}

[[nodiscard]] inline auto mat4::zero() noexcept -> mat4
{
    return {};
}

[[nodiscard]] inline auto mat4::indentity() noexcept -> mat4
{
    // clang-format off
    return {1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};
    // clang-format on
}

[[nodiscard]] inline auto mat4::scale(const float xyz) noexcept -> mat4
{
    return scale(vector3<float>{xyz});
}

[[nodiscard]] inline auto mat4::scale(const float x, const float y, const float z) noexcept -> mat4
{
    return scale({x, y, z});
}

[[nodiscard]] inline auto mat4::scale(const vector3<float> &vec) noexcept -> mat4
{
    // clang-format off
    return {vec.x, 0.0f,  0.0f,  0.0f,
            0.0f,  vec.y, 0.0f,  0.0f,
            0.0f,  0.0f,  vec.z, 0.0f,
            0.0f,  0.0f,  0.0f,  1.0f};
    // clang-format on
}

template <typename T>
[[nodiscard]] inline auto mat4::scale(const T xyz) noexcept -> mat4
{
    return scale(static_cast<float>(xyz));
}

template <typename T>
[[nodiscard]] inline auto mat4::scale(const T x, const T y, const T z) noexcept -> mat4
{
    return scale(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

template <typename T>
[[nodiscard]] inline auto mat4::scale(const vector3<T> &vec) noexcept -> mat4
{
    return scale(vector3<float>{vec});
}

[[nodiscard]] inline auto mat4::translate(const float x, const float y) noexcept -> mat4
{
    return translate({x, y, 0.0f});
}

[[nodiscard]] inline auto mat4::translate(const float x, const float y, const float z) noexcept -> mat4
{
    return translate({x, y, z});
}

[[nodiscard]] inline auto mat4::translate(const vector3<float> &vec) noexcept -> mat4
{
    // clang-format off
    return {1.0f, 0.0f, 0.0f, vec.x,
            0.0f, 1.0f, 0.0f, vec.y,
            0.0f, 0.0f, 1.0f, vec.z,
            0.0f, 0.0f, 0.0f, 1.0f};
    // clang-format on
}

template <typename T>
[[nodiscard]] inline auto mat4::translate(const T x, const T y) noexcept -> mat4
{
    return translate(static_cast<float>(x), static_cast<float>(y));
}

template <typename T>
[[nodiscard]] inline auto mat4::translate(const T x, const T y, const T z) noexcept -> mat4
{
    return translate(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

template <typename T>
[[nodiscard]] inline auto mat4::translate(const vector3<T> &vec) noexcept -> mat4
{
    return translate(vector3<float>{vec});
}

[[nodiscard]] inline auto mat4::rotate(const unitf<radian> angle, const vector3<float> &vec) noexcept -> mat4
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

template <typename T>
[[nodiscard]] inline auto mat4::rotate(const unitf<radian> angle, const vector3<T> &vec) noexcept -> mat4
{
    return rotate(angle, vector3<float>{vec});
}

[[nodiscard]] inline auto mat4::ortho(const float left, const float right, const float bottom, const float top) noexcept
    -> mat4
{
    // clang-format off
    return {
        2.0f / (right - left),
        0.0f,
        0.0f,
        -(right + left) / (right - left),

        0.0f,
        2.0f / (top - bottom),
        0.0f,
        -(top + bottom) / (top - bottom),

        0.0f,
        0.0f,
        -1.0f,
        0.0f,

        0.0f,
        0.0f,
        0.0f,
        1.0f
    };
    // clang-format on
}

[[nodiscard]] inline auto mat4::ortho(const float left, const float right, const float bottom, const float top,
                                      const float near, const float far) noexcept -> mat4
{
    // clang-format off
    return {
        2.0f / (right - left),
        0.0f,
        0.0f,
        -(right + left) / (right - left),

        0.0f,
        2.0f / (top - bottom),
        0.0f,
        -(top + bottom) / (top - bottom),

        0.0f,
        0.0f,
        -2.0f / (far - near),
        -(far + near) / (far - near),

        0.0f,
        0.0f,
        0.0f,
        1.0f
    };
    // clang-format on
}

template <typename T>
[[nodiscard]] inline auto mat4::ortho(const T left, const T right, const T bottom, const T top) noexcept -> mat4
{
    return mat4::ortho(static_cast<float>(left), static_cast<float>(right), static_cast<float>(bottom),
                       static_cast<float>(top));
}

template <typename T, typename U>
[[nodiscard]] inline auto mat4::ortho(const T left, const T right, const T bottom, const T top, const U near,
                                      const U far) noexcept -> mat4
{
    return mat4::ortho(static_cast<float>(left), static_cast<float>(right), static_cast<float>(bottom),
                       static_cast<float>(top), static_cast<float>(near), static_cast<float>(far));
}

template <typename T>
[[nodiscard]] inline auto mat4::ortho(const rectangle<T> &rect) noexcept -> mat4
{
    return mat4::ortho(left(rect), right(rect), bottom(rect), top(rect));
}

template <typename T, typename U>
[[nodiscard]] inline auto mat4::ortho(const rectangle<T> &rect, const U near, const U far) noexcept -> mat4
{
    return mat4::ortho(left(rect), right(rect), bottom(rect), top(rect), near, far);
}

[[nodiscard]] inline auto mat4::projection(const unitf<radian> fov_y, const float aspect_ratio, const float near,
                                           const float far) noexcept -> mat4
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
        -(2.0f * far * near) / (far - near),

        0.0f,
        0.0f,
        -1.0f,
        0.0f
    };
    // clang-format on
}

template <typename T, typename U>
[[nodiscard]] inline auto mat4::projection(const unit_base<radian, void, U> fov_y, const T aspect_ratio, const U near,
                                           const U far) noexcept -> mat4
{
    return projection(static_cast<float>(fov_y), static_cast<float>(aspect_ratio), static_cast<float>(near),
                      static_cast<float>(far));
}

[[nodiscard]] inline auto mat4::projection_fov(const unitf<radian> fov, const float width, const float height,
                                               const float near, const float far) noexcept -> mat4
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
        0.0f
    };
    // clang-format on
}

template <typename T, typename U>
[[nodiscard]] inline auto mat4::projection_fov(const unit_base<radian, void, U> fov, const T width, const T height,
                                               const U near, const U far) noexcept -> mat4
{
    return projection_fov(static_cast<float>(fov), static_cast<float>(width), static_cast<float>(height),
                          static_cast<float>(near), static_cast<float>(far));
}

[[nodiscard]] inline auto determinant(const mat4 &mat) noexcept -> float
{
    // clang-format off
    const auto a = mat3{
        mat[1][1], mat[2][1], mat[3][1],
        mat[1][2], mat[2][2], mat[3][2],
        mat[1][3], mat[2][3], mat[3][3],
    };

    const auto b = mat3{
        mat[0][1], mat[2][1], mat[3][1],
        mat[0][2], mat[2][2], mat[3][2],
        mat[0][3], mat[2][3], mat[3][3],
    };

    const auto c = mat3{
        mat[0][1], mat[1][1], mat[3][1],
        mat[0][2], mat[1][2], mat[3][2],
        mat[0][3], mat[1][3], mat[3][3],
    };

    const auto d = mat3{
        mat[0][1], mat[1][1], mat[2][1],
        mat[0][2], mat[1][2], mat[2][2],
        mat[0][3], mat[1][3], mat[2][3],
    };
    // clang-format on

    return mat[0][0] * determinant(a) - mat[1][0] * determinant(b) + mat[2][0] * determinant(c) -
           mat[3][0] * determinant(d);
}

[[nodiscard]] inline auto inverse(const mat4 &mat) noexcept -> mat4
{
    auto v0 = mat[0][2] * mat[1][3] - mat[1][2] * mat[0][3];
    auto v1 = mat[0][2] * mat[2][3] - mat[2][2] * mat[0][3];
    auto v2 = mat[0][2] * mat[3][3] - mat[3][2] * mat[0][3];
    auto v3 = mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3];
    auto v4 = mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3];
    auto v5 = mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3];

    const auto t00 = +(v5 * mat[1][1] - v4 * mat[2][1] + v3 * mat[3][1]);
    const auto t10 = -(v5 * mat[0][1] - v2 * mat[2][1] + v1 * mat[3][1]);
    const auto t20 = +(v4 * mat[0][1] - v2 * mat[1][1] + v0 * mat[3][1]);
    const auto t30 = -(v3 * mat[0][1] - v1 * mat[1][1] + v0 * mat[2][1]);

    const auto inverse_determinant = 1 / (t00 * mat[0][0] + t10 * mat[1][0] + t20 * mat[2][0] + t30 * mat[3][0]);

    const auto d00 = t00 * inverse_determinant;
    const auto d10 = t10 * inverse_determinant;
    const auto d20 = t20 * inverse_determinant;
    const auto d30 = t30 * inverse_determinant;

    const auto d01 = -(v5 * mat[1][0] - v4 * mat[2][0] + v3 * mat[3][0]) * inverse_determinant;
    const auto d11 = +(v5 * mat[0][0] - v2 * mat[2][0] + v1 * mat[3][0]) * inverse_determinant;
    const auto d21 = -(v4 * mat[0][0] - v2 * mat[1][0] + v0 * mat[3][0]) * inverse_determinant;
    const auto d31 = +(v3 * mat[0][0] - v1 * mat[1][0] + v0 * mat[2][0]) * inverse_determinant;

    v0 = mat[0][1] * mat[1][3] - mat[1][1] * mat[0][3];
    v1 = mat[0][1] * mat[2][3] - mat[2][1] * mat[0][3];
    v2 = mat[0][1] * mat[3][3] - mat[3][1] * mat[0][3];
    v3 = mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3];
    v4 = mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3];
    v5 = mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3];

    const auto d02 = +(v5 * mat[1][0] - v4 * mat[2][0] + v3 * mat[3][0]) * inverse_determinant;
    const auto d12 = -(v5 * mat[0][0] - v2 * mat[2][0] + v1 * mat[3][0]) * inverse_determinant;
    const auto d22 = +(v4 * mat[0][0] - v2 * mat[1][0] + v0 * mat[3][0]) * inverse_determinant;
    const auto d32 = -(v3 * mat[0][0] - v1 * mat[1][0] + v0 * mat[2][0]) * inverse_determinant;

    v0 = mat[1][2] * mat[0][1] - mat[0][2] * mat[1][1];
    v1 = mat[2][2] * mat[0][1] - mat[0][2] * mat[2][1];
    v2 = mat[3][2] * mat[0][1] - mat[0][2] * mat[3][1];
    v3 = mat[2][2] * mat[1][1] - mat[1][2] * mat[2][1];
    v4 = mat[3][2] * mat[1][1] - mat[1][2] * mat[3][1];
    v5 = mat[3][2] * mat[2][1] - mat[2][2] * mat[3][1];

    const auto d03 = -(v5 * mat[1][0] - v4 * mat[2][0] + v3 * mat[3][0]) * inverse_determinant;
    const auto d13 = +(v5 * mat[0][0] - v2 * mat[2][0] + v1 * mat[3][0]) * inverse_determinant;
    const auto d23 = -(v4 * mat[0][0] - v2 * mat[1][0] + v0 * mat[3][0]) * inverse_determinant;
    const auto d33 = +(v3 * mat[0][0] - v1 * mat[1][0] + v0 * mat[2][0]) * inverse_determinant;

    // clang-format off
    return {
        d00, d01, d02, d03,
        d10, d11, d12, d13,
        d20, d21, d22, d23,
        d30, d31, d32, d33
    };
    // clang-format on
}

[[nodiscard]] inline auto is_affine(const mat4 &mat) noexcept -> bool
{
    return (mat[0][3] == 0.0f) && (mat[1][3] == 0.0f) && (mat[2][3] == 0.0f) && (mat[3][3] == 1.0f);
}

inline void decompose(const mat4 &mat, vector3<float> &translation, vector3<float> &scale,
                      quaternion &orientation) noexcept
{
    const auto m3 = mat3{mat};

    vector3<float> shear;
    const auto q = qr_decompose(m3, scale, shear);

    orientation = quaternion{q};
    translation.set(mat[3][0], mat[3][1], mat[3][2]);
}

[[nodiscard]] inline auto ptr(mat4 &mat) noexcept -> float *
{
    return &mat[0][0];
}

[[nodiscard]] inline auto ptr(const mat4 &mat) noexcept -> const float *
{
    return &mat[0][0];
}

} // namespace aeon::math
