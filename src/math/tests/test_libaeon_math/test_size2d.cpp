// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/size2d.h>
#include <aeon/math/size2d_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_size2d, test_size2d_default_int)
{
    [[maybe_unused]] math::size2d<int> size;
}

struct external_size2d
{
    int width{};
    int height{};
};

TEST(test_size2d, test_size2d_convert_from_unknown)
{
    const external_size2d s{10, 20};

    math::size2d<int> size{s};
    EXPECT_EQ(size.width, 10);
    EXPECT_EQ(size.height, 20);

    const auto s2 = size.convert_to<external_size2d>();
    EXPECT_EQ(s2.width, 10);
    EXPECT_EQ(s2.height, 20);
}

TEST(test_size2d, test_size2d_clamp)
{
    const math::size2d min{5, 10};
    const math::size2d max{50, 100};

    EXPECT_EQ(math::clamp(math::size2d{10, 20}, min, max), (math::size2d{10, 20}));
    EXPECT_EQ(math::clamp(math::size2d{40, 90}, min, max), (math::size2d{40, 90}));
    EXPECT_EQ(math::clamp(math::size2d{4, 20}, min, max), (math::size2d{5, 20}));
    EXPECT_EQ(math::clamp(math::size2d{5, 9}, min, max), (math::size2d{5, 10}));
    EXPECT_EQ(math::clamp(math::size2d{51, 90}, min, max), (math::size2d{50, 90}));
    EXPECT_EQ(math::clamp(math::size2d{50, 110}, min, max), (math::size2d{50, 100}));
}

TEST(test_size2d, test_size2d_bit_ceil)
{
    math::size2d value1{5u, 10u};
    math::size2d value2{50u, 100u};
    math::size2d value3{64u, 128u};

    EXPECT_EQ((math::bit_ceiled(value1)), (math::size2d{8u, 16u}));
    EXPECT_EQ((math::bit_ceiled(value2)), (math::size2d{64u, 128u}));
    EXPECT_EQ((math::bit_ceiled(value3)), (math::size2d{64u, 128u}));

    math::bit_ceil(value1);
    math::bit_ceil(value2);
    math::bit_ceil(value3);

    EXPECT_EQ(value1, (math::size2d{8u, 16u}));
    EXPECT_EQ(value2, (math::size2d{64u, 128u}));
    EXPECT_EQ(value3, (math::size2d{64u, 128u}));
}

TEST(test_size2d, test_size2d_bit_floor)
{
    math::size2d value1{5u, 10u};
    math::size2d value2{50u, 100u};
    math::size2d value3{64u, 128u};

    EXPECT_EQ((math::bit_floored(value1)), (math::size2d{4u, 8u}));
    EXPECT_EQ((math::bit_floored(value2)), (math::size2d{32u, 64u}));
    EXPECT_EQ((math::bit_floored(value3)), (math::size2d{64u, 128u}));

    math::bit_floor(value1);
    math::bit_floor(value2);
    math::bit_floor(value3);

    EXPECT_EQ(value1, (math::size2d{4u, 8u}));
    EXPECT_EQ(value2, (math::size2d{32u, 64u}));
    EXPECT_EQ(value3, (math::size2d{64u, 128u}));
}
