// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x + rhs, lhs.y + rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs + rhs.x, lhs + rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x - rhs, lhs.y - rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs - rhs.x, lhs - rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {-vec.x, -vec.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x * rhs, lhs.y * rhs};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs * rhs.x, lhs * rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs.x, lhs.y / rhs.y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>
{
    return {lhs.x / rhs, lhs.y / rhs};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs.x), static_cast<T>(static_cast<U>(lhs.y) * rhs.y)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) * rhs), static_cast<T>(static_cast<U>(lhs.y) * rhs)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs.x), static_cast<T>(static_cast<U>(lhs.y) / rhs.y)};
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>
{
    return {static_cast<T>(static_cast<U>(lhs.x) / rhs), static_cast<T>(static_cast<U>(lhs.y) / rhs)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs * rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &
{
    lhs = lhs / rhs;
    return lhs;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator<(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return (lhs.x < rhs.x && lhs.y < rhs.y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool
{
    return (lhs.x > rhs.x && lhs.y > rhs.y);
}

} // namespace aeon::math
