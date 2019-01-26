// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/math/math.h>

using namespace aeon;

TEST(test_math, test_math_float_sigmoid)
{
    for (auto val = -100.0f; val <= 100.0f; val += 0.01f)
    {
        ASSERT_LE(math::sigmoid(val), 1.0f);
        ASSERT_GE(math::sigmoid(val), 0.0f);
    }
}

TEST(test_math, test_math_double_sigmoid)
{
    for (auto val = -100.0; val <= 100.0; val += 0.01)
    {
        ASSERT_LE(math::sigmoid(val), 1.0);
        ASSERT_GE(math::sigmoid(val), 0.0);
    }
}

TEST(test_math, test_math_variadic_min)
{
    EXPECT_EQ(3, math::min(5, 4, 3));
    EXPECT_EQ(3, math::min(3, 4, 3));
    EXPECT_EQ(1, math::min(1, 2, 3, 4, 5));
    EXPECT_EQ(1, math::min(5, 4, 3, 2, 1));

    EXPECT_EQ(3.0f, math::min(5.0f, 4.0f, 3.0f));
    EXPECT_EQ(3.0f, math::min(3.0f, 4.0f, 3.0f));
    EXPECT_EQ(1.0f, math::min(1.0f, 2.0f, 3.0f, 4.0f, 5.0f));
    EXPECT_EQ(1.0f, math::min(5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
}

TEST(test_math, test_math_variadic_max)
{
    EXPECT_EQ(5, math::max(5, 4, 3));
    EXPECT_EQ(4, math::max(3, 4, 3));
    EXPECT_EQ(5, math::max(1, 2, 3, 4, 5));
    EXPECT_EQ(5, math::max(5, 4, 3, 2, 1));

    EXPECT_EQ(5.0f, math::max(5.0f, 4.0f, 3.0f));
    EXPECT_EQ(4.0f, math::max(3.0f, 4.0f, 3.0f));
    EXPECT_EQ(5.0f, math::max(1.0f, 2.0f, 3.0f, 4.0f, 5.0f));
    EXPECT_EQ(5.0f, math::max(5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
}

TEST(test_math, test_math_constexpr_pow_int)
{
    EXPECT_EQ(4, math::constexpr_pow(2, 2));
    EXPECT_EQ(4.0f, math::constexpr_pow(2.0f, 2));
    EXPECT_EQ(4.0, math::constexpr_pow(2.0, 2));

    EXPECT_EQ(8, math::constexpr_pow(2, 3));
    EXPECT_EQ(8.0f, math::constexpr_pow(2.0f, 3));
    EXPECT_EQ(8.0, math::constexpr_pow(2.0, 3));

    EXPECT_EQ(16, math::constexpr_pow(2, 4));
    EXPECT_EQ(16.0f, math::constexpr_pow(2.0f, 4));
    EXPECT_EQ(16.0, math::constexpr_pow(2.0, 4));
}
