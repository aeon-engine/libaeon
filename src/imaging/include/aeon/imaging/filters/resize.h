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

namespace aeon::imaging::filters
{

template <typename T>
inline auto resize_bilinear(const image_view<T> &img, const math::size2d<dimension> size) -> image<T>
{
    image new_image(image_descriptor<T>{size});
    const auto dst = view(new_image).data();

    const float x_ratio = static_cast<float>(width(img) - 1) / width(size);
    const float y_ratio = static_cast<float>(height(img) - 1) / height(size);
    auto offset = 0;
    for (auto i = 0; i < height(size); ++i)
    {
        for (auto j = 0; j < width(size); ++j)
        {
            const auto x = static_cast<int>(x_ratio * j);
            const auto y = static_cast<int>(y_ratio * i);
            const auto x_diff = (x_ratio * j) - x;
            const auto y_diff = (y_ratio * i) - y;

            const auto &A = img.at({x, y});
            const auto &B = img.at({x + 1, y});
            const auto &C = img.at({x, y + 1});
            const auto &D = img.at({x + 1, y + 1});

            // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
            dst[offset++] = static_cast<T>((A * (1.0f - x_diff) * (1.0f - y_diff)) + (B * (x_diff) * (1.0f - y_diff)) +
                                           (C * (y_diff) * (1.0f - x_diff)) + (D * (x_diff * y_diff)));
        }
    }

    return new_image;
}

inline auto resize_bilinear(const dynamic_image &img, const math::size2d<dimension> size) -> dynamic_image
{
    return process_image_to_copy(img, resize_bilinear, size);
}

} // namespace aeon::imaging::filters
