// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <cmath>
#include <limits>

namespace aeon::math
{

template <typename T>
inline vector2<T>::vector2() noexcept
    : x{}
    , y{}
{
}

template <typename T>
inline vector2<T>::vector2(const T xy) noexcept
    : x{xy}
    , y{xy}
{
}

template <typename T>
inline vector2<T>::vector2(const T x, const T y) noexcept
    : x{x}
    , y{y}
{
}

template <typename T>
template <typename U>
inline vector2<T>::vector2(const U x, const U y) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
{
}

template <typename T>
template <typename U>
inline vector2<T>::vector2(const vector2<U> &vec) noexcept
    : x{static_cast<T>(vec.x)}
    , y{static_cast<T>(vec.y)}
{
}

template <typename T>
inline vector2<T>::vector2(const T xy[2]) noexcept
    : x{xy[0]}
    , y{xy[1]}
{
}

template <typename T>
[[nodiscard]] inline auto vector2<T>::operator[](const std::size_t i) noexcept -> T &
{
    aeon_assert_array_bounds(value, i);
    return value[i];
}

template <typename T>
[[nodiscard]] inline auto vector2<T>::operator[](const std::size_t i) const noexcept -> const T &
{
    aeon_assert_array_bounds(value, i);
    return value[i];
}

template <typename T>
[[nodiscard]] inline auto vector2<T>::zero() noexcept -> vector2<T>
{
    return vector2<T>{};
}

template <typename T>
inline void vector2<T>::set(const T new_x, const T new_y) noexcept
{
    x = new_x;
    y = new_y;
}

template <typename T>
inline void translate(vector2<T> &lhs, const T x, const T y) noexcept
{
    lhs += vector2{x, y};
}

template <typename T>
inline void translate(vector2<T> &lhs, const vector2<T> &rhs) noexcept
{
    lhs += rhs;
}

template <typename T>
[[nodiscard]] inline auto translated(const vector2<T> &lhs, const T x, const T y) noexcept -> vector2<T>
{
    return lhs + vector2{x, y};
}

template <typename T>
[[nodiscard]] inline auto translated(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return lhs + rhs;
}

template <typename T>
[[nodiscard]] inline auto dot(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template <typename T>
[[nodiscard]] inline auto cross(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
}

template <typename T>
[[nodiscard]] inline auto length(const vector2<T> &vec) noexcept -> T
{
    return std::sqrt(dot(vec, vec));
}

template <typename T>
[[nodiscard]] inline auto squared_length(const vector2<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <typename T>
inline void normalize(vector2<T> &vec) noexcept
{
    vec = normalized(vec);
}

template <typename T>
[[nodiscard]] inline auto normalized(const vector2<T> &vec) noexcept -> vector2<T>
{
    auto l = length(vec);

    if (l > std::numeric_limits<T>::epsilon())
        return vec / l;

    return vector2<T>::zero();
}

template <typename T>
[[nodiscard]] inline auto sin(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::sin(vec.x), std::sin(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto cos(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::cos(vec.x), std::cos(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto tan(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::tan(vec.x), std::tan(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto asin(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::asin(vec.x), std::asin(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto acos(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::acos(vec.x), std::acos(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto atan(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::atan(vec.x), std::atan(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto atan2(const vector2<T> &vec) noexcept -> T
{
    return {std::atan2(vec.y), std::atan2(vec.x)};
}

template <typename T>
[[nodiscard]] inline auto abs(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::abs(vec.x), std::abs(vec.y)};
}

template <typename T>
[[nodiscard]] inline auto distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline auto squared_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline auto midpoint(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return (lhs + rhs) * 0.5f;
}

template <typename T>
[[nodiscard]] inline auto floor(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    auto x = lhs.x;
    auto y = lhs.y;

    if (rhs.x < x)
        x = rhs.x;
    if (rhs.y < y)
        y = rhs.y;

    return {x, y};
}

template <typename T>
[[nodiscard]] inline auto ceil(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    auto x = lhs.x;
    auto y = lhs.y;

    if (rhs.x > x)
        x = rhs.x;
    if (rhs.y > y)
        y = rhs.y;

    return {x, y};
}

template <typename T>
[[nodiscard]] inline auto ptr(vector2<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <typename T>
[[nodiscard]] inline auto ptr(const vector2<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math
