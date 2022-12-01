// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/size3d.h>
#include <aeon/math/size3d_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_size3d, test_size3d_default_int)
{
    [[maybe_unused]] math::size3d<int> size;
}

TEST(test_size3d, test_size3d_clamp)
{
    const math::size3d min{5, 10, 20};
    const math::size3d max{50, 100, 200};

    EXPECT_EQ(math::clamp(math::size3d{10, 20, 30}, min, max), (math::size3d{10, 20, 30}));
    EXPECT_EQ(math::clamp(math::size3d{40, 90, 190}, min, max), (math::size3d{40, 90, 190}));
    EXPECT_EQ(math::clamp(math::size3d{4, 20, 19}, min, max), (math::size3d{5, 20, 20}));
    EXPECT_EQ(math::clamp(math::size3d{5, 9, 201}, min, max), (math::size3d{5, 10, 200}));
    EXPECT_EQ(math::clamp(math::size3d{51, 90, 300}, min, max), (math::size3d{50, 90, 200}));
    EXPECT_EQ(math::clamp(math::size3d{50, 110, 1}, min, max), (math::size3d{50, 100, 20}));
}

TEST(test_size3d, test_size3d_bit_ceil)
{
    math::size3d value1{5u, 10u, 20u};
    math::size3d value2{50u, 100u, 200u};
    math::size3d value3{64u, 128u, 256u};

    EXPECT_EQ((math::bit_ceiled(value1)), (math::size3d{8u, 16u, 32u}));
    EXPECT_EQ((math::bit_ceiled(value2)), (math::size3d{64u, 128u, 256u}));
    EXPECT_EQ((math::bit_ceiled(value3)), (math::size3d{64u, 128u, 256u}));

    math::bit_ceil(value1);
    math::bit_ceil(value2);
    math::bit_ceil(value3);

    EXPECT_EQ(value1, (math::size3d{8u, 16u, 32u}));
    EXPECT_EQ(value2, (math::size3d{64u, 128u, 256u}));
    EXPECT_EQ(value3, (math::size3d{64u, 128u, 256u}));
}

TEST(test_size3d, test_size3d_bit_floor)
{
    math::size3d value1{5u, 10u, 20u};
    math::size3d value2{50u, 100u, 200u};
    math::size3d value3{64u, 128u, 256u};

    EXPECT_EQ((math::bit_floored(value1)), (math::size3d{4u, 8u, 16u}));
    EXPECT_EQ((math::bit_floored(value2)), (math::size3d{32u, 64u, 128u}));
    EXPECT_EQ((math::bit_floored(value3)), (math::size3d{64u, 128u, 256u}));

    math::bit_floor(value1);
    math::bit_floor(value2);
    math::bit_floor(value3);

    EXPECT_EQ(value1, (math::size3d{4u, 8u, 16u}));
    EXPECT_EQ(value2, (math::size3d{32u, 64u, 128u}));
    EXPECT_EQ(value3, (math::size3d{64u, 128u, 256u}));
}
