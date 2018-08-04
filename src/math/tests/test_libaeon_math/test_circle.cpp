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
#include <aeon/math/circle.h>
#include <aeon/math/circle_stream.h>

using namespace aeon;

TEST(test_circle, test_circle_default_int)
{
    math::circle<int> c{10};
    EXPECT_EQ(math::position(c), (math::vector2{0, 0}));
    EXPECT_EQ(math::radius(c), 10);
}

TEST(test_circle, test_circle_default_float)
{
    math::circle<float> c{10.0f};
    EXPECT_EQ(math::position(c), (math::vector2{0.0f, 0.0f}));
    EXPECT_EQ(math::radius(c), 10.0f);
}

TEST(test_circle, test_circle_equals)
{
    EXPECT_EQ((math::circle{10}), (math::circle{0, 0, 10}));
    EXPECT_EQ((math::circle{10, 20, 30}), (math::circle{10, 20, 30}));
    EXPECT_NE((math::circle{10, 20, 30}), (math::circle{30}));
}

TEST(test_circle, test_circle_int_circumference)
{
    math::circle<int> c{5};
    EXPECT_EQ(math::diameter(c), 10);
    EXPECT_FLOAT_EQ(math::circumference(c), math::constants<float>::pi * 10.0f);
}

TEST(test_circle, test_circle_float_circumference)
{
    math::circle<float> c{5.0f};
    EXPECT_EQ(math::diameter(c), 10.0f);
    EXPECT_FLOAT_EQ(math::circumference(c), math::constants<float>::pi * 10.0f);
}

TEST(test_circle, test_circle_double_circumference)
{
    math::circle<double> c{5.0};
    EXPECT_EQ(math::diameter(c), 10.0);
    EXPECT_DOUBLE_EQ(math::circumference(c), math::constants<double>::pi * 10.0);
}

TEST(test_circle, test_circle_int_area)
{
    math::circle<int> c{10};
    EXPECT_FLOAT_EQ(math::area(c), 314.159265f);
}

TEST(test_circle, test_circle_float_area)
{
    math::circle<float> c{10.0f};
    EXPECT_FLOAT_EQ(math::area(c), 314.159265f);
}

TEST(test_circle, test_circle_double_area)
{
    math::circle<double> c{10.0};
    EXPECT_DOUBLE_EQ(math::area(c), 314.15926535897933);
}

TEST(test_circle, test_circle_set_position)
{
    math::circle<int> c{10};
    EXPECT_EQ(math::radius(c), 10);
    EXPECT_EQ(math::position(c), (math::vector2{0, 0}));

    c = math::set_position(c, 20, 30);
    EXPECT_EQ(math::radius(c), 10);
    EXPECT_EQ(math::position(c), (math::vector2{20, 30}));

    c = math::set_position(c, math::vector2{40, 50});
    EXPECT_EQ(math::radius(c), 10);
    EXPECT_EQ(math::position(c), (math::vector2{40, 50}));
}

TEST(test_circle, test_circle_to_rectangle)
{
    math::circle<int> c{5};
    EXPECT_EQ(math::rect(c), (math::rectangle<int>{-5, -5, 5, 5}));

    c = math::set_position(c, 10, 10);
    EXPECT_EQ(math::rect(c), (math::rectangle<int>{5, 5, 15, 15}));
}

TEST(test_circle, test_circle_overlaps_with_rectangle)
{
    EXPECT_TRUE(math::overlaps(math::circle{5.0f}, math::rectangle{0.0f, 0.0f, 5.0f, 5.0f}));
    EXPECT_TRUE(math::overlaps(math::circle{5.0f}, math::rectangle{4.99999f, -5.0f, 10.0f, 5.0f}));
    EXPECT_FALSE(math::overlaps(math::circle{5.0f}, math::rectangle{6.0f, -5.0f, 10.0f, 5.0f}));
}
