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
#include <aeon/math/rectangle.h>

namespace aeon::imaging::filters
{

template <typename T>
inline void fill(image_view<T> &img, const T color)
{
    const auto w = imaging::width(img);
    const auto h = imaging::height(img);

    for (auto y = 0; y < h; ++y)
    {
        for (auto x = 0; x < w; ++x)
        {
            img.at({x, y}) = color;
        }
    }
}

template <typename T>
inline void fill(dynamic_image &img, const T color)
{
    process_image(img, fill, color);
}

template <typename T>
inline void fill(image_view<T> &img, const math::rectangle<dimension> rect, const T color)
{
    aeon_assert(math::contains(rect, rectangle(img)), "Rectangle does not fit within image.");

    for (auto y = math::top(rect); y < math::bottom(rect); ++y)
    {
        for (auto x = math::left(rect); x < math::right(rect); ++x)
        {
            img.at({x, y}) = color;
        }
    }
}

template <typename T>
inline void fill(dynamic_image &img, const math::rectangle<dimension> rect, const T color)
{
    process_image(img, fill, rect, color);
}

} // namespace aeon::imaging::filters
