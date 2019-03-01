// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/math.h>
#include <aeon/math/vector2.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>

namespace aeon::math
{

template <typename T>
circle<T>::circle(const T radius) noexcept
    : position{}
    , radius{radius}
{
}

template <typename T>
circle<T>::circle(const T x, const T y, const T radius) noexcept
    : circle{vector2<T>{x, y}, radius}
{
}

template <typename T>
circle<T>::circle(const vector2<T> position, const T radius) noexcept
    : position{position}
    , radius{radius}
{
}

template <typename T>
[[nodiscard]] inline auto position(const circle<T> &c) noexcept -> vector2<T>
{
    return c.position;
}

template <typename T>
[[nodiscard]] inline auto center(const circle<T> &c) noexcept -> vector2<T>
{
    return position(c);
}

template <typename T>
[[nodiscard]] inline auto empty(const circle<T> &c) noexcept -> bool
{
    return radius(c) == T(0);
}

template <typename T>
[[nodiscard]] inline auto null(const circle<T> &c) noexcept -> bool
{
    return empty(c);
}

template <typename T>
[[nodiscard]] inline auto valid(const circle<T> &c) noexcept -> bool
{
    return radius(c) >= T(0);
}

template <typename T>
[[nodiscard]] inline auto size(const circle<T> &c) noexcept -> size2d<T>
{
    const auto d = diameter(c);
    return {d, d};
}

template <typename T>
[[nodiscard]] inline auto radius(const circle<T> &c) noexcept -> T
{
    return c.radius;
}

template <typename T>
[[nodiscard]] inline auto radius_squared(const circle<T> &c) noexcept -> T
{
    return radius(c) * radius(c);
}

template <typename T>
[[nodiscard]] inline auto diameter(const circle<T> &c) noexcept -> T
{
    return radius(c) * T(2);
}

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type *>
[[nodiscard]] inline auto circumference(const circle<T> &c) noexcept -> float
{
    return static_cast<float>(diameter(c)) * constants<float>::pi;
}

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type *>
[[nodiscard]] inline auto circumference(const circle<T> &c) noexcept -> T
{
    return diameter(c) * constants<T>::pi;
}

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type *>
[[nodiscard]] inline auto area(const circle<T> &c) noexcept -> float
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return constants<float>::pi * static_cast<float>(r2);
}

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type *>
[[nodiscard]] inline auto area(const circle<T> &c) noexcept -> T
{
    const auto r = radius(c);
    const auto r2 = r * r;
    return constants<T>::pi * r2;
}

template <typename T>
inline void set_position(circle<T> &c, const T x, const T y) noexcept
{
    c = positioned(c, x, y);
}

template <typename T>
inline void set_position(circle<T> &c, const vector2<T> &vec) noexcept
{
    c = positioned(c, vec);
}

template <typename T>
[[nodiscard]] inline auto positioned(const circle<T> &c, const T x, const T y) noexcept -> circle<T>
{
    return positioned(c, vector2{x, y});
}

template <typename T>
[[nodiscard]] inline auto positioned(const circle<T> &c, const vector2<T> &vec) noexcept -> circle<T>
{
    return {vec, radius(c)};
}

template <typename T>
inline void inflate(circle<T> &c, const T val) noexcept
{
    c = inflated(c, val);
}

template <typename T>
[[nodiscard]] inline auto inflated(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) + val};
}

template <typename T>
inline void scale(circle<T> &c, const T val) noexcept
{
    c = scaled(c);
}

template <typename T>
[[nodiscard]] inline auto scaled(const circle<T> &c, const T val) noexcept -> circle<T>
{
    return {position(c), radius(c) * val};
}

template <typename T>
[[nodiscard]] inline auto rect(const circle<T> &c) noexcept -> rectangle<T>
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

template <typename T>
[[nodiscard]] inline auto distance(const circle<T> &lhs, const circle<T> &rhs) noexcept -> T
{
    return distance(position(lhs), position(rhs));
}

template <typename T>
[[nodiscard]] inline auto distance(const circle<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return distance(position(lhs), rhs);
}

template <typename T>
[[nodiscard]] inline auto contains(const circle<T> &c, const vector2<T> &vec) noexcept -> bool
{
    return distance(position(c), vec) <= radius(c);
}

template <typename T>
[[nodiscard]] inline auto overlaps(const circle<T> &c, const rectangle<T> &rect) noexcept -> bool
{
    const auto closest = closest_point(rect, position(c));
    const auto distance = position(c) - closest;
    const auto distance_squared = squared_length(distance);
    return distance_squared < radius_squared(c);
}

template <typename T>
inline auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return position(lhs) == position(rhs) && radius(lhs) == radius(rhs);
}

template <typename T>
inline auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math
