// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/math.h>
#include <aeon/math/vector2.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr circle<T>::circle(const T radius) noexcept
    : position{}
    , radius{radius}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr circle<T>::circle(const T x, const T y, const T radius) noexcept
    : circle{vector2<T>{x, y}, radius}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr circle<T>::circle(const vector2<T> position, const T radius) noexcept
    : position{position}
    , radius{radius}
{
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto position(const circle<T> &c) noexcept -> vector2<T>
{
    return c.position;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto center(const circle<T> &c) noexcept -> vector2<T>
{
    return position(c);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto empty(const circle<T> &c) noexcept -> bool
{
    return radius(c) == T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto null(const circle<T> &c) noexcept -> bool
{
    return empty(c);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto valid(const circle<T> &c) noexcept -> bool
{
    return radius(c) >= T(0);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto size(const circle<T> &c) noexcept -> size2d<T>
{
    const auto d = diameter(c);
    return {d, d};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto radius(const circle<T> &c) noexcept -> T
{
    return c.radius;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto radius_squared(const circle<T> &c) noexcept -> T
{
    return radius(c) * radius(c);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto diameter(const circle<T> &c) noexcept -> T
{
    return radius(c) * T(2);
}

template <common::concepts::arithmetic_convertible T, std::enable_if_t<!std::is_floating_point_v<T>> *>
[[nodiscard]] inline constexpr auto circumference(const circle<T> &c) noexcept -> float
{
    return static_cast<float>(diameter(c)) * constants<float>::pi;
}

template <common::concepts::arithmetic_convertible T, std::enable_if_t<std::is_floating_point_v<T>> *>
[[nodiscard]] inline constexpr auto circumference(const circle<T> &c) noexcept -> T
{
    return diameter(c) * constants<T>::pi;
}

template <common::concepts::arithmetic_convertible T, std::enable_if_t<!std::is_floating_point_v<T>> *>
[[nodiscard]] inline constexpr auto area(const circle<T> &c) noexcept -> float
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return constants<float>::pi * static_cast<float>(r2);
}

template <common::concepts::arithmetic_convertible T, std::enable_if_t<std::is_floating_point_v<T>> *>
[[nodiscard]] inline constexpr auto area(const circle<T> &c) noexcept -> T
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return constants<T>::pi * r2;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(circle<T> &c, const T x, const T y) noexcept
{
    c = positioned(c, x, y);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(circle<T> &c, const vector2<T> &vec) noexcept
{
    c = positioned(c, vec);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto positioned(const circle<T> &c, const T x, const T y) noexcept -> circle<T>
{
    return positioned(c, vector2{x, y});
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto positioned(const circle<T> &c, const vector2<T> &vec) noexcept -> circle<T>
{
    return {vec, radius(c)};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(circle<T> &c, const T val) noexcept
{
    c = inflated(c, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto inflated(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) + val};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(circle<T> &c, const T val) noexcept
{
    c = scaled(c, val);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) * val};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rect(const circle<T> &c) noexcept -> rectangle<T>
{
    // Specific code for a circle, this is faster than generating a
    // rectangle with set_position and anchor_point::center.
    const auto r = radius(c);
    const auto d = diameter(c);
    const auto pos = position(c);
    const auto left = pos.x - r;
    const auto top = pos.y - r;
    return {left, top, left + d, top + d};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const circle<T> &lhs, const circle<T> &rhs) noexcept -> T
{
    return distance(position(lhs), position(rhs));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const circle<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return distance(position(lhs), rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto contains(const circle<T> &c, const vector2<T> &vec) noexcept -> bool
{
    return distance(position(c), vec) <= radius(c);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto overlaps(const circle<T> &c, const rectangle<T> &rect) noexcept -> bool
{
    const auto closest = closest_point(rect, position(c));
    const auto distance = position(c) - closest;
    const auto distance_squared = squared_length(distance);
    return distance_squared < radius_squared(c);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return position(lhs) == position(rhs) && radius(lhs) == radius(rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
