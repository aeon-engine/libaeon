// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/line_segment2d.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_line_segment2d, test_line_segment2d_size)
{
    math::line_segment2d segment{math::vector2{10, 10}, math::vector2{100, 100}};
    EXPECT_EQ((math::size(segment)), (math::vector2{90, 90}));
}

TEST(test_line_segment2d, test_line_segment2d_middle)
{
    math::line_segment2d segment{math::vector2{10, 10}, math::vector2{20, 20}};
    EXPECT_EQ((math::middle(segment)), (math::vector2{15, 15}));

    math::line_segment2d segment2{math::vector2{10.0f, 10.0f}, math::vector2{20.0f, 20.0f}};
    EXPECT_EQ((math::middle(segment2)), (math::vector2{15.0f, 15.0f}));
}

TEST(test_line_segment2d, test_line_segment2d_round)
{
    math::line_segment2d segment{math::vector2{10.7f, 10.3f}, math::vector2{100.6f, 100.8f}};
    EXPECT_EQ((math::round(segment)),
              (math::line_segment2d{math::vector2{11.0f, 10.0f}, math::vector2{101.0f, 101.0f}}));
}