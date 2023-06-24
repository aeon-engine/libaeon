// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/vector2.h>
#include <aeon/math/vector2_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_vector2, test_vector2_default_int)
{
    [[maybe_unused]] math::vector2<int> vec;
}

TEST(test_vector2, test_vector2_operators_add)
{
    const math::vector2 vec{5, 8};
    math::vector2 vec2{5, 8};

    const auto result = vec + vec2;
    vec2 += vec;

    EXPECT_EQ(result, vec2);
}

TEST(test_vector2, test_vector2_interpolate)
{
    const math::vector2 vec{5.0f, 20.0f};
    const math::vector2 vec2{10.0f, 40.0f};

    EXPECT_EQ(math::interpolate(vec, vec2, 0.0), vec);
    EXPECT_EQ(math::interpolate(vec, vec2, 1.0), vec2);
}
