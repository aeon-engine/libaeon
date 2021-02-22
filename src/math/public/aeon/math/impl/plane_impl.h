// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane() noexcept
    : normal{}
    , distance{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane(const T a, const T b, const T c, const T distance) noexcept
    : normal{a, b, c}
    , distance{distance}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane(const vector3<T> normal) noexcept
    : normal{normal}
    , distance{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane(const vector3<T> normal, const T distance) noexcept
    : normal{normal}
    , distance{distance}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane(const vector3<T> point, const vector3<T> normal) noexcept
    : normal{normal}
    , distance{dot(normal, point)}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr plane<T>::plane(const vector3<T> &point1, const vector3<T> &point2, const vector3<T> point3,
                                 const winding_order order) noexcept
    : normal{}
    , distance{}
{
    if (order == winding_order::clockwise)
        normal = normalized(cross(point1 - point3, point1 - point2));
    else
        normal = normalized(cross(point1 - point2, point1 - point3));

    distance = dot(normal, point1);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normal(const plane<T> &plane) noexcept -> vector3<T>
{
    return plane.normal;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const plane<T> &plane) noexcept -> T
{
    return plane.distance;
}

template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(plane<T> &plane) noexcept
{
    plane = normalized(plane);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const plane<T> &p) noexcept -> plane<T>
{
    const auto l = length(normal(p));

    if (l == T{})
        return plane<T>{};

    return plane<T>{normal(p) /= l, distance(p) /= l};
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto center(const plane<T> &plane) noexcept -> vector3<T>
{
    return normal(plane) * distance(plane);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto intersection(const plane<T> &plane1, const plane<T> &plane2,
                                                 const plane<T> &plane3) noexcept -> std::optional<vector3<T>>
{
    const auto normal1 = normal(plane1);
    const auto normal2 = normal(plane2);
    const auto normal3 = normal(plane3);

    const auto denominator = dot(cross(normal1, normal2), normal3);

    if (approximately_zero(denominator))
        return std::nullopt;

    return ((cross(normal2, normal3) * distance(plane1)) + (cross(normal3, normal1) * distance(plane2)) +
            (cross(normal1, normal2) * distance(plane3))) /
           denominator;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto intersection(const plane<T> &plane, const ray3d<T> &ray) noexcept
    -> std::optional<vector3<T>>
{
    const auto denominator = dot(normal(plane), normal(ray));

    if (approximately_zero(denominator))
        return std::nullopt;

    const auto distance = (dot(normal(plane), origin(ray)) - distance(plane)) / denominator;

    if (distance > constants<T>::tolerance)
        return std::nullopt;

    distance = -distance;
    return origin(ray) + normal(ray) * distance;
}

} // namespace aeon::math
