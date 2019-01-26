// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size2d_stream.h>

using namespace aeon;

TEST(test_size2d, test_size2d_default_int)
{
    math::size2d<int> size;
}

struct external_size2d
{
    int width{};
    int height{};
};

TEST(test_size2d, test_size2d_convert_from_unknown)
{
    const external_size2d s{10, 20};

    math::size2d<int> size{math::convert_type{}, s};
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
