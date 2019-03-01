// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/common/assert.h>
#include <cmath>
#include <limits>

namespace aeon::math
{

template <typename T>
inline vector3<T>::vector3() noexcept
    : x{}
    , y{}
    , z{}
{
}

template <typename T>
inline vector3<T>::vector3(const T xyz) noexcept
    : x{xyz}
    , y{xyz}
    , z{xyz}
{
}

template <typename T>
inline vector3<T>::vector3(const T x, const T y) noexcept
    : x{x}
    , y{y}
    , z{}
{
}

template <typename T>
inline vector3<T>::vector3(const T x, const T y, const T z) noexcept
    : x{x}
    , y{y}
    , z{z}
{
}

template <typename T>
template <typename U>
inline vector3<T>::vector3(const U x, const U y) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{}
{
}

template <typename T>
template <typename U>
inline vector3<T>::vector3(const U x, const U y, const U z) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{static_cast<T>(z)}
{
}

template <typename T>
template <typename U>
inline vector3<T>::vector3(const vector3<U> &vec) noexcept
    : x{static_cast<T>(vec.x)}
    , y{static_cast<T>(vec.y)}
    , z{static_cast<T>(vec.z)}
{
}

template <typename T>
inline vector3<T>::vector3(const vector2<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{}
{
}

template <typename T>
inline vector3<T>::vector3(const vector2<T> vec, const T z) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
{
}

template <typename T>
inline vector3<T>::vector3(const T xyz[3]) noexcept
    : x{xyz[0]}
    , y{xyz[1]}
    , z{xyz[2]}
{
}

template <typename T>
[[nodiscard]] inline auto vector3<T>::operator=(const vector2<T> &vec) noexcept -> vector3<T> &
{
    x = vec.x;
    y = vec.y;
    z = T{};
    return *this;
}

template <typename T>
[[nodiscard]] inline auto vector3<T>::operator[](const std::size_t i) noexcept -> T &
{
    aeon_assert_array_bounds(value, i);
    return value[i];
}

template <typename T>
[[nodiscard]] inline auto vector3<T>::operator[](const std::size_t i) const noexcept -> const T &
{
    aeon_assert_array_bounds(value, i);
    return value[i];
}

template <typename T>
[[nodiscard]] inline auto vector3<T>::zero() noexcept -> vector3<T>
{
    return vector3<T>{};
}

template <typename T>
inline void vector3<T>::set(const T new_x, const T new_y, const T new_z) noexcept
{
    x = new_x;
    y = new_y;
    z = new_z;
}

template <typename T>
inline void translate(vector3<T> &lhs, const T x, const T y, const T z) noexcept
{
    lhs += vector3{x, y, z};
}

template <typename T>
inline void translate(vector3<T> &lhs, const vector3<T> &rhs) noexcept
{
    lhs += rhs;
}

template <typename T>
[[nodiscard]] inline auto translated(const vector3<T> &lhs, const T x, const T y, const T z) noexcept -> vector3<T>
{
    return lhs + vector3{x, y, z};
}

template <typename T>
[[nodiscard]] inline auto translated(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return lhs + rhs;
}

template <typename T>
[[nodiscard]] inline auto dot(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template <typename T>
[[nodiscard]] inline auto cross(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return {(lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z), (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

template <typename T>
[[nodiscard]] inline auto length(const vector3<T> &vec) noexcept -> T
{
    return std::sqrt(dot(vec, vec));
}

template <typename T>
[[nodiscard]] inline auto squared_length(const vector3<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <typename T>
inline void normalize(vector3<T> &vec) noexcept
{
    vec = normalized(vec);
}

template <typename T>
[[nodiscard]] inline auto normalized(const vector3<T> &vec) noexcept -> vector3<T>
{
    auto l = length(vec);

    if (l > std::numeric_limits<T>::epsilon())
        return vec / l;

    return vector3<T>::zero();
}

template <typename T>
[[nodiscard]] inline auto sin(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::sin(vec.x), std::sin(vec.y), std::sin(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto cos(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::cos(vec.x), std::cos(vec.y), std::cos(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto tan(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::tan(vec.x), std::tan(vec.y), std::tan(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto asin(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::asin(vec.x), std::asin(vec.y), std::asin(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto acos(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::acos(vec.x), std::acos(vec.y), std::acos(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto atan(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::atan(vec.x), std::atan(vec.y), std::atan(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto abs(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {std::abs(vec.x), std::abs(vec.y), std::abs(vec.z)};
}

template <typename T>
[[nodiscard]] inline auto distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline auto squared_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline auto midpoint(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    return (lhs + rhs) * 0.5f;
}

template <typename T>
[[nodiscard]] inline auto floor(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;

    if (rhs.x < x)
        x = rhs.x;
    if (rhs.y < y)
        y = rhs.y;
    if (rhs.z < z)
        z = rhs.z;

    return {x, y, z};
}

template <typename T>
[[nodiscard]] inline auto ceil(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;

    if (rhs.x > x)
        x = rhs.x;
    if (rhs.y > y)
        y = rhs.y;
    if (rhs.z > z)
        z = rhs.z;

    return {x, y, z};
}

template <typename T>
[[nodiscard]] inline auto ptr(vector3<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <typename T>
[[nodiscard]] inline auto ptr(const vector3<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math
