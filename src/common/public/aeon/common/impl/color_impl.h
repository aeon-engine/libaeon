// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/color_limits.h>

namespace aeon::common
{

template <concepts::arithmetic T>
inline color3<T>::color3() noexcept
    : color3<T>{color_limits<T>::min(), color_limits<T>::min(), color_limits<T>::min()}
{
}

template <concepts::arithmetic T>
inline color3<T>::color3(const type r, const type g, const type b) noexcept
    : r{r}
    , g{g}
    , b{b}
{
}

template <concepts::arithmetic T>
inline color4<T>::color4() noexcept
    : color4<T>{color_limits<type>::min(), color_limits<type>::min(), color_limits<type>::min(),
                color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline color4<T>::color4(const type r, const type g, const type b) noexcept
    : color4<T>{r, g, b, color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline color4<T>::color4(const type r, const type g, const type b, const type a) noexcept
    : r{r}
    , g{g}
    , b{b}
    , a{a}
{
}

template <concepts::arithmetic T>
inline color4<T>::color4(const color3<type> c) noexcept
    : color4<T>{c.r, c.g, c.b, color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline color4<T>::color4(const color3<type> c, const type a) noexcept
    : color4<T>{c.r, c.g, c.b, a}
{
}

} // namespace aeon::common
