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

namespace internal
{

template <typename from_t, typename to_t>
inline auto to_pixel_encoding(const image_view<from_t> &img, to_t (*converter)(const from_t)) -> image<to_t>
{
    aeon_assert(!null(img), "Given image can not be null.");
    aeon_assert(continuous(img), "to_pixel_encoding only works on continuous images.");

    const image_descriptor<to_t> d{width(img), height(img)};
    image<to_t> new_image(d);

    const auto src_image_data = img.data();
    const auto new_image_data = new_image.data();

    const auto dims = width(img) * height(img);

    for (auto i = 0; i < dims; ++i)
    {
        new_image_data[i] = converter(src_image_data[i]);
    }

    return new_image;
}

} // namespace internal

class convert_exception : public imaging_exception
{
};

auto to_rgb24(const dynamic_image &img) -> image<rgb24>;
auto to_bgr24(const dynamic_image &img) -> image<bgr24>;
auto to_rgba32(const dynamic_image &img) -> image<rgba32>;
auto to_bgra32(const dynamic_image &img) -> image<bgra32>;

template <typename T>
inline auto to_rgb24(const image_view<T> &img) -> image<rgb24>
{
    return internal::to_pixel_encoding<T, rgb24>(img, pixel<T>::to_rgb24);
}

template <typename T>
inline auto to_bgr24(const image_view<T> &img) -> image<bgr24>
{
    return internal::to_pixel_encoding<T, bgr24>(img, pixel<T>::to_bgr24);
}

template <typename T>
inline auto to_rgba32(const image_view<T> &img) -> image<rgba32>
{
    return internal::to_pixel_encoding<T, rgba32>(img, pixel<T>::to_rgba32);
}

template <typename T>
inline auto to_bgra32(const image_view<T> &img) -> image<bgra32>
{
    return internal::to_pixel_encoding<T, bgra32>(img, pixel<T>::to_bgra32);
}

} // namespace aeon::imaging::convert
