// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding.h>

namespace aeon::imaging::convert
{

template <typename pixel_type_t>
struct pixel final
{
    [[nodiscard]] static auto to_rgb24(const pixel_type_t pixel) noexcept -> rgb24
    {
        constexpr auto shift = (sizeof(pixel_type_t) * 8) - 8;

        if constexpr (shift != 0)
        {
            const auto rgb_pixel = static_cast<std::uint8_t>(pixel << shift);
            return {rgb_pixel, rgb_pixel, rgb_pixel};
        }
        else
        {
            return {pixel, pixel, pixel};
        }
    }

    [[nodiscard]] static auto to_rgba32(const pixel_type_t pixel) noexcept -> rgba32
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.r, rgb.g, rgb.b, 255};
    }

    [[nodiscard]] static auto to_bgr24(const pixel_type_t pixel) noexcept -> bgr24
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.b, rgb.g, rgb.r};
    }

    [[nodiscard]] static auto to_bgra32(const pixel_type_t pixel) noexcept -> bgra32
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.b, rgb.g, rgb.r, 255};
    }
};

template <>
struct pixel<float> final
{
    [[nodiscard]] static auto to_rgb24(const float pixel) noexcept -> rgb24
    {
        const auto rgb_pixel = static_cast<std::uint8_t>(pixel * 255.0f);
        return {rgb_pixel, rgb_pixel, rgb_pixel};
    }

    [[nodiscard]] static auto to_rgba32(const float pixel) noexcept -> rgba32
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.r, rgb.g, rgb.b, 255};
    }

    [[nodiscard]] static auto to_bgr24(const float pixel) noexcept -> bgr24
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.b, rgb.g, rgb.r};
    }

    [[nodiscard]] static auto to_bgra32(const float pixel) noexcept -> bgra32
    {
        const auto rgb = to_rgb24(pixel);
        return {rgb.b, rgb.g, rgb.r, 255};
    }
};

template <>
struct pixel<rgb24> final
{
    [[nodiscard]] static auto to_rgb24(const rgb24 pixel) noexcept -> rgb24
    {
        return pixel;
    }

    [[nodiscard]] static auto to_rgba32(const rgb24 pixel) noexcept -> rgba32
    {
        return {pixel.r, pixel.g, pixel.b, 255};
    }

    [[nodiscard]] static auto to_bgr24(const rgb24 pixel) noexcept -> bgr24
    {
        return {pixel.b, pixel.g, pixel.r};
    }

    [[nodiscard]] static auto to_bgra32(const rgb24 pixel) noexcept -> bgra32
    {
        return {pixel.b, pixel.g, pixel.r, 255};
    }
};

template <>
struct pixel<rgba32> final
{
    [[nodiscard]] static auto to_rgb24(const rgba32 pixel) noexcept -> rgb24
    {
        return {pixel.r, pixel.g, pixel.b};
    }

    [[nodiscard]] static auto to_rgba32(const rgba32 pixel) noexcept -> rgba32
    {
        return pixel;
    }

    [[nodiscard]] static auto to_bgr24(const rgba32 pixel) noexcept -> bgr24
    {
        return {pixel.b, pixel.g, pixel.r};
    }

    [[nodiscard]] static auto to_bgra32(const rgba32 pixel) noexcept -> bgra32
    {
        return {pixel.b, pixel.g, pixel.r, pixel.a};
    }
};

template <>
struct pixel<bgr24> final
{
    [[nodiscard]] static auto to_rgb24(const bgr24 pixel) noexcept -> rgb24
    {
        return {pixel.r, pixel.g, pixel.b};
    }

    [[nodiscard]] static auto to_rgba32(const bgr24 pixel) noexcept -> rgba32
    {
        return {pixel.r, pixel.g, pixel.b, 255};
    }

    [[nodiscard]] static auto to_bgr24(const bgr24 pixel) noexcept -> bgr24
    {
        return pixel;
    }

    [[nodiscard]] static auto to_bgra32(const bgr24 pixel) noexcept -> bgra32
    {
        return {pixel.b, pixel.g, pixel.r, 255};
    }
};

template <>
struct pixel<bgra32> final
{
    [[nodiscard]] static auto to_rgb24(const bgra32 pixel) noexcept -> rgb24
    {
        return {pixel.r, pixel.g, pixel.b};
    }

    [[nodiscard]] static auto to_rgba32(const bgra32 pixel) noexcept -> rgba32
    {
        return {pixel.r, pixel.g, pixel.b, pixel.a};
    }

    [[nodiscard]] static auto to_bgr24(const bgra32 pixel) noexcept -> bgr24
    {
        return {pixel.b, pixel.g, pixel.r};
    }

    [[nodiscard]] static auto to_bgra32(const bgra32 pixel) noexcept -> bgra32
    {
        return pixel;
    }
};

} // namespace aeon::imaging::convert
