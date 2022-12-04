// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/quaternion.h>
#include <aeon/math/quaternion_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_quaternion, test_quaternion_default)
{
    [[maybe_unused]] math::quaternion quat;
}

TEST(test_quaternion, test_quaternion_equals)
{
    EXPECT_EQ((math::quaternion{}), (math::quaternion{}));
    EXPECT_EQ(math::quaternion::identity(), math::quaternion::identity());
    EXPECT_NE((math::quaternion{}), math::quaternion::identity());
}
