// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/swizzle_vector.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_swizzle, test_swizzle_single_vector2)
{
    math::vector2 vec{10, 20};

    EXPECT_EQ(10, (math::swizzle<math::swizzle_x>(vec)));
    EXPECT_EQ(10, (math::swizzle<math::swizzle_r>(vec)));

    EXPECT_EQ(20, (math::swizzle<math::swizzle_y>(vec)));
    EXPECT_EQ(20, (math::swizzle<math::swizzle_g>(vec)));
}

TEST(test_swizzle, test_swizzle_single_change_vector2)
{
    math::vector2 vec{10, 20};

    EXPECT_EQ(1, (math::swizzle<math::swizzle_one>(vec)));
    EXPECT_EQ(0, (math::swizzle<math::swizzle_zero>(vec)));
    EXPECT_EQ(-1, (math::swizzle<math::swizzle_minus_one>(vec)));
}

TEST(test_swizzle, test_swizzle_single_vector3)
{
    math::vector3 vec{10, 20, 30};

    EXPECT_EQ(10, (math::swizzle<math::swizzle_x>(vec)));
    EXPECT_EQ(10, (math::swizzle<math::swizzle_r>(vec)));

    EXPECT_EQ(20, (math::swizzle<math::swizzle_y>(vec)));
    EXPECT_EQ(20, (math::swizzle<math::swizzle_g>(vec)));

    EXPECT_EQ(30, (math::swizzle<math::swizzle_z>(vec)));
    EXPECT_EQ(30, (math::swizzle<math::swizzle_b>(vec)));
}

TEST(test_swizzle, test_swizzle_single_change_vector3)
{
    math::vector3 vec{10, 20, 30};

    EXPECT_EQ(1, (math::swizzle<math::swizzle_one>(vec)));
    EXPECT_EQ(0, (math::swizzle<math::swizzle_zero>(vec)));
    EXPECT_EQ(-1, (math::swizzle<math::swizzle_minus_one>(vec)));
}

TEST(test_swizzle, test_swizzle_single_vector4)
{
    math::vector4 vec{10, 20, 30, 40};

    EXPECT_EQ(10, (math::swizzle<math::swizzle_x>(vec)));
    EXPECT_EQ(10, (math::swizzle<math::swizzle_r>(vec)));

    EXPECT_EQ(20, (math::swizzle<math::swizzle_y>(vec)));
    EXPECT_EQ(20, (math::swizzle<math::swizzle_g>(vec)));

    EXPECT_EQ(30, (math::swizzle<math::swizzle_z>(vec)));
    EXPECT_EQ(30, (math::swizzle<math::swizzle_b>(vec)));

    EXPECT_EQ(40, (math::swizzle<math::swizzle_w>(vec)));
    EXPECT_EQ(40, (math::swizzle<math::swizzle_a>(vec)));
}

TEST(test_swizzle, test_swizzle_single_change_vector4)
{
    math::vector4 vec{10, 20, 30, 40};

    EXPECT_EQ(1, (math::swizzle<math::swizzle_one>(vec)));
    EXPECT_EQ(0, (math::swizzle<math::swizzle_zero>(vec)));
    EXPECT_EQ(-1, (math::swizzle<math::swizzle_minus_one>(vec)));
}

TEST(test_swizzle, test_swizzle_vector2)
{
    math::vector2 vec{10, 20};

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_x, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_y, math::swizzle_x>(vec)));

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_r, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_g, math::swizzle_r>(vec)));

    EXPECT_EQ((math::vector2{10, 1}), (math::swizzle<math::swizzle_r, math::swizzle_one>(vec)));
    EXPECT_EQ((math::vector2{0, 10}), (math::swizzle<math::swizzle_zero, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{-1, 10}), (math::swizzle<math::swizzle_minus_one, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{10, -1}), (math::swizzle<math::swizzle_r, math::swizzle_minus_one>(vec)));
}

TEST(test_swizzle, test_swizzle_vector3_to_vector2)
{
    math::vector3 vec{10, 20, 30};

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_x, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{20, 30}), (math::swizzle<math::swizzle_y, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector2{10, 30}), (math::swizzle<math::swizzle_x, math::swizzle_z>(vec)));

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_r, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{20, 30}), (math::swizzle<math::swizzle_g, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector2{10, 30}), (math::swizzle<math::swizzle_r, math::swizzle_b>(vec)));

    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_y, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector2{30, 20}), (math::swizzle<math::swizzle_z, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{30, 10}), (math::swizzle<math::swizzle_z, math::swizzle_x>(vec)));

    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_g, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{30, 20}), (math::swizzle<math::swizzle_b, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{30, 10}), (math::swizzle<math::swizzle_b, math::swizzle_r>(vec)));

    EXPECT_EQ((math::vector2{10, 10}), (math::swizzle<math::swizzle_x, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector2{20, 20}), (math::swizzle<math::swizzle_y, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{30, 30}), (math::swizzle<math::swizzle_z, math::swizzle_z>(vec)));

    EXPECT_EQ((math::vector2{10, 10}), (math::swizzle<math::swizzle_r, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{20, 20}), (math::swizzle<math::swizzle_g, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{30, 30}), (math::swizzle<math::swizzle_b, math::swizzle_b>(vec)));

    EXPECT_EQ((math::vector2{10, 1}), (math::swizzle<math::swizzle_r, math::swizzle_one>(vec)));
    EXPECT_EQ((math::vector2{-1, 20}), (math::swizzle<math::swizzle_minus_one, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{0, 30}), (math::swizzle<math::swizzle_zero, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector2{10, 0}), (math::swizzle<math::swizzle_r, math::swizzle_zero>(vec)));
}

TEST(test_swizzle, test_swizzle_vector3)
{
    math::vector3 vec{10, 20, 30};

    EXPECT_EQ((math::vector3{10, 20, 30}), (math::swizzle<math::swizzle_x, math::swizzle_y, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector3{20, 30, 10}), (math::swizzle<math::swizzle_y, math::swizzle_z, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector3{10, 30, 20}), (math::swizzle<math::swizzle_x, math::swizzle_z, math::swizzle_y>(vec)));

    EXPECT_EQ((math::vector3{10, 20, 30}), (math::swizzle<math::swizzle_r, math::swizzle_g, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector3{20, 30, 10}), (math::swizzle<math::swizzle_g, math::swizzle_b, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector3{10, 30, 20}), (math::swizzle<math::swizzle_r, math::swizzle_b, math::swizzle_g>(vec)));

    EXPECT_EQ((math::vector3{10, 1, 30}), (math::swizzle<math::swizzle_r, math::swizzle_one, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector3{0, 30, -1}),
              (math::swizzle<math::swizzle_zero, math::swizzle_b, math::swizzle_minus_one>(vec)));
    EXPECT_EQ((math::vector3{1, 1, 20}), (math::swizzle<math::swizzle_one, math::swizzle_one, math::swizzle_g>(vec)));
}

TEST(test_swizzle, test_swizzle_vector4_to_vector2)
{
    math::vector4 vec{10, 20, 30, 40};

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_x, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{20, 30}), (math::swizzle<math::swizzle_y, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector2{10, 30}), (math::swizzle<math::swizzle_x, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector2{10, 40}), (math::swizzle<math::swizzle_x, math::swizzle_w>(vec)));

    EXPECT_EQ((math::vector2{10, 20}), (math::swizzle<math::swizzle_r, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{20, 30}), (math::swizzle<math::swizzle_g, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector2{10, 30}), (math::swizzle<math::swizzle_r, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector2{10, 40}), (math::swizzle<math::swizzle_r, math::swizzle_a>(vec)));

    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_y, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector2{30, 20}), (math::swizzle<math::swizzle_z, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{30, 10}), (math::swizzle<math::swizzle_z, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector2{30, 40}), (math::swizzle<math::swizzle_z, math::swizzle_w>(vec)));

    EXPECT_EQ((math::vector2{20, 10}), (math::swizzle<math::swizzle_g, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{30, 20}), (math::swizzle<math::swizzle_b, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{30, 10}), (math::swizzle<math::swizzle_b, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{30, 40}), (math::swizzle<math::swizzle_b, math::swizzle_a>(vec)));

    EXPECT_EQ((math::vector2{10, 10}), (math::swizzle<math::swizzle_x, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector2{20, 20}), (math::swizzle<math::swizzle_y, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector2{30, 30}), (math::swizzle<math::swizzle_z, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector2{40, 40}), (math::swizzle<math::swizzle_w, math::swizzle_w>(vec)));

    EXPECT_EQ((math::vector2{10, 10}), (math::swizzle<math::swizzle_r, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector2{20, 20}), (math::swizzle<math::swizzle_g, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector2{30, 30}), (math::swizzle<math::swizzle_b, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector2{40, 40}), (math::swizzle<math::swizzle_a, math::swizzle_a>(vec)));
}

TEST(test_swizzle, test_swizzle_vector4_to_vector3)
{
    math::vector4 vec{10, 20, 30, 40};

    EXPECT_EQ((math::vector3{10, 20, 30}), (math::swizzle<math::swizzle_x, math::swizzle_y, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector3{20, 30, 40}), (math::swizzle<math::swizzle_y, math::swizzle_z, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector3{10, 30, 40}), (math::swizzle<math::swizzle_x, math::swizzle_z, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector3{10, 40, 30}), (math::swizzle<math::swizzle_x, math::swizzle_w, math::swizzle_z>(vec)));

    EXPECT_EQ((math::vector3{10, 20, 30}), (math::swizzle<math::swizzle_r, math::swizzle_g, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector3{20, 30, 40}), (math::swizzle<math::swizzle_g, math::swizzle_b, math::swizzle_a>(vec)));
    EXPECT_EQ((math::vector3{10, 30, 40}), (math::swizzle<math::swizzle_r, math::swizzle_b, math::swizzle_a>(vec)));
    EXPECT_EQ((math::vector3{10, 40, 30}), (math::swizzle<math::swizzle_r, math::swizzle_a, math::swizzle_b>(vec)));

    EXPECT_EQ((math::vector3{20, 10, 30}), (math::swizzle<math::swizzle_y, math::swizzle_x, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector3{30, 20, 40}), (math::swizzle<math::swizzle_z, math::swizzle_y, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector3{30, 10, 40}), (math::swizzle<math::swizzle_z, math::swizzle_x, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector3{30, 40, 20}), (math::swizzle<math::swizzle_z, math::swizzle_w, math::swizzle_y>(vec)));

    EXPECT_EQ((math::vector3{20, 10, 30}), (math::swizzle<math::swizzle_g, math::swizzle_r, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector3{30, 20, 40}), (math::swizzle<math::swizzle_b, math::swizzle_g, math::swizzle_a>(vec)));
    EXPECT_EQ((math::vector3{30, 10, 40}), (math::swizzle<math::swizzle_b, math::swizzle_r, math::swizzle_a>(vec)));
    EXPECT_EQ((math::vector3{30, 40, 20}), (math::swizzle<math::swizzle_b, math::swizzle_a, math::swizzle_g>(vec)));

    EXPECT_EQ((math::vector3{10, 10, 10}), (math::swizzle<math::swizzle_x, math::swizzle_x, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector3{20, 20, 20}), (math::swizzle<math::swizzle_y, math::swizzle_y, math::swizzle_y>(vec)));
    EXPECT_EQ((math::vector3{30, 30, 30}), (math::swizzle<math::swizzle_z, math::swizzle_z, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector3{40, 40, 40}), (math::swizzle<math::swizzle_w, math::swizzle_w, math::swizzle_w>(vec)));

    EXPECT_EQ((math::vector3{10, 10, 10}), (math::swizzle<math::swizzle_r, math::swizzle_r, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector3{20, 20, 20}), (math::swizzle<math::swizzle_g, math::swizzle_g, math::swizzle_g>(vec)));
    EXPECT_EQ((math::vector3{30, 30, 30}), (math::swizzle<math::swizzle_b, math::swizzle_b, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector3{40, 40, 40}), (math::swizzle<math::swizzle_a, math::swizzle_a, math::swizzle_a>(vec)));
}

TEST(test_swizzle, test_swizzle_vector4)
{
    math::vector4 vec{10, 20, 30, 40};

    EXPECT_EQ((math::vector4{10, 20, 30, 40}),
              (math::swizzle<math::swizzle_x, math::swizzle_y, math::swizzle_z, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector4{20, 30, 10, 40}),
              (math::swizzle<math::swizzle_y, math::swizzle_z, math::swizzle_x, math::swizzle_w>(vec)));
    EXPECT_EQ((math::vector4{10, 30, 20, 40}),
              (math::swizzle<math::swizzle_x, math::swizzle_z, math::swizzle_y, math::swizzle_w>(vec)));

    EXPECT_EQ((math::vector4{40, 10, 20, 30}),
              (math::swizzle<math::swizzle_w, math::swizzle_x, math::swizzle_y, math::swizzle_z>(vec)));
    EXPECT_EQ((math::vector4{40, 20, 30, 10}),
              (math::swizzle<math::swizzle_w, math::swizzle_y, math::swizzle_z, math::swizzle_x>(vec)));
    EXPECT_EQ((math::vector4{40, 10, 30, 20}),
              (math::swizzle<math::swizzle_w, math::swizzle_x, math::swizzle_z, math::swizzle_y>(vec)));

    EXPECT_EQ((math::vector4{40, 10, 20, 30}),
              (math::swizzle<math::swizzle_a, math::swizzle_r, math::swizzle_g, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector4{40, 20, 30, 10}),
              (math::swizzle<math::swizzle_a, math::swizzle_g, math::swizzle_b, math::swizzle_r>(vec)));
    EXPECT_EQ((math::vector4{40, 10, 30, 20}),
              (math::swizzle<math::swizzle_a, math::swizzle_r, math::swizzle_b, math::swizzle_g>(vec)));

    EXPECT_EQ((math::vector4{0, 10, 1, 30}),
              (math::swizzle<math::swizzle_zero, math::swizzle_r, math::swizzle_one, math::swizzle_b>(vec)));
    EXPECT_EQ((math::vector4{40, -1, 30, 1}),
              (math::swizzle<math::swizzle_a, math::swizzle_minus_one, math::swizzle_b, math::swizzle_one>(vec)));
    EXPECT_EQ((math::vector4{0, 10, 30, 0}),
              (math::swizzle<math::swizzle_zero, math::swizzle_r, math::swizzle_b, math::swizzle_zero>(vec)));
}
