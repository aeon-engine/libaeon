// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/math/circle.h>
#include <aeon/math/circle_stream.h>
#include <gtest/gtest.h>

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

    math::set_position(c, 20, 30);
    EXPECT_EQ(math::radius(c), 10);
    EXPECT_EQ(math::position(c), (math::vector2{20, 30}));

    math::set_position(c, math::vector2{40, 50});
    EXPECT_EQ(math::radius(c), 10);
    EXPECT_EQ(math::position(c), (math::vector2{40, 50}));
}

TEST(test_circle, test_circle_to_rectangle)
{
    math::circle<int> c{5};
    EXPECT_EQ(math::rect(c), (math::rectangle<int>{-5, -5, 5, 5}));

    math::set_position(c, 10, 10);
    EXPECT_EQ(math::rect(c), (math::rectangle<int>{5, 5, 15, 15}));
}

TEST(test_circle, test_circle_overlaps_with_rectangle)
{
    EXPECT_TRUE(math::overlaps(math::circle{5.0f}, math::rectangle{0.0f, 0.0f, 5.0f, 5.0f}));
    EXPECT_TRUE(math::overlaps(math::circle{5.0f}, math::rectangle{4.99999f, -5.0f, 10.0f, 5.0f}));
    EXPECT_FALSE(math::overlaps(math::circle{5.0f}, math::rectangle{6.0f, -5.0f, 10.0f, 5.0f}));
}
