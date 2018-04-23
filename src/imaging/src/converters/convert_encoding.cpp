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

#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/imaging/converters/convert_pixel.h>
#include <cassert>

namespace aeon::imaging::convert
{

template <typename source_pixel_type_t>
auto to_rgb24(const image &img) -> image
{
    const descriptor d(width(img), height(img), pixel_encoding::rgb24);
    image new_image(d);

    const auto src_image_data = data<source_pixel_type_t>(img);
    const auto new_image_data = data<imaging::rgb24>(new_image);

    const auto dims = dimensions(img);

    for (auto i = 0u; i < dims; ++i)
    {
        new_image_data[i] = pixel<source_pixel_type_t>::to_rgb24(src_image_data[i]);
    }

    return new_image;
}

auto to_rgb24(const image &img) -> image
{
    assert(continuous(img));

    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return to_rgb24<std::uint8_t>(img);
        case pixel_encoding::unsigned16:
            return to_rgb24<std::uint16_t>(img);
        case pixel_encoding::unsigned32:
            return to_rgb24<std::uint32_t>(img);
        case pixel_encoding::float32:
            return to_rgb24<float>(img);
        case pixel_encoding::rgb24:
            return img.clone();
        case pixel_encoding::rgba32:
            return to_rgb24<rgba32>(img);
        case pixel_encoding::bgr24:
            return to_rgb24<bgr24>(img);
        default:
            throw convert_exception();
    }
}

} // namespace aeon::imaging::convert
