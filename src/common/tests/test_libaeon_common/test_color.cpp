// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/color.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_color, test_color_rgb_default_u8)
{
    const common::color_rgb_u color;
    EXPECT_EQ(0, color.r);
    EXPECT_EQ(0, color.g);
    EXPECT_EQ(0, color.b);
}

TEST(test_color, test_color_rgb_default_float)
{
    const common::color_rgb_f color;
    EXPECT_EQ(0.0f, color.r);
    EXPECT_EQ(0.0f, color.g);
    EXPECT_EQ(0.0f, color.b);
}

TEST(test_color, test_color_rgb_default_double)
{
    const common::color_rgb_d color;
    EXPECT_EQ(0.0, color.r);
    EXPECT_EQ(0.0, color.g);
    EXPECT_EQ(0.0, color.b);
}

TEST(test_color, test_color_rgba_default_u8)
{
    const common::color_rgba_u color;
    EXPECT_EQ(0, color.r);
    EXPECT_EQ(0, color.g);
    EXPECT_EQ(0, color.b);
    EXPECT_EQ(255, color.a);
}

TEST(test_color, test_color_rgba_default_float)
{
    const common::color_rgba_f color;
    EXPECT_EQ(0.0f, color.r);
    EXPECT_EQ(0.0f, color.g);
    EXPECT_EQ(0.0f, color.b);
    EXPECT_EQ(1.0f, color.a);
}

TEST(test_color, test_color_rgba_default_double)
{
    const common::color_rgba_d color;
    EXPECT_EQ(0.0, color.r);
    EXPECT_EQ(0.0, color.g);
    EXPECT_EQ(0.0, color.b);
    EXPECT_EQ(1.0, color.a);
}

TEST(test_color, test_color_rgba_from_rgb_u8)
{
    const common::color_rgb_u color_rgb{10, 20, 30};
    const common::color_rgba_u color{color_rgb, 40};
    EXPECT_EQ(10, color.r);
    EXPECT_EQ(20, color.g);
    EXPECT_EQ(30, color.b);
    EXPECT_EQ(40, color.a);
}

TEST(test_color, test_color_rgba_from_rgb_float)
{
    const common::color_rgb_f color_rgb{10.0f, 20.0f, 30.0f};
    const common::color_rgba_f color{color_rgb, 40.0f};
    EXPECT_EQ(10.0f, color.r);
    EXPECT_EQ(20.0f, color.g);
    EXPECT_EQ(30.0f, color.b);
    EXPECT_EQ(40.0f, color.a);
}

TEST(test_color, test_color_rgba_from_rgb_double)
{
    const common::color_rgb_d color_rgb{10.0, 20.0, 30.0};
    const common::color_rgba_d color{color_rgb, 40.0};
    EXPECT_EQ(10.0, color.r);
    EXPECT_EQ(20.0, color.g);
    EXPECT_EQ(30.0, color.b);
    EXPECT_EQ(40.0, color.a);
}

TEST(test_color, test_color_rgba_double_from_rgba_u8)
{
    const common::color_rgba_u color{128, 255, 64, 32};
    const common::color_rgba_d color_dbl{color};
    EXPECT_NEAR(0.5, color_dbl.r, 0.005);
    EXPECT_NEAR(1.0, color_dbl.g, 0.005);
    EXPECT_NEAR(0.25, color_dbl.b, 0.005);
    EXPECT_NEAR(0.125, color_dbl.a, 0.005);

    const common::color_rgba_u color_u8{color_dbl};
    EXPECT_EQ(color, color_u8);
}
