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
#include <aeon/math/range.h>
#include <aeon/math/range_stream.h>

using namespace aeon;

TEST(test_range, test_range_default_int)
{
    const math::range<int> range;
    EXPECT_EQ(math::begin(range), 0);
    EXPECT_EQ(math::end(range), 0);
    EXPECT_EQ(math::size(range), 0);
}

TEST(test_range, test_range_default_float)
{
    const math::range<float> range;
    EXPECT_EQ(math::begin(range), 0.0f);
    EXPECT_EQ(math::end(range), 0.0f);
    EXPECT_EQ(math::size(range), 0.0f);
}

TEST(test_range, test_range_int)
{
    const math::range<int> range{10, 25};
    EXPECT_EQ(math::begin(range), 10);
    EXPECT_EQ(math::end(range), 25);
    EXPECT_EQ(math::size(range), 15);
}

TEST(test_range, test_range_equals)
{
    const math::range<int> range{10, 25};
    const math::range<int> range2{25, 10};
    const math::range<int> range3{10, 25};

    EXPECT_FALSE(range == range2);
    EXPECT_TRUE(range != range2);
    EXPECT_FALSE(range2 == range3);
    EXPECT_TRUE(range2 != range3);
    EXPECT_TRUE(range == range3);
    EXPECT_FALSE(range != range3);
}

TEST(test_range, test_range_equals2)
{
    const math::range<int> range{10, 25};
    const math::range<int> range2{25, 10};
    const math::range<int> range3{10, 25};

    EXPECT_NE(range, range2);
    EXPECT_NE(range2, range3);
    EXPECT_EQ(range, range3);
}
