// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator+(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

template <typename T>
inline constexpr auto operator+(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs};
}

template <typename T>
inline constexpr auto operator+(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w};
}

template <typename T>
inline constexpr auto operator-(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z, rhs.z, lhs.w - rhs.w};
}

template <typename T>
inline constexpr auto operator-(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs};
}

template <typename T>
inline constexpr auto operator-(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w};
}

template <typename T>
inline constexpr auto operator-(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {-vec.x, -vec.y, -vec.z, -vec.w};
}

template <typename T>
inline constexpr auto operator*(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w};
}

template <typename T>
inline constexpr auto operator*(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
}

template <typename T>
inline constexpr auto operator*(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w};
}

template <typename T>
inline constexpr auto operator/(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>
{
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
}

template <typename T, typename U>
inline constexpr auto operator*(const vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) * rhs.z), static_cast<T>(static_cast<U>(lhs.w) * rhs.w)};
}

template <typename T, typename U>
inline constexpr auto operator*(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs),
            static_cast<T>(static_cast<U>(lhs.z) * rhs), static_cast<T>(static_cast<U>(lhs.w) * rhs)};
}

template <typename T, typename U>
inline constexpr auto operator/(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs),
            static_cast<T>(static_cast<U>(lhs.z) / rhs), static_cast<T>(static_cast<U>(lhs.w) / rhs)};
}

template <typename T>
inline constexpr auto operator+=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator+=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator-=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator-=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator*=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator*=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator/=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline constexpr auto operator*=(vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline constexpr auto operator*=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline constexpr auto operator/=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline constexpr auto operator==(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

template <typename T>
inline constexpr auto operator!=(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w);
}

template <typename T>
inline constexpr auto operator>(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w);
}

} // namespace aeon::math
