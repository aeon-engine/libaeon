// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>

#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/converters/stride.h>
#include <aeon/imaging/converters/convert_encoding.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_load_bmp)
{
    const auto image = imaging::file::bmp::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.bmp");

    const auto new_image = imaging::convert::remove_stride(image);
    const auto new_image2 = imaging::convert::to_rgb24(new_image);

    imaging::file::png::save(new_image2, "test_load_bmp.png");
}
