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

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/blit.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_blit)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);

    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto d = imaging::image_descriptor<imaging::rgba32>{256, 256};
    auto dst = imaging::image{d};

    auto view1 = imaging::make_view(imaging::view(image), {0, 0, 64, 64});
    imaging::filters::blit(view1, imaging::view(dst), {10, 10});

    auto view2 = imaging::make_view(imaging::view(image), {128, 128, 150, 160});
    imaging::filters::blit(view2, imaging::view(dst), {40, 40});

    auto view3 = imaging::make_view(imaging::view(image), {140, 100, 210, 160});
    imaging::filters::blit(view3, imaging::view(dst), {100, 100});

    imaging::file::png::save(imaging::view(dst), "test_blit.png");
}

TEST(test_imaging, test_scale_blit)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);

    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto d = imaging::image_descriptor<imaging::rgba32>{256, 256};
    auto dst = imaging::image{d};

    auto view1 = imaging::make_view(imaging::view(image), {0, 0, 64, 64});
    imaging::filters::scale_blit(view1, imaging::view(dst), {10, 10, 246, 246});

    auto view2 = imaging::make_view(imaging::view(image), {140, 100, 210, 160});
    imaging::filters::scale_blit(view2, imaging::view(dst), {16, 16, 32, 32});

    imaging::file::png::save(imaging::view(dst), "test_scale_blit.png");
}
