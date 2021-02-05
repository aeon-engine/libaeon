// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/shared_image.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_construct_image8)
{
    imaging::image_descriptor<std::uint8_t> d{10, 10};
    imaging::image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint8_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_image16)
{
    imaging::image_descriptor<std::uint16_t> d{10, 10};
    imaging::image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint16_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_float32)
{
    imaging::image_descriptor<float> d{10, 10};
    imaging::image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(float), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_rgb24)
{
    imaging::image_descriptor<imaging::rgb24> d{10, 10};
    imaging::image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(imaging::rgb24), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_image_float_data)
{
    imaging::image_descriptor<float> d{3, 3};
    imaging::image image{d};

    const auto data = image.data<float>();
    for (auto i = 0u; i < (3 * 3); ++i)
    {
        data[i] = 1.0f;
    }
}

TEST(test_imaging, test_image_free_functions)
{
    imaging::image_descriptor<float> d{3, 3};
    imaging::image image{d};

    ASSERT_EQ(imaging::width(d), imaging::width(image));
    ASSERT_EQ(imaging::height(d), imaging::height(image));
    ASSERT_EQ(imaging::stride(d), imaging::stride(image));
}

TEST(test_imaging, test_construct_dynamic_image)
{
    imaging::dynamic_image_descriptor d{imaging::pixel_encoding::unsigned8, 10, 10};
    imaging::dynamic_image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint8_t), imaging::size(image));
    EXPECT_EQ(imaging::pixel_encoding::unsigned8, imaging::encoding(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_shared_image8)
{
    imaging::image_descriptor<std::uint8_t> d{10, 10};
    imaging::shared_image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint8_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_shared_image16)
{
    imaging::image_descriptor<std::uint16_t> d{10, 10};
    imaging::shared_image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint16_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_shared_float32)
{
    imaging::image_descriptor<float> d{10, 10};
    imaging::shared_image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(float), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_shared_rgb24)
{
    imaging::image_descriptor<imaging::rgb24> d{10, 10};
    imaging::shared_image image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(imaging::rgb24), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}
