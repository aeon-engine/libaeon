// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/vector4.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector2.h>
#include <aeon/math/swizzle_component.h>
#include <cstdlib>

namespace aeon::math
{

template <swizzle_component one, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector4<T> &vec) noexcept -> T
{
    if constexpr (one == swizzle_component::x)
        return vec.x;

    if constexpr (one == swizzle_component::y)
        return vec.y;

    if constexpr (one == swizzle_component::z)
        return vec.z;

    if constexpr (one == swizzle_component::w)
        return vec.w;
}

template <swizzle_component one, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector3<T> &vec) noexcept -> T
{
    if constexpr (one == swizzle_component::x)
        return vec.x;

    if constexpr (one == swizzle_component::y)
        return vec.y;

    if constexpr (one == swizzle_component::z)
        return vec.z;
}

template <swizzle_component one, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector2<T> &vec) noexcept -> T
{
    if constexpr (one == swizzle_component::x)
        return vec.x;

    if constexpr (one == swizzle_component::y)
        return vec.y;
}

template <swizzle_component one, swizzle_component two, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector2<T> &vec) noexcept -> vector2<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec)};
}

template <swizzle_component one, swizzle_component two, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector3<T> &vec) noexcept -> vector2<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec)};
}

template <swizzle_component one, swizzle_component two, swizzle_component three,
          common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector3<T> &vec) noexcept -> vector3<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec), swizzle<three>(vec)};
}

template <swizzle_component one, swizzle_component two, common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector4<T> &vec) noexcept -> vector2<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec)};
}

template <swizzle_component one, swizzle_component two, swizzle_component three,
          common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector4<T> &vec) noexcept -> vector3<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec), swizzle<three>(vec)};
}

template <swizzle_component one, swizzle_component two, swizzle_component three, swizzle_component four,
          common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto swizzle(const vector4<T> &vec) noexcept -> vector4<T>
{
    return {swizzle<one>(vec), swizzle<two>(vec), swizzle<three>(vec), swizzle<four>(vec)};
}

} // namespace aeon::math
