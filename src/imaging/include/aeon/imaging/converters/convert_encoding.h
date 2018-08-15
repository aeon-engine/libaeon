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
#include <aeon/imaging/converters/convert_pixel.h>
#include <aeon/common/assert.h>

namespace aeon::imaging::convert
{

class convert_exception : public imaging_exception
{
};

auto to_rgb24(const dynamic_image &img) -> image<rgb24>;

template <typename T>
inline auto to_rgb24(const image<T> &img) -> image<rgb24>
{
    aeon_assert(continuous(img), "to_rgb24 only works on continuous images.");

    const image_descriptor<rgb24> d{width(img), height(img)};
    image<rgb24> new_image(d);

    const auto src_image_data = img.data();
    const auto new_image_data = new_image.data();

    const auto dims = width(img) * height(img);

    for (auto i = 0; i < dims; ++i)
    {
        new_image_data[i] = pixel<T>::to_rgb24(src_image_data[i]);
    }

    return new_image;
}

} // namespace aeon::imaging::convert
