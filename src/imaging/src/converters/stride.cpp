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

#include <aeon/imaging/converters/stride.h>
#include <cassert>

namespace aeon::imaging::convert
{

auto remove_stride(const image &img) -> image
{
    if (continuous(img))
        return img.clone();

    const descriptor d(width(img), height(img), encoding(img));
    image new_image(d);

    const auto src_data = img.data<std::uint8_t>();
    const auto dst_data = new_image.data<std::uint8_t>();

    for (auto y = 0u; y < height(img); ++y)
    {
        const auto offset = y * stride(img);
        const auto src_scanline = &src_data[offset];
        const auto src_scanline_end = &src_data[offset + width(img) * bytes_per_pixel(img)];

        const auto dst_offset = y * stride(new_image);
        const auto dst_scanline = &dst_data[dst_offset];

        std::copy(src_scanline, src_scanline_end, dst_scanline);
    }

    return new_image;
}

} // namespace aeon::imaging::convert
