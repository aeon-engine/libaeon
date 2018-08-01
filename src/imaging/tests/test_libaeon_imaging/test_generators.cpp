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

#include <gtest/gtest.h>

#include <aeon/imaging/generators/simplex_noise.h>
#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/imaging/filters/resize.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/image.h>

using namespace aeon;

TEST(test_imaging, test_image_generator_perlin_noise)
{
    const imaging::image_descriptor<float> d{128, 128};
    imaging::image image{d};

    imaging::generators::simplex_noise(image, 4.0f, 0.2f, 0.05f);

    const auto rgb_image = imaging::convert::to_rgb24(image);

    imaging::file::png::save(imaging::view(rgb_image), "test_image_generator_perlin_noise.png");
}

TEST(test_imaging, test_image_generator_scale_perlin_noise)
{
    const imaging::image_descriptor<float> d{128, 128};
    imaging::image image{d};

    imaging::generators::simplex_noise(image, 4.0f, 0.2f, 0.05f);
    image = imaging::filters::resize_bilinear(view(image), {250, 500});

    const auto rgb_image = imaging::convert::to_rgb24(image);

    imaging::file::png::save(imaging::view(rgb_image), "test_image_generator_perlin_noise_scaled.png");
}
