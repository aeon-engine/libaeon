// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/vector3.h>

namespace aeon::math
{

template <typename T>
class ray3d
{
public:
    constexpr ray3d() noexcept;
    constexpr explicit ray3d(const vector3<T> normal) noexcept;
    constexpr explicit ray3d(const vector3<T> normal, const vector3<T> origin) noexcept;

    ~ray3d() noexcept = default;

    constexpr ray3d(const ray3d &) noexcept = default;
    constexpr auto operator=(const ray3d &) noexcept -> ray3d & = default;

    constexpr ray3d(ray3d &&) noexcept = default;
    constexpr auto operator=(ray3d &&) noexcept -> ray3d & = default;

    vector3<T> normal;
    vector3<T> origin;
};

template <typename T>
[[nodiscard]] inline constexpr auto normal(const ray3d<T> &ray) noexcept -> vector3<T>;

template <typename T>
[[nodiscard]] inline constexpr auto origin(const ray3d<T> &ray) noexcept -> vector3<T>;

template <typename T>
inline constexpr void normalize(ray3d<T> &ray) noexcept;

template <typename T>
[[nodiscard]] inline constexpr auto normalized(const ray3d<T> &ray) noexcept -> ray3d<T>;

template <typename T>
inline constexpr auto operator==(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/ray3d_impl.h>
#include <aeon/math/impl/ray3d_operators_impl.h>
