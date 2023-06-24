// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/vector4.h>
#include <aeon/math/vector4_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_vector4, test_vector4_default_int)
{
    [[maybe_unused]] math::vector4<int> vec;
}

TEST(test_vector4, test_vector4_interpolate)
{
    const math::vector4 vec{5.0f, 20.0f, 30.0f, 35.0f};
    const math::vector4 vec2{10.0f, 40.0f, 60.0f, 70.0f};

    EXPECT_EQ(math::interpolate(vec, vec2, 0.0), vec);
    EXPECT_EQ(math::interpolate(vec, vec2, 1.0), vec2);
}
