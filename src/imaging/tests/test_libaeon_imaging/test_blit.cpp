// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_blit)
{
    auto image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::pixel_format(image), imaging::format::r8g8b8a8_uint);

    auto dst = imaging::image{imaging::pixel_format(image), 256, 256};

    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    math::blit(view1, dst, {10, 10});

    auto view2 = imaging::make_view(image, {128, 128, 150, 160});
    math::blit(view2, dst, {40, 40});

    auto view3 = imaging::make_view(image, {140, 100, 210, 160});
    math::blit(view3, dst, {100, 100});

    imaging::file::png::save(dst, "test_blit.png");
}
