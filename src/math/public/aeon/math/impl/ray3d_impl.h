// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr ray3d<T>::ray3d() noexcept
    : normal{}
    , origin{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr ray3d<T>::ray3d(const vector3<T> normal) noexcept
    : normal{normal}
    , origin{}
{
}

template <common::concepts::arithmetic_convertible T>
inline constexpr ray3d<T>::ray3d(const vector3<T> normal, const vector3<T> origin) noexcept
    : normal{normal}
    , origin{origin}
{
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normal(const ray3d<T> &ray) noexcept -> vector3<T>
{
    return ray.normal;
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto origin(const ray3d<T> &ray) noexcept -> vector3<T>
{
    return ray.origin;
}

template <common::concepts::arithmetic_convertible T>
constexpr void normalize(ray3d<T> &ray) noexcept
{
    ray = normalized(ray);
}

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const ray3d<T> &ray) noexcept -> ray3d<T>
{
    return ray3d<T>{normalized(normal(ray)), origin(ray)};
}

} // namespace aeon::math
