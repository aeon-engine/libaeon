// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/converters/stride.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_load_bmp)
{
    const auto image = imaging::file::bmp::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.bmp");

    const auto new_image = imaging::convert::remove_stride(image);
    const auto new_image2 = imaging::swizzle_copy<math::swizzle_b, math::swizzle_g, math::swizzle_r>(
        new_image, imaging::format::r8g8b8_uint);

    imaging::file::png::save(new_image2, "test_load_bmp.png");
}
