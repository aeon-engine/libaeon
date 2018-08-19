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

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>

namespace aeon::imaging::convert
{

template <typename T>
inline auto remove_stride(const image<T> &img) -> image<T>
{
    if (continuous(img))
        return img.clone();

    const image_descriptor<T> d{width(img), height(img)};
    image<T> new_image{d};

    const auto src_data = img.template data<std::uint8_t>();
    const auto dst_data = new_image.template data<std::uint8_t>();

    for (auto y = 0; y < height(img); ++y)
    {
        const auto offset = y * stride_y(img);
        const auto src_scanline = &src_data[offset];
        const auto src_scanline_end = &src_data[offset + width(img) * stride_x(img)];

        const auto dst_offset = y * stride_y(new_image);
        const auto dst_scanline = &dst_data[dst_offset];

        std::copy(src_scanline, src_scanline_end, dst_scanline);
    }

    return new_image;
}

inline auto remove_stride(const dynamic_image &img) -> dynamic_image
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return dynamic_image(remove_stride(img.get_image<std::uint8_t>()));
        case pixel_encoding::unsigned16:
            return dynamic_image(remove_stride(img.get_image<std::uint16_t>()));
        case pixel_encoding::unsigned32:
            return dynamic_image(remove_stride(img.get_image<std::uint32_t>()));
        case pixel_encoding::float32:
            return dynamic_image(remove_stride(img.get_image<float>()));
        case pixel_encoding::rgb24:
            return dynamic_image(remove_stride(img.get_image<rgb24>()));
        case pixel_encoding::rgba32:
            return dynamic_image(remove_stride(img.get_image<rgba32>()));
        case pixel_encoding::bgr24:
            return dynamic_image(remove_stride(img.get_image<bgr24>()));
        case pixel_encoding::bgra32:
            return dynamic_image(remove_stride(img.get_image<bgra32>()));
        default:
            throw imaging_exception();
    }
}

} // namespace aeon::imaging::convert
