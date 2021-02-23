// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/compilers.h>
#include <aeon/common/concepts.h>
#include <cstdint>

namespace aeon::common
{

AEON_PACK_STRUCT_PUSH(1)
template <concepts::arithmetic T>
class color_rgb
{
public:
    using type = T;

    constexpr color_rgb() noexcept;
    constexpr explicit color_rgb(const type r, const type g, const type b) noexcept;

    ~color_rgb() = default;

    constexpr color_rgb(const color_rgb &) noexcept = default;
    constexpr auto operator=(const color_rgb &) noexcept -> color_rgb & = default;

    constexpr color_rgb(color_rgb &&) noexcept = default;
    constexpr auto operator=(color_rgb &&) noexcept -> color_rgb & = default;

    type r;
    type g;
    type b;
} AEON_PACK_STRUCT_POP(1);

using color_rgb_u = color_rgb<std::uint8_t>;
using color_rgb_f = color_rgb<float>;
using color_rgb_d = color_rgb<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgb<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgb<T> &color) noexcept -> const T *;

AEON_PACK_STRUCT_PUSH(1)
template <concepts::arithmetic T>
class color_rgba
{
public:
    using type = T;

    constexpr color_rgba() noexcept;

    constexpr explicit color_rgba(const type r, const type g, const type b) noexcept;
    constexpr explicit color_rgba(const type r, const type g, const type b, const type a) noexcept;

    constexpr explicit color_rgba(const color_rgb<type> c) noexcept;
    constexpr explicit color_rgba(const color_rgb<type> c, const type a) noexcept;

    ~color_rgba() = default;

    constexpr color_rgba(const color_rgba &) noexcept = default;
    constexpr auto operator=(const color_rgba &) noexcept -> color_rgba & = default;

    constexpr color_rgba(color_rgba &&) noexcept = default;
    constexpr auto operator=(color_rgba &&) noexcept -> color_rgba & = default;

    type r;
    type g;
    type b;
    type a;
} AEON_PACK_STRUCT_POP(1);

using color_rgba_u = color_rgba<std::uint8_t>;
using color_rgba_f = color_rgba<float>;
using color_rgba_d = color_rgba<double>;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(color_rgba<T> &color) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given color.
 * The color data layout is [r g b a]
 * \param[in] color - Color
 * \return Pointer to color data.
 */
template <concepts::arithmetic T>
[[nodiscard]] inline constexpr auto ptr(const color_rgba<T> &color) noexcept -> const T *;

} // namespace aeon::common

#include <aeon/common/impl/color_impl.h>
