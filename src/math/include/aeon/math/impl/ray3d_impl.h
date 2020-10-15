// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr ray3d<T>::ray3d() noexcept
    : normal{}
    , origin{}
{
}

template <typename T>
inline constexpr ray3d<T>::ray3d(const vector3<T> normal) noexcept
    : normal{normal}
    , origin{}
{
}

template <typename T>
inline constexpr ray3d<T>::ray3d(const vector3<T> normal, const vector3<T> origin) noexcept
    : normal{normal}
    , origin{origin}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto normal(const ray3d<T> &ray) noexcept -> vector3<T>
{
    return ray.normal;
}

template <typename T>
[[nodiscard]] inline constexpr auto origin(const ray3d<T> &ray) noexcept -> vector3<T>
{
    return ray.origin;
}

template <typename T>
constexpr void normalize(ray3d<T> &ray) noexcept
{
    ray = normalized(ray);
}

template <typename T>
[[nodiscard]] inline constexpr auto normalized(const ray3d<T> &ray) noexcept -> ray3d<T>
{
    return ray3d<T>{normalized(normal(ray)), origin(ray)};
}

} // namespace aeon::math
