// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/image.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_construct_image8)
{
    const imaging::image image{common::element_type::u8_1, imaging::pixel_encoding::monochrome, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(std::uint8_t), math::size(image));
}

TEST(test_imaging, test_construct_image16)
{
    const imaging::image image{common::element_type::u16_1, imaging::pixel_encoding::monochrome, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(std::uint16_t), math::size(image));
}

TEST(test_imaging, test_construct_float32)
{
    const imaging::image image{common::element_type::f32_1, imaging::pixel_encoding::monochrome, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(float), math::size(image));
}

TEST(test_imaging, test_construct_rgb24)
{
    const imaging::image image{common::element_type::u8_3, imaging::pixel_encoding::rgb, 3, 3};
    EXPECT_EQ(3ull * 3ull * sizeof(std::uint8_t) * 3, math::size(image));
}
