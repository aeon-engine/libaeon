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

#include <aeon/imaging/image_view.h>

namespace aeon::imaging::filters
{

template <typename T>
inline auto invert_horizontally(const image_view<T> &img) -> image<T>
{
    const auto w = width(img);
    const auto h = height(img);

    image<T> new_image(descriptor(img));

    for (auto y = 0; y < h; ++y)
    {
        for (auto x = 0; x < w; ++x)
        {
            const auto pixel_offset = img.template at<std::uint8_t>({x, y});
            const auto new_pixel_offset = view(new_image).template at<std::uint8_t>({w - x - 1, y});

            for (auto offset = 0u; offset < sizeof(T); ++offset)
                *(new_pixel_offset + offset) = *(pixel_offset + offset);
        }
    }

    return new_image;
}

inline auto invert_horizontally(const dynamic_image &img) -> dynamic_image
{
    return process_image(img, invert_horizontally);
}

template <typename T>
inline auto invert_vertically(const image_view<T> &img) -> image<T>
{
    aeon_assert(continuous(img), "invert_vertically only works on continuous images.");

    image<T> new_image(descriptor(img));

    const auto src_data = img.template data<std::uint8_t>();
    const auto dst_data = view(new_image).template data<std::uint8_t>();

    for (auto y = 0; y < height(img); ++y)
    {
        const auto offset = y * stride_y(img);
        const auto src_scanline = &src_data[offset];
        const auto src_scanline_end = &src_data[offset + width(img) * sizeof(T)];

        const auto dst_offset = (height(img) - y - 1) * stride_y(new_image);
        const auto dst_scanline = &dst_data[dst_offset];

        std::copy(src_scanline, src_scanline_end, dst_scanline);
    }

    return new_image;
}

inline auto invert_vertically(const dynamic_image &img) -> dynamic_image
{
    return process_image(img, invert_vertically);
}

} // namespace aeon::imaging::filters
