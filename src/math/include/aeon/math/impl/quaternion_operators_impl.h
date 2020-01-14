// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::math
{

inline constexpr auto operator+(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline constexpr auto operator-(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w - rhs.w, lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

inline constexpr auto operator*(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
            lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x};
}

inline constexpr auto operator*(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return {lhs.w * rhs, lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

inline constexpr auto operator/(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion
{
    return {lhs.w / rhs.w, lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

inline constexpr auto operator/(const quaternion &lhs, const float rhs) noexcept -> quaternion
{
    return {lhs.w / rhs, lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

inline constexpr auto operator+=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &
{
    lhs = lhs + rhs;
    return lhs;
}

inline constexpr auto operator-=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &
{
    lhs = lhs - rhs;
    return lhs;
}

inline constexpr auto operator*=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &
{
    lhs = lhs * rhs;
    return lhs;
}

inline constexpr auto operator*=(quaternion &lhs, const float rhs) noexcept -> quaternion &
{
    lhs = lhs * rhs;
    return lhs;
}

inline constexpr auto operator/=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &
{
    lhs = lhs / rhs;
    return lhs;
}

inline constexpr auto operator/=(quaternion &lhs, const float rhs) noexcept -> quaternion &
{
    lhs = lhs / rhs;
    return lhs;
}

inline constexpr auto operator==(const quaternion &lhs, const quaternion &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

inline constexpr auto operator!=(const quaternion &lhs, const quaternion &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
