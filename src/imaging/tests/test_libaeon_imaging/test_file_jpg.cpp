// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/file/jpg_file.h>
#include <aeon/imaging/file/png_file.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_load_jpg)
{
    const auto image = imaging::file::jpg::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.jpg");
    imaging::file::png::save(image, "test_load_jpg.png");
}

TEST(test_imaging, test_save_jpg)
{
    const auto image = imaging::file::jpg::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.jpg");
    imaging::file::jpg::save(image, imaging::file::jpg::subsample_mode::subsample_440, 60, "test_save_jpg.jpg");
}

TEST(test_imaging, test_load_and_save_jpg_make_view_crop)
{
    auto image = imaging::file::jpg::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.jpg");
    ASSERT_EQ(imaging::pixel_format(image), imaging::format::r8g8b8_uint);

    const auto view = imaging::make_view(image, {400, 300, 450 + 200, 300 + 130});
    imaging::file::jpg::save(view, imaging::file::jpg::subsample_mode::subsample_440, 60, "test_save_jpg_cropped.jpg");
}
