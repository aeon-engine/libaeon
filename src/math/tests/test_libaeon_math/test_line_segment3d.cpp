// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/line_segment3d.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_line_segment3d, test_line_segment3d_size)
{
    math::line_segment3d segment{math::vector3{10, 10, 10}, math::vector3{100, 100, 100}};
    EXPECT_EQ((math::size(segment)), (math::vector3{90, 90, 90}));
}

TEST(test_line_segment3d, test_line_segment3d_middle)
{
    math::line_segment3d segment{math::vector3{10, 10, 10}, math::vector3{20, 20, 20}};
    EXPECT_EQ((math::middle(segment)), (math::vector3{15, 15, 15}));

    math::line_segment3d segment2{math::vector3{10.0f, 10.0f, 10.0f}, math::vector3{20.0f, 20.0f, 20.0f}};
    EXPECT_EQ((math::middle(segment2)), (math::vector3{15.0f, 15.0f, 15.0f}));
}

TEST(test_line_segment3d, test_line_segment3d_round)
{
    math::line_segment3d segment{math::vector3{10.7f, 10.3f, 10.8f}, math::vector3{100.6f, 100.8f, 100.1f}};
    EXPECT_EQ((math::round(segment)),
              (math::line_segment3d{math::vector3{11.0f, 10.0f, 11.0f}, math::vector3{101.0f, 101.0f, 100.0f}}));
}
