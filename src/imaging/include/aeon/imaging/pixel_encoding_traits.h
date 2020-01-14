// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding.h>

namespace aeon::imaging
{

template <typename T>
struct pixel_encoding_trait
{
};

template <>
struct pixel_encoding_trait<std::uint8_t>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned8;
    }
};

template <>
struct pixel_encoding_trait<std::uint16_t>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned16;
    }
};

template <>
struct pixel_encoding_trait<std::uint32_t>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned32;
    }
};

template <>
struct pixel_encoding_trait<float>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::float32;
    }
};

template <>
struct pixel_encoding_trait<rgb24>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgb24;
    }
};

template <>
struct pixel_encoding_trait<rgba32>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgba32;
    }
};

template <>
struct pixel_encoding_trait<bgr24>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::bgr24;
    }
};

template <>
struct pixel_encoding_trait<bgra32>
{
    [[nodiscard]] static constexpr auto encoding() noexcept
    {
        return pixel_encoding::bgra32;
    }
};

[[nodiscard]] inline constexpr auto bytes_per_pixel(const pixel_encoding encoding) noexcept -> std::ptrdiff_t
{
    switch (encoding)
    {
        case pixel_encoding::unsigned8:
            return sizeof(std::uint8_t);
        case pixel_encoding::unsigned16:
            return sizeof(std::uint16_t);
        case pixel_encoding::unsigned32:
            return sizeof(std::uint32_t);
        case pixel_encoding::float32:
            return sizeof(float);
        case pixel_encoding::rgb24:
            return sizeof(rgb24);
        case pixel_encoding::rgba32:
            return sizeof(rgba32);
        case pixel_encoding::bgr24:
            return sizeof(bgr24);
        case pixel_encoding::bgra32:
            return sizeof(bgra32);
        default:
            aeon_assert_fail("Invalid pixel encoding.");
            return 1;
    }
}

} // namespace aeon::imaging
