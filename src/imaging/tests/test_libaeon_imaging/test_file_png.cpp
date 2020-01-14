// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/invert.h>
#include <aeon/imaging/filters/resize.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

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
