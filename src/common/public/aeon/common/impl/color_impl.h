// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/color_limits.h>

namespace aeon::common
{

template <concepts::arithmetic T>
inline constexpr color_rgb<T>::color_rgb() noexcept
    : color_rgb<T>{color_limits<T>::min(), color_limits<T>::min(), color_limits<T>::min()}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgb<T>::color_rgb(const type r, const type g, const type b) noexcept
    : r{r}
    , g{g}
    , b{b}
{
}

template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgb<T> &color) noexcept -> T *
{
    return &color.r;
}

template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgb<T> &color) noexcept -> const T *
{
    return &color.r;
}

template <concepts::arithmetic T>
inline constexpr auto operator==(const color_rgb<T> &lhs, const color_rgb<T> &rhs) noexcept -> bool
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

template <concepts::arithmetic T>
inline constexpr auto operator!=(const color_rgb<T> &lhs, const color_rgb<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba() noexcept
    : color_rgba<T>{color_limits<type>::min(), color_limits<type>::min(), color_limits<type>::min(),
                    color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba(const type r, const type g, const type b) noexcept
    : color_rgba<T>{r, g, b, color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba(const type r, const type g, const type b, const type a) noexcept
    : r{r}
    , g{g}
    , b{b}
    , a{a}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba(const color_rgb<type> c) noexcept
    : color_rgba<T>{c.r, c.g, c.b, color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba(const color_rgb<type> c, const type a) noexcept
    : color_rgba<T>{c.r, c.g, c.b, a}
{
}

template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgba<T> &color) noexcept -> T *
{
    return &color.r;
}

template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgba<T> &color) noexcept -> const T *
{
    return &color.r;
}

template <concepts::arithmetic T>
inline constexpr auto operator==(const color_rgba<T> &lhs, const color_rgba<T> &rhs) noexcept -> bool
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

template <concepts::arithmetic T>
inline constexpr auto operator!=(const color_rgba<T> &lhs, const color_rgba<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::common
