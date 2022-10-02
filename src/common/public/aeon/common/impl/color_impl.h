// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/color_limits.h>
#include <algorithm>

namespace aeon::common
{

namespace internal
{

template <concepts::arithmetic from_t, concepts::arithmetic to_t>
struct convert_rgb_color_type
{
    [[nodiscard]] constexpr static auto convert(const from_t from) noexcept -> to_t
    {
        return static_cast<to_t>(from);
    }
};

template <>
struct convert_rgb_color_type<std::uint8_t, float>
{
    [[nodiscard]] constexpr static auto convert(const std::uint8_t from) noexcept -> float
    {
        return static_cast<float>(from) / 255.0f;
    }
};

template <>
struct convert_rgb_color_type<std::uint8_t, double>
{
    [[nodiscard]] constexpr static auto convert(const std::uint8_t from) noexcept -> double
    {
        return static_cast<double>(from) / 255.0;
    }
};

template <>
struct convert_rgb_color_type<float, std::uint8_t>
{
    [[nodiscard]] constexpr static auto convert(const float from) noexcept -> std::uint8_t
    {
        const auto result = static_cast<int>(from * 255.0f);
        return static_cast<std::uint8_t>(std::clamp(result, 0, 255));
    }
};

template <>
struct convert_rgb_color_type<double, std::uint8_t>
{
    [[nodiscard]] constexpr static auto convert(const double from) noexcept -> std::uint8_t
    {
        const auto result = static_cast<int>(from * 255.0);
        return static_cast<std::uint8_t>(std::clamp(result, 0, 255));
    }
};

} // namespace internal

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
template <concepts::arithmetic U>
inline constexpr color_rgb<T>::color_rgb(const U r, const U g, const U b) noexcept
    : color_rgb<T>{internal::convert_rgb_color_type<U, T>::convert(r),
                   internal::convert_rgb_color_type<U, T>::convert(g),
                   internal::convert_rgb_color_type<U, T>::convert(b)}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgb<T>::color_rgb(const color_rgb<U> color) noexcept
    : color_rgb<T>{internal::convert_rgb_color_type<U, T>::convert(color.r),
                   internal::convert_rgb_color_type<U, T>::convert(color.g),
                   internal::convert_rgb_color_type<U, T>::convert(color.b)}
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
inline constexpr color_rgba<T>::color_rgba(const color_rgb<type> color) noexcept
    : color_rgba<T>{color.r, color.g, color.b, color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
inline constexpr color_rgba<T>::color_rgba(const color_rgb<type> color, const type a) noexcept
    : color_rgba<T>{color.r, color.g, color.b, a}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgba<T>::color_rgba(const U r, const U g, const U b) noexcept
    : color_rgba<T>{internal::convert_rgb_color_type<U, T>::convert(r),
                    internal::convert_rgb_color_type<U, T>::convert(g),
                    internal::convert_rgb_color_type<U, T>::convert(b), color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgba<T>::color_rgba(const U r, const U g, const U b, const U a) noexcept
    : color_rgba<T>{
          internal::convert_rgb_color_type<U, T>::convert(r), internal::convert_rgb_color_type<U, T>::convert(g),
          internal::convert_rgb_color_type<U, T>::convert(b), internal::convert_rgb_color_type<U, T>::convert(a)}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgba<T>::color_rgba(const color_rgb<U> color) noexcept
    : color_rgba<T>{internal::convert_rgb_color_type<U, T>::convert(color.r),
                    internal::convert_rgb_color_type<U, T>::convert(color.g),
                    internal::convert_rgb_color_type<U, T>::convert(color.b), color_limits<type>::max()}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgba<T>::color_rgba(const color_rgb<U> color, const U a) noexcept
    : color_rgba<T>{internal::convert_rgb_color_type<U, T>::convert(color.r),
                    internal::convert_rgb_color_type<U, T>::convert(color.g),
                    internal::convert_rgb_color_type<U, T>::convert(color.b),
                    internal::convert_rgb_color_type<U, T>::convert(a)}
{
}

template <concepts::arithmetic T>
template <concepts::arithmetic U>
inline constexpr color_rgba<T>::color_rgba(const color_rgba<U> color) noexcept
    : color_rgba<T>{internal::convert_rgb_color_type<U, T>::convert(color.r),
                    internal::convert_rgb_color_type<U, T>::convert(color.g),
                    internal::convert_rgb_color_type<U, T>::convert(color.b),
                    internal::convert_rgb_color_type<U, T>::convert(color.a)}
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
