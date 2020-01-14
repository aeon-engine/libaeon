// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/mat3.h>
#include <aeon/math/vector3.h>
#include <cmath>
#include <algorithm>
#include <array>

namespace aeon::math
{

inline constexpr quaternion::quaternion() noexcept
    : w{}
    , x{}
    , y{}
    , z{}
{
}

inline constexpr quaternion::quaternion(const float w, const float x, const float y, const float z) noexcept
    : w{w}
    , x{x}
    , y{y}
    , z{z}
{
}

template <typename T>
inline constexpr quaternion::quaternion(const T w, const T x, const T y, const T z) noexcept
    : w{static_cast<float>(w)}
    , x{static_cast<float>(x)}
    , y{static_cast<float>(y)}
    , z{static_cast<float>(z)}
{
}

inline quaternion::quaternion(const vector3<float> &euler) noexcept
{
    const auto c = cos(euler * 0.5f);
    const auto s = sin(euler * 0.5f);

    w = c.x * c.y * c.z + s.x * s.y * s.z;
    x = s.x * c.y * c.z - c.x * s.y * s.z;
    y = c.x * s.y * c.z + s.x * c.y * s.z;
    z = c.x * c.y * s.z - s.x * s.y * c.z;
}

inline quaternion::quaternion(const mat3 &mat) noexcept
{
    const auto trace = mat[0][0] + mat[1][1] + mat[2][2];

    if (trace > 0.0)
    {
        auto root = std::sqrt(trace + 1.0f);
        w = 0.5f * root;
        root = 0.5f / root;
        x = (mat[1][2] - mat[2][1]) * root;
        y = (mat[2][0] - mat[0][2]) * root;
        z = (mat[0][1] - mat[1][0]) * root;
    }
    else
    {
        constexpr std::array<int, 3> next_index{1, 2, 0};

        auto i = 0;
        if (mat[1][1] > mat[0][0])
            i = 1;

        if (mat[2][2] > mat.at(i, i))
            i = 2;

        const auto j = next_index[i];
        const auto k = next_index[j];

        auto root = std::sqrt(mat.at(i, i) - mat.at(j, j) - mat.at(k, k) + 1.0f);
        std::array<float *, 3> apk_quat{&x, &y, &z};
        *apk_quat[i] = 0.5f * root;
        root = 0.5f / root;
        w = (mat.at(j, k) - mat.at(k, j)) * root;
        *apk_quat[j] = (mat.at(i, j) + mat.at(j, i)) * root;
        *apk_quat[k] = (mat.at(i, k) + mat.at(k, i)) * root;
    }
}

[[nodiscard]] inline constexpr auto quaternion::indentity() noexcept -> quaternion
{
    return {1.0f, 0.0f, 0.0f, 0.0f};
}

inline constexpr void quaternion::set(const float new_w, const float new_x, const float new_y,
                                      const float new_z) noexcept
{
    w = new_w;
    x = new_x;
    y = new_y;
    z = new_z;
}

[[nodiscard]] inline auto pitch(const quaternion &quat) noexcept -> float
{
    return std::atan2(2.0f * (quat.y * quat.z + quat.w * quat.x),
                      quat.w * quat.w - quat.x * quat.x - quat.y * quat.y + quat.z * quat.z);
}

[[nodiscard]] inline auto yaw(const quaternion &quat) noexcept -> float
{
    return std::asin(std::clamp(-2.0f * (quat.x * quat.z - quat.w * quat.y), -1.0f, 1.0f));
}

[[nodiscard]] inline auto roll(const quaternion &quat) noexcept -> float
{
    return std::atan2(2.0f * (quat.x * quat.y + quat.w * quat.z),
                      quat.w * quat.w + quat.x * quat.x - quat.y * quat.y - quat.z * quat.z);
}

[[nodiscard]] inline auto euler(const quaternion &quat) noexcept -> vector3<float>
{
    return {pitch(quat), yaw(quat), roll(quat)};
}

[[nodiscard]] inline constexpr auto dot(const quaternion &a, const quaternion &b) noexcept -> float
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

[[nodiscard]] inline constexpr auto ptr(quaternion &quat) noexcept -> float *
{
    return &quat.w;
}

[[nodiscard]] inline constexpr auto ptr(const quaternion &quat) noexcept -> const float *
{
    return &quat.w;
}

} // namespace aeon::math
