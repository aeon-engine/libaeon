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

using namespace aeon;

TEST(test_imaging, test_construct_image8)
{
    imaging::descriptor d{10, 10, imaging::pixel_encoding::unsigned8};
    imaging::image image{d};

    EXPECT_EQ(10 * 10, imaging::size(image));
    EXPECT_EQ(d, image.get_descriptor());
}

TEST(test_imaging, test_construct_image16)
{
    imaging::descriptor d{10, 10, imaging::pixel_encoding::unsigned16};
    imaging::image image{d};

    EXPECT_EQ(10 * 10 * 2, imaging::size(image));
    EXPECT_EQ(d, image.get_descriptor());
}

TEST(test_imaging, test_image_float_data)
{
    imaging::descriptor d{3, 3, imaging::pixel_encoding::float32};
    imaging::image image{d};

    const auto data = image.data<float>();
    for (auto i = 0u; i < (3 * 3); ++i)
    {
        data[i] = 1.0f;
    }
}

TEST(test_imaging, test_image_free_functions)
{
    imaging::descriptor d{3, 3, imaging::pixel_encoding::float32};
    imaging::image image{d};

    ASSERT_EQ(imaging::width(d), imaging::width(image));
    ASSERT_EQ(imaging::height(d), imaging::height(image));
    ASSERT_EQ(imaging::stride(d), imaging::stride(image));
    ASSERT_EQ(imaging::encoding(d), imaging::encoding(image));
}

TEST(test_imaging, test_image_float_data_iterator)
{
    imaging::descriptor d{3, 3, imaging::pixel_encoding::float32};
    imaging::image image{d};

    const auto data = image.data<float>();
    for (auto i = 0u; i < (3 * 3); ++i)
    {
        data[i] = static_cast<float>(i);
    }

    int counter = 0u;
    for (auto itr = std::begin(image); itr != std::end(image); ++itr)
    {
        ASSERT_FLOAT_EQ(*itr.as<float>(), static_cast<float>(counter++));
    }

    ASSERT_EQ(3 * 3, counter);

    counter = 0;
    for (auto pixel : imaging::pixel_iterator<float>(image))
    {
        ASSERT_FLOAT_EQ(pixel, static_cast<float>(counter++));
    }

    ASSERT_EQ(3 * 3, counter);

    for (auto &pixel : imaging::pixel_iterator<float>(image))
    {
        pixel = 3.0f;
    }

    for (auto pixel : imaging::pixel_iterator<float>(image))
    {
        ASSERT_FLOAT_EQ(3.0f, pixel);
    }
}
