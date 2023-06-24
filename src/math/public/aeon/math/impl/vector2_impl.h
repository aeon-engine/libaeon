// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/math.h>
#include <aeon/common/assert.h>
#include <cmath>
#include <array>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr vector2<T>::vector2() noexcept
    : x{}
    , y{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector2<T>::vector2(const T xy) noexcept
    : x{xy}
    , y{xy}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector2<T>::vector2(const T x, const T y) noexcept
    : x{x}
    , y{y}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr vector2<T>::vector2(const U x, const U y) noexcept
    : x{static_cast<T>(x)}
    , y{static_cast<T>(y)}
{
}

template <common::concepts::arithmetic_convertible T>
template <common::concepts::arithmetic_convertible U>
inline constexpr vector2<T>::vector2(const vector2<U> &vec) noexcept
    : x{static_cast<T>(vec.x)}
    , y{static_cast<T>(vec.y)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr vector2<T>::vector2(const T xy[2]) noexcept
    : x{xy[0]}
    , y{xy[1]}
{
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector2<T>::operator[](const std::size_t i) noexcept -> T &
{
    std::array<T *, 2> value{&x, &y};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector2<T>::operator[](const std::size_t i) const noexcept -> const T &
{
    std::array<const T *, 2> value{&x, &y};
    aeon_assert_size_bounds(value, i);
    return *value[i];
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto vector2<T>::zero() noexcept -> vector2<T>
{
    return vector2<T>{};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void vector2<T>::set(const T new_x, const T new_y) noexcept
{
    x = new_x;
    y = new_y;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector2<T> &lhs, const T x, const T y) noexcept
{
    lhs += vector2{x, y};
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector2<T> &lhs, const vector2<T> &rhs) noexcept
{
    lhs += rhs;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector2<T> &lhs, const T x, const T y) noexcept -> vector2<T>
{
    return lhs + vector2{x, y};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return lhs + rhs;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sum(const vector2<T> &vec) noexcept -> T
{
    return vec.x + vec.y;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto dot(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cross(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto length(const vector2<T> &vec) noexcept -> T
{
    if constexpr (!std::is_integral_v<T>)
        return std::sqrt(dot(vec, vec));
    else
        return static_cast<T>(std::sqrt(static_cast<double>(dot(vec, vec))));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_length(const vector2<T> &vec) noexcept -> T
{
    return dot(vec, vec);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(vector2<T> &vec) noexcept
{
    vec = normalized(vec);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const vector2<T> &vec) noexcept -> vector2<T>
{
    const auto l = length(vec);

    if (l > constants<T>::tolerance)
        return vec / l;

    return vector2<T>::zero();
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const vector2<T> &vec) noexcept -> T
{
    return std::min(vec.x, vec.y);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const vector2<T> &vec) noexcept -> T
{
    return std::max(vec.x, vec.y);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sin(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::sin(vec.x), std::sin(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cos(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::cos(vec.x), std::cos(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto tan(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::tan(vec.x), std::tan(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto asin(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::asin(vec.x), std::asin(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto acos(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::acos(vec.x), std::acos(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::atan(vec.x), std::atan(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan2(const vector2<T> &vec) noexcept -> T
{
    return {std::atan2(vec.y), std::atan2(vec.x)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto abs(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::abs(vec.x), std::abs(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return length(lhs - rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return squared_length(lhs - rhs);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto absolute_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept
    -> vector2<T>
{
    return {std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto manhattan_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return sum(absolute_distance(lhs, rhs));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto chebyshev_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T
{
    return max(absolute_distance(lhs, rhs));
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto midpoint(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    return (lhs + rhs) * T(0.5);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    auto x = lhs.x;
    auto y = lhs.y;

    if (rhs.x < x)
        x = rhs.x;
    if (rhs.y < y)
        y = rhs.y;

    return {x, y};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::floor(vec.x), std::floor(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>
{
    auto x = lhs.x;
    auto y = lhs.y;

    if (rhs.x > x)
        x = rhs.x;
    if (rhs.y > y)
        y = rhs.y;

    return {x, y};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::ceil(vec.x), std::ceil(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {std::round(vec.x), std::round(vec.y)};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto angle(const vector2<T> &vec) -> T
{
    return std::atan2(vec.y, vec.x);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_by(const vector2<T> &vec, const unitf<radian> angle,
                                              const vector2<T> &center) noexcept -> vector2<T>
{
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);

    const auto norm_vec = vector2<float>{vec - center};
    return vector2<T>{norm_vec.x * c - norm_vec.y * s, norm_vec.x * s + norm_vec.y * c} + center;
}

template <common::concepts::arithmetic_convertible T, std::floating_point U>
[[nodiscard]] inline constexpr auto interpolate(const vector2<T> &val1, const vector2<T> &val2, const U ratio) noexcept
    -> vector2<T>
{
    const auto inverted = (U(1.0) - ratio);

    return vector2<T>{static_cast<U>(val1.x) * inverted + static_cast<U>(val2.x) * ratio,
                      static_cast<U>(val1.y) * inverted + static_cast<U>(val2.y) * ratio};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto winding(const vector2<T> &vec1, const vector2<T> &vec2,
                                            const vector2<T> &vec3) noexcept -> winding_order
{
    const auto val = (vec2.y - vec1.y) * (vec3.x - vec2.x) - (vec2.x - vec1.x) * (vec3.y - vec2.y);

    if (val > 0)
        return winding_order::clockwise;

    return winding_order::counter_clockwise;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(vector2<T> &vec) noexcept -> T *
{
    return &vec.x;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(const vector2<T> &vec) noexcept -> const T *
{
    return &vec.x;
}

} // namespace aeon::math
