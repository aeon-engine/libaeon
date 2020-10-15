// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <aeon/math/ray3d.h>
#include <optional>

namespace aeon::math
{

template <typename T>
class plane
{
public:
    constexpr plane() noexcept;
    constexpr explicit plane(const T a, const T b, const T c, const T distance) noexcept;
    constexpr explicit plane(const vector3<T> normal) noexcept;
    constexpr explicit plane(const vector3<T> normal, const T distance) noexcept;
    constexpr explicit plane(const vector3<T> point, const vector3<T> normal) noexcept;

    ~plane() noexcept = default;

    constexpr plane(const plane &) noexcept = default;
    constexpr auto operator=(const plane &) noexcept -> plane & = default;

    constexpr plane(plane &&) noexcept = default;
    constexpr auto operator=(plane &&) noexcept -> plane & = default;

    vector3<T> normal;
    T distance;
};

template <typename T>
[[nodiscard]] inline constexpr auto normal(const plane<T> &plane) noexcept -> vector3<T>;

template <typename T>
[[nodiscard]] inline constexpr auto distance(const plane<T> &plane) noexcept -> T;

template <typename T>
inline constexpr void normalize(plane<T> &plane) noexcept;

template <typename T>
[[nodiscard]] inline constexpr auto normalized(const plane<T> &p) noexcept -> plane<T>;

template <typename T>
[[nodiscard]] inline constexpr auto center(const plane<T> &plane) noexcept -> vector3<T>;

template <typename T>
[[nodiscard]] inline constexpr auto intersection(const plane<T> &plane1, const plane<T> &plane2,
                                                 const plane<T> &plane3) noexcept -> std::optional<vector3<T>>;

template <typename T>
[[nodiscard]] inline constexpr auto intersection(const plane<T> &plane, const ray3d<T> &ray) noexcept
    -> std::optional<vector3<T>>;

template <typename T>
inline constexpr auto operator==(const plane<T> &lhs, const plane<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const plane<T> &lhs, const plane<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/plane_impl.h>
#include <aeon/math/impl/plane_operators_impl.h>
