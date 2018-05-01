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
#include <aeon/math/simplex_noise.h>
#include <cassert>

namespace aeon::imaging::generators
{

inline void simplex_noise(image &image, const float octaves, const float persistence, const float scale) noexcept
{
    assert(encoding(image) == pixel_encoding::float32);
    assert(continuous(image));

    const auto image_width = width(image);

    auto offset = 0u;
    for (auto &pixel : imaging::pixel_iterator<float>(image))
    {
        const auto x = static_cast<float>(offset % image_width);
        const auto y = static_cast<float>(offset / image_width);
        pixel = math::simplex_noise::scaled_octave_noise_2d(octaves, persistence, scale, 0.0f, 1.0f, x, y);
        ++offset;
    }
}

} // namespace aeon::imaging::generators
