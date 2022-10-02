// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/image.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_construct_image8)
{
    const imaging::image image{imaging::format::r8_uint, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(std::uint8_t), math::size(image));
}

TEST(test_imaging, test_construct_float32)
{
    const imaging::image image{imaging::format::r32_float, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(float), math::size(image));
}

TEST(test_imaging, test_construct_rgb24)
{
    const imaging::image image{imaging::format::r8g8b8_uint, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(std::uint8_t) * 3, math::size(image));
}
