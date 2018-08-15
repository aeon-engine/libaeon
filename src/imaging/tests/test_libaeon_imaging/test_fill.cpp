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
#include <aeon/imaging/filters/fill.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_fill)
{
    const imaging::image_descriptor<imaging::rgb24> d{256, 256};
    imaging::image<imaging::rgb24> image{d};

    auto view1 = imaging::make_view(imaging::view(image), {0, 0, 64, 64});
    imaging::filters::fill(view1, {255, 0, 0});

    auto view2 = imaging::make_view(imaging::view(image), {200, 200, 220, 255});
    imaging::filters::fill(view2, {0, 255, 0});

    auto view3 = imaging::make_view(imaging::view(image), {140, 100, 210, 160});
    imaging::filters::fill(view3, {0, 0, 255});

    imaging::file::png::save(imaging::view(image), "test_fill_rgb24.png");
}

TEST(test_imaging, test_fill_rect)
{
    const imaging::image_descriptor<imaging::rgb24> d{256, 256};
    imaging::image<imaging::rgb24> image{d};

    imaging::filters::fill(imaging::view(image), {0, 0, 64, 64}, {255, 0, 0});
    imaging::filters::fill(imaging::view(image), {200, 200, 220, 255}, {0, 255, 0});
    imaging::filters::fill(imaging::view(image), {140, 100, 210, 160}, {0, 0, 255});

    imaging::file::png::save(imaging::view(image), "test_fill_rect_rgb24.png");
}
