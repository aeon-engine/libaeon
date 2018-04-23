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

namespace aeon::imaging::convert
{

template <typename pixel_type_t>
struct pixel
{
    static auto to_rgb24(const pixel_type_t pixel) noexcept -> rgb24
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
};

template <>
struct pixel<float>
{
    static auto to_rgb24(const float pixel) noexcept -> rgb24
    {
        const auto rgb_pixel = static_cast<std::uint8_t>(pixel * 255.0f);
        return {rgb_pixel, rgb_pixel, rgb_pixel};
    }
};

template <>
struct pixel<rgb24>
{
    static auto to_rgb24(const rgb24 pixel) noexcept -> rgb24
    {
        return pixel;
    }
};

template <>
struct pixel<rgba32>
{
    static auto to_rgb24(const rgba32 pixel) noexcept -> rgb24
    {
        return {pixel.r, pixel.g, pixel.b};
    }
};

template <>
struct pixel<bgr24>
{
    static auto to_rgb24(const bgr24 pixel) noexcept -> rgb24
    {
        return {pixel.r, pixel.g, pixel.b};
    }
};

} // namespace aeon::imaging::convert
