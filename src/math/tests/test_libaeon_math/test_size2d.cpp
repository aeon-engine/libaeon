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
#include <aeon/math/size2d.h>
#include <aeon/math/size2d_stream.h>

using namespace aeon;

TEST(test_size2d, test_size2d_default_int)
{
    math::size2d<int> size;
}

struct external_size2d
{
    int width{};
    int height{};
};

TEST(test_size2d, test_size2d_convert_from_unknown)
{
    const external_size2d s{10, 20};

    math::size2d<int> size{math::convert_type{}, s};
    EXPECT_EQ(size.width, 10);
    EXPECT_EQ(size.height, 20);

    const auto s2 = size.convert_to<external_size2d>();
    EXPECT_EQ(s2.width, 10);
    EXPECT_EQ(s2.height, 20);
}

TEST(test_size2d, test_size2d_clamp)
{
    const math::size2d min{5, 10};
    const math::size2d max{50, 100};

    EXPECT_EQ(math::clamp(math::size2d{10, 20}, min, max), (math::size2d{10, 20}));
    EXPECT_EQ(math::clamp(math::size2d{40, 90}, min, max), (math::size2d{40, 90}));
    EXPECT_EQ(math::clamp(math::size2d{4, 20}, min, max), (math::size2d{5, 20}));
    EXPECT_EQ(math::clamp(math::size2d{5, 9}, min, max), (math::size2d{5, 10}));
    EXPECT_EQ(math::clamp(math::size2d{51, 90}, min, max), (math::size2d{50, 90}));
    EXPECT_EQ(math::clamp(math::size2d{50, 110}, min, max), (math::size2d{50, 100}));
}
