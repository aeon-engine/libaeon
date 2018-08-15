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
#include <aeon/imaging/filters/invert.h>
#include <aeon/imaging/filters/resize.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_load_and_save_png)
{
    const auto image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    imaging::file::png::save(image, "test_load_and_save_png.png");
}

TEST(test_imaging, test_load_and_save_png_make_view_crop)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);
    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto view = imaging::make_view(image, {70, 50, 70 + 32, 50 + 50});
    imaging::file::png::save(view, "test_load_and_save_png_cropped.png");
}

TEST(test_imaging, test_load_and_save_png_make_view_crop_scale)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);
    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto view = imaging::make_view(image, {70, 50, 70 + 32, 50 + 50});
    const auto scaled_dynamic_image = imaging::dynamic_image{imaging::filters::resize_bilinear(view, {64, 64})};
    imaging::file::png::save(scaled_dynamic_image, "test_load_and_save_png_cropped_scaled.png");
}

TEST(test_imaging, test_load_and_save_png_invert)
{
    const auto image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");

    const auto vimage = imaging::filters::invert_vertically(image);
    imaging::file::png::save(vimage, "felix_v_invert.png");

    const auto himage = imaging::filters::invert_horizontally(image);
    imaging::file::png::save(himage, "felix_h_invert.png");
}

TEST(test_imaging, test_load_and_save_png_resize)
{
    const auto image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    const auto scaled_image = imaging::filters::resize_bilinear(image, {1024, 1024});
    imaging::file::png::save(scaled_image, "felix_1024x1024.png");
}

TEST(test_imaging, test_load_and_save_png_resize_downscale)
{
    const auto image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    const auto scaled_image = imaging::filters::resize_bilinear(image, {24, 24});
    imaging::file::png::save(scaled_image, "felix_24x24.png");
}
