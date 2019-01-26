// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline auto operator+(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

template <typename T>
inline auto operator+(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

template <typename T>
inline auto operator+(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs + rhs.x, lhs + rhs.y, lhs + rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x - rhs, lhs.y - rhs, lhs.z - rhs};
}

template <typename T>
inline auto operator-(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs - rhs.x, lhs - rhs.y, lhs - rhs.z};
}

template <typename T>
inline auto operator-(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {-vec.x, -vec.y, -vec.z};
}

template <typename T>
inline auto operator*(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

template <typename T>
inline auto operator*(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

template <typename T>
inline auto operator*(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}

template <typename T>
inline auto operator/(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

template <typename T>
inline auto operator/(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>
{
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

template <typename T, typename U>
inline auto operator*(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) * rhs.z)};
}

template <typename T, typename U>
inline auto operator*(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs),
            static_cast<T>(static_cast<U>(lhs.z) * rhs)};
}

template <typename T, typename U>
inline auto operator/(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs.x), static_cast<T>(static_cast<U>(lhs.y) / rhs.y),
            static_cast<T>(static_cast<U>(lhs.z) / rhs.z)};
}

template <typename T, typename U>
inline auto operator/(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs),
            static_cast<T>(static_cast<U>(lhs.z) / rhs)};
}

template <typename T>
inline auto operator+=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator/=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline auto operator/=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator/=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator/=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline auto operator==(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T>
inline auto operator!=(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);
}

template <typename T>
inline auto operator>(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z);
}

} // namespace aeon::math
