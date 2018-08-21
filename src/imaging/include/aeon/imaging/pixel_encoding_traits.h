/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned8;
    }
};

template <>
struct pixel_encoding_trait<std::uint16_t>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned16;
    }
};

template <>
struct pixel_encoding_trait<std::uint32_t>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned32;
    }
};

template <>
struct pixel_encoding_trait<float>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::float32;
    }
};

template <>
struct pixel_encoding_trait<rgb24>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgb24;
    }
};

template <>
struct pixel_encoding_trait<rgba32>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgba32;
    }
};

template <>
struct pixel_encoding_trait<bgr24>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::bgr24;
    }
};

template <>
struct pixel_encoding_trait<bgra32>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::bgra32;
    }
};

inline constexpr auto bytes_per_pixel(const pixel_encoding encoding) noexcept -> std::ptrdiff_t
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
