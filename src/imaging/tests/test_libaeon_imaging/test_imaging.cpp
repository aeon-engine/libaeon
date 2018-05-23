/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>

#include <aeon/imaging/image.h>
#include "aeon/imaging/pixel_encoding.h"

using namespace aeon;

TEST(test_imaging, test_construct_image8)
{
    imaging::image_descriptor<std::uint8_t> d{10, 10};
    imaging::image<std::uint8_t> image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint8_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_image16)
{
    imaging::image_descriptor<std::uint16_t> d{10, 10};
    imaging::image<std::uint16_t> image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(std::uint16_t), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_float32)
{
    imaging::image_descriptor<float> d{10, 10};
    imaging::image<float> image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(float), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_construct_rgb24)
{
    imaging::image_descriptor<imaging::rgb24> d{10, 10};
    imaging::image<imaging::rgb24> image{d};

    EXPECT_EQ(10 * 10 * aeon_signed_sizeof(imaging::rgb24), imaging::size(image));
    EXPECT_EQ(d, imaging::descriptor(image));
}

TEST(test_imaging, test_image_float_data)
{
    imaging::image_descriptor<float> d{3, 3};
    imaging::image<float> image{d};

    const auto data = image.view().data<float>();
    for (auto i = 0u; i < (3 * 3); ++i)
    {
        data[i] = 1.0f;
    }
}

TEST(test_imaging, test_image_free_functions)
{
    imaging::image_descriptor<float> d{3, 3};
    imaging::image<float> image{d};

    ASSERT_EQ(imaging::width(d), imaging::width(image));
    ASSERT_EQ(imaging::height(d), imaging::height(image));
    ASSERT_EQ(imaging::stride_x(d), imaging::stride_x(image));
}
