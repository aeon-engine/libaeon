// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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
    EXPECT_EQ(math::quaternion::indentity(), math::quaternion::indentity());
    EXPECT_NE((math::quaternion{}), math::quaternion::indentity());
}
