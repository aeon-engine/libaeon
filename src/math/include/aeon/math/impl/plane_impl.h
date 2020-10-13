// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/math.h>

namespace aeon::math
{

template <typename T>
inline constexpr plane<T>::plane() noexcept
    : normal{}
    , distance{}
{
}

template <typename T>
inline constexpr plane<T>::plane(const T a, const T b, const T c, const T distance) noexcept
    : normal{a, b, c}
    , distance{distance}
{
}

template <typename T>
inline constexpr plane<T>::plane(const vector3<T> normal) noexcept
    : normal{normal}
    , distance{}
{
}

template <typename T>
inline constexpr plane<T>::plane(const vector3<T> normal, const T distance) noexcept
    : normal{normal}
    , distance{distance}
{
}

template <typename T>
inline constexpr plane<T>::plane(const vector3<T> point, const vector3<T> normal) noexcept
    : normal{normal}
    , distance{dot(normal, point)}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto normal(const plane<T> &plane) noexcept -> vector3<T>
{
    return plane.normal;
}

template <typename T>
[[nodiscard]] inline constexpr auto distance(const plane<T> &plane) noexcept -> T
{
    return plane.distance;
}

template <typename T>
inline constexpr void normalize(plane<T> &plane) noexcept
{
    plane = normalized(plane);
}

template <typename T>
[[nodiscard]] inline constexpr auto normalized(const plane<T> &p) noexcept -> plane<T>
{
    const auto l = length(normal(p));

    if (l == T{})
        return {};

    return {normal(p) /= l, distance(p) /= l};
}

template <typename T>
[[nodiscard]] inline constexpr auto center(const plane<T> &plane) noexcept -> vector3<T>
{
    return normal(plane) * distance(plane);
}

} // namespace aeon::math
