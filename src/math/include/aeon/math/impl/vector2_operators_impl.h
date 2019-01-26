// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T>
inline auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs, lhs.y + rhs};
}

template <typename T>
inline auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs + rhs.x, lhs + rhs.y};
}

template <typename T>
inline auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T>
inline auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs, lhs.y - rhs};
}

template <typename T>
inline auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs - rhs.x, lhs - rhs.y};
}

template <typename T>
inline auto operator-(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {-vec.x, -vec.y};
}

template <typename T>
inline auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

template <typename T>
inline auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs, lhs.y * rhs};
}

template <typename T>
inline auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs * rhs.x, lhs * rhs.y};
}

template <typename T>
inline auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}

template <typename T>
inline auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs, lhs.y / rhs};
}

template <typename T, typename U>
inline auto operator*(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y)};
}

template <typename T, typename U>
inline auto operator*(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs)};
}

template <typename T, typename U>
inline auto operator/(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs.x), static_cast<T>(static_cast<U>(lhs.y) / rhs.y)};
}

template <typename T, typename U>
inline auto operator/(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs)};
}

template <typename T>
inline auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator/=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator/=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <typename T>
inline auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename T>
inline auto operator!=(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y);
}

template <typename T>
inline auto operator>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y);
}

} // namespace aeon::math
