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
#include <aeon/types/circle.h>

using namespace aeon;

TEST(test_circle, test_circle_default_int)
{
    types::circle<int> c(10);
    EXPECT_EQ(types::position(c), (math::vector2{0, 0}));
    EXPECT_EQ(types::radius(c), 10);
}

TEST(test_circle, test_circle_default_float)
{
    types::circle<float> c(10.0f);
    EXPECT_EQ(types::position(c), (math::vector2{0.0f, 0.0f}));
    EXPECT_EQ(types::radius(c), 10.0f);
}

TEST(test_circle, test_circle_int_circumference)
{
    types::circle<int> c(5);
    EXPECT_EQ(types::diameter(c), 10);
    EXPECT_FLOAT_EQ(types::circumference(c), math::constants<float>::pi * 10.0f);
}

TEST(test_circle, test_circle_float_circumference)
{
    types::circle<float> c(5.0f);
    EXPECT_EQ(types::diameter(c), 10.0f);
    EXPECT_FLOAT_EQ(types::circumference(c), math::constants<float>::pi * 10.0f);
}

TEST(test_circle, test_circle_double_circumference)
{
    types::circle<double> c(5.0);
    EXPECT_EQ(types::diameter(c), 10.0);
    EXPECT_DOUBLE_EQ(types::circumference(c), math::constants<double>::pi * 10.0);
}

TEST(test_circle, test_circle_int_area)
{
    types::circle<int> c(10);
    EXPECT_FLOAT_EQ(types::area(c), 314.159265f);
}

TEST(test_circle, test_circle_float_area)
{
    types::circle<float> c(10.0f);
    EXPECT_FLOAT_EQ(types::area(c), 314.159265f);
}

TEST(test_circle, test_circle_double_area)
{
    types::circle<double> c(10.0);
    EXPECT_DOUBLE_EQ(types::area(c), 314.15926535897933);
}

TEST(test_circle, test_circle_set_position)
{
    types::circle<int> c(10);
    EXPECT_EQ(types::radius(c), 10);
    EXPECT_EQ(types::position(c), (math::vector2{0, 0}));

    c = types::set_position(c, 20, 30);
    EXPECT_EQ(types::radius(c), 10);
    EXPECT_EQ(types::position(c), (math::vector2{20, 30}));

    c = types::set_position(c, math::vector2{40, 50});
    EXPECT_EQ(types::radius(c), 10);
    EXPECT_EQ(types::position(c), (math::vector2{40, 50}));
}

TEST(test_circle, test_circle_to_rectangle)
{
    types::circle<int> c(5);
    EXPECT_EQ(types::rect(c), (types::rectangle<int>{-5, -5, 5, 5}));

    c = types::set_position(c, 10, 10);
    EXPECT_EQ(types::rect(c), (types::rectangle<int>{5, 5, 15, 15}));
}

TEST(test_circle, test_circle_overlaps_with_rectangle)
{
    EXPECT_TRUE(types::overlaps(types::circle{5.0f}, types::rectangle{0.0f, 0.0f, 5.0f, 5.0f}));
    EXPECT_TRUE(types::overlaps(types::circle{5.0f}, types::rectangle{4.99999f, -5.0f, 10.0f, 5.0f}));
    EXPECT_FALSE(types::overlaps(types::circle{5.0f}, types::rectangle{6.0f, -5.0f, 10.0f, 5.0f}));
}
