// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/pixel_encoding.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_fill)
{
    imaging::image image{imaging::format::r8g8b8_uint, 256, 256};
    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    math::fill(view1, imaging::rgb24{255, 0, 0});

    auto view2 = imaging::make_view(image, {200, 200, 220, 255});
    math::fill(view2, imaging::rgb24{0, 255, 0});

    auto view3 = imaging::make_view(image, {140, 100, 210, 160});
    math::fill(view3, imaging::rgb24{0, 0, 255});

    imaging::file::png::save(image, "test_fill_rgb24.png");
}

TEST(test_imaging, test_fill_rect)
{
    imaging::image image{imaging::format::r8g8b8_uint, 256, 256};

    math::fill(image, {0, 0, 64, 64}, imaging::rgb24{255, 0, 0});
    math::fill(image, {200, 200, 220, 255}, imaging::rgb24{0, 255, 0});
    math::fill(image, {140, 100, 210, 160}, imaging::rgb24{0, 0, 255});

    imaging::file::png::save(image, "test_fill_rect_rgb24.png");
}
