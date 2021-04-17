// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/file/file.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_load)
{
    EXPECT_NO_THROW([[maybe_unused]] const auto image =
                        imaging::file::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png"));
    EXPECT_NO_THROW([[maybe_unused]] const auto image =
                        imaging::file::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.jpg"));
    EXPECT_NO_THROW([[maybe_unused]] const auto image =
                        imaging::file::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.bmp"));
}
