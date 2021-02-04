// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/vector3.h>
#include <aeon/common/assert.h>
#include <cmath>

namespace aeon::math
{

template <typename T>
inline constexpr vector4<T>::vector4() noexcept
    : x{}
    , y{}
    , z{}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const T xyzw) noexcept
    : x{xyzw}
    , y{xyzw}
    , z{xyzw}
    , w{xyzw}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const T x, const T y) noexcept
    : x{x}
    , y{y}
    , z{}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const T x, const T y, const T z) noexcept
    : x{x}
    , y{y}
    , z{z}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const T x, const T y, const T z, const T w) noexcept
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}

template <typename T>
template <typename U>
inline constexpr vector4<T>::vector4(const U x, const U y) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{}
    , w{}
{
}

template <typename T>
template <typename U>
inline constexpr vector4<T>::vector4(const U x, const U y, const U z) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{static_cast<T>(z)}
    , w{}
{
}

template <typename T>
template <typename U>
inline constexpr vector4<T>::vector4(const U x, const U y, const U z, const U w) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
    , z{static_cast<T>(z)}
    , w{static_cast<T>(w)}
{
}

template <typename T>
template <typename U>
inline constexpr vector4<T>::vector4(const vector4<U> &vec) noexcept
    : x{static_cast<T>(vec.x)}
    , y{static_cast<T>(vec.y)}
    , z{static_cast<T>(vec.z)}
    , w{static_cast<T>(vec.w)}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const vector2<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const vector2<T> vec, const T z) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const vector2<T> vec, const T z, const T w) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{z}
    , w{w}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const vector3<T> vec) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{vec.z}
    , w{}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const vector3<T> vec, const T w) noexcept
    : x{vec.x}
    , y{vec.y}
    , z{vec.z}
    , w{w}
{
}

template <typename T>
inline constexpr vector4<T>::vector4(const T xyzw[4]) noexcept
    : x{xyzw[0]}
    , y{xyzw[1]}
    , z{xyzw[2]}
    , w{xyzw[3]}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto vector4<T>::operator=(const vector2<T> &vec) noexcept -> vector4<T> &
{
    x = vec.x;
    y = vec.y;
    z = T{};
    w = T{};
    return *this;
}

template <typename T>
[[nodiscard]] inline constexpr auto vector4<T>::operator=(const vector3<T> &vec) noexcept -> vector4<T> &
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = T{};
    return *this;
}

template <typename T>
[[nodiscard]] inline constexpr auto vector4<T>::operator[](const std::size_t i) noexcept -> T &
{
    std::array<T *, 4> value{&x, &y, &z, &w};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <typename T>
[[nodiscard]] inline constexpr auto vector4<T>::operator[](const std::size_t i) const noexcept -> const T &
{
    std::array<const T *, 4> value{&x, &y, &z, &w};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <typename T>
[[nodiscard]] inline constexpr auto vector4<T>::zero() noexcept -> vector4<T>
{
    return vector4<T>{};
}

template <typename T>
inline constexpr void vector4<T>::set(const T new_x, const T new_y, const T new_z, const T new_w) noexcept
{
    x = new_x;
    y = new_y;
    z = new_z;
    w = new_w;
}

template <typename T>
inline constexpr void translate(vector4<T> &lhs, const T x, const T y, const T z, const T w) noexcept
{
    lhs += vector4{x, y, z, w};
}

template <typename T>
inline constexpr void translate(vector4<T> &lhs, const vector4<T> &rhs) noexcept
{
    lhs += rhs;
}

template <typename T>
[[nodiscard]] inline constexpr auto translated(const vector4<T> &lhs, const T x, const T y, const T z,
                                               const T w) noexcept -> vector4<T>
{
    return lhs + vector4{x, y, z, w};
}

template <typename T>
[[nodiscard]] inline constexpr auto translated(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return lhs + rhs;
}

template <typename T>
[[nodiscard]] inline constexpr auto sum(const vector4<T> &vec) noexcept -> T
{
    return vec.x + vec.y + vec.z + vec.w;
}

template <typename T>
[[nodiscard]] inline constexpr auto dot(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

template <typename T>
[[nodiscard]] inline constexpr auto length(const vector4<T> &vec) noexcept -> T
{
    return std::sqrt(dot(vec, vec));
}

template <typename T>
[[nodiscard]] inline constexpr auto squared_length(const vector4<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <typename T>
inline constexpr void normalize(vector4<T> &vec) noexcept
{
    vec = normalized(vec);
}

template <typename T>
[[nodiscard]] inline constexpr auto normalized(const vector4<T> &vec) noexcept -> vector4<T>
{
    auto l = length(vec);

    if (l > constants<T>::tolerance)
        return vec / l;

    return vector4<T>::zero();
}

template <typename T>
[[nodiscard]] inline constexpr auto min(const vector4<T> &vec) noexcept -> T
{
    return std::min({vec.x, vec.y, vec.z, vec.w});
}

template <typename T>
[[nodiscard]] inline constexpr auto max(const vector4<T> &vec) noexcept -> T
{
    return std::max({vec.x, vec.y, vec.z, vec.w});
}

template <typename T>
[[nodiscard]] inline constexpr auto sin(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::sin(vec.x), std::sin(vec.y), std::sin(vec.z), std::sin(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto cos(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::cos(vec.x), std::cos(vec.y), std::cos(vec.z), std::cos(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto tan(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::tan(vec.x), std::tan(vec.y), std::tan(vec.z), std::tan(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto asin(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::asin(vec.x), std::asin(vec.y), std::asin(vec.z), std::asin(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto acos(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::acos(vec.x), std::acos(vec.y), std::acos(vec.z), std::acos(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto atan(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::atan(vec.x), std::atan(vec.y), std::atan(vec.z), std::atan(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto abs(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {std::abs(vec.x), std::abs(vec.y), std::abs(vec.z), std::abs(vec.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline constexpr auto squared_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <typename T>
[[nodiscard]] inline constexpr auto absolute_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept
    -> vector4<T>
{
    return {std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y), std::abs(lhs.z - rhs.z), std::abs(lhs.w - rhs.w)};
}

template <typename T>
[[nodiscard]] inline constexpr auto manhattan_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T
{
    return sum(absolute_distance(lhs, rhs));
}

template <typename T>
[[nodiscard]] inline constexpr auto midpoint(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    return (lhs + rhs) * 0.5f;
}

template <typename T>
[[nodiscard]] inline constexpr auto floor(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;
    auto w = lhs.w;

    if (rhs.x < x)
        x = rhs.x;

    if (rhs.y < y)
        y = rhs.y;

    if (rhs.z < z)
        z = rhs.z;

    if (rhs.w < w)
        w = rhs.w;

    return {x, y, z, w};
}

template <typename T>
[[nodiscard]] inline constexpr auto ceil(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>
{
    auto x = lhs.x;
    auto y = lhs.y;
    auto z = lhs.z;
    auto w = lhs.w;

    if (rhs.x > x)
        x = rhs.x;

    if (rhs.y > y)
        y = rhs.y;

    if (rhs.z > z)
        z = rhs.z;

    if (rhs.w > w)
        w = rhs.w;

    return {x, y, z, w};
}

template <typename T>
[[nodiscard]] inline constexpr auto ptr(vector4<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <typename T>
[[nodiscard]] inline constexpr auto ptr(const vector4<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math
