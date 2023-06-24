// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/vector3.h>
#include <aeon/math/vector3_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_vector3, test_vector3_default_int)
{
    [[maybe_unused]] math::vector3<int> vec;
}

TEST(test_vector3, test_vector3_interpolate)
{
    const math::vector3 vec{5.0f, 20.0f, 30.0f};
    const math::vector3 vec2{10.0f, 40.0f, 60.0f};

    EXPECT_EQ(math::interpolate(vec, vec2, 0.0), vec);
    EXPECT_EQ(math::interpolate(vec, vec2, 1.0), vec2);
}
