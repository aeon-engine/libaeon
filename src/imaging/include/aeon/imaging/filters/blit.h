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
#include <aeon/types/coordinate.h>
#include <aeon/common/assert.h>

namespace aeon::imaging::filters
{

template <typename T>
inline void blit(const image_view<T> &src, image_view<T> &dst, const types::coordinate<dimension> pos)
{
    aeon_assert(types::contains(types::translate(rectangle(src), pos), rectangle(dst)),
                "Source does not fit within destination.");

    const auto w = width(src);
    const auto h = height(src);
    const auto src_stride = stride_y(src) / sizeof(T);
    const auto src_data = src.data();

    auto dst_data = dst.data();
    const auto dst_stride = stride_y(dst) / sizeof(T);

    for (auto y = 0; y < h; ++y)
    {
        const auto src_row = &src_data[y * src_stride];
        auto dst_row = &dst_data[(pos.y + y) * dst_stride];

        for (auto x = 0; x < w; ++x)
        {
            dst_row[x + pos.x] = src_row[x];
        }
    }
}

inline void blit(const dynamic_image &src, dynamic_image &dst, const types::coordinate<dimension> pos)
{
    process_image2(src, dst, blit, pos);
}

} // namespace aeon::imaging::filters
