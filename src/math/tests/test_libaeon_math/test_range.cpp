// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/range.h>
#include <aeon/math/range_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_range, test_range_default_int)
{
    const math::range<int> range;
    EXPECT_EQ(math::begin(range), 0);
    EXPECT_EQ(math::end(range), 0);
    EXPECT_EQ(math::size(range), 0);
}

TEST(test_range, test_range_default_float)
{
    const math::range<float> range;
    EXPECT_EQ(math::begin(range), 0.0f);
    EXPECT_EQ(math::end(range), 0.0f);
    EXPECT_EQ(math::size(range), 0.0f);
}

TEST(test_range, test_range_int)
{
    const math::range<int> range{10, 25};
    EXPECT_EQ(math::begin(range), 10);
    EXPECT_EQ(math::end(range), 25);
    EXPECT_EQ(math::size(range), 15);
}

TEST(test_range, test_range_equals)
{
    const math::range<int> range{10, 25};
    const math::range<int> range2{25, 10};
    const math::range<int> range3{10, 25};

    EXPECT_FALSE(range == range2);
    EXPECT_TRUE(range != range2);
    EXPECT_FALSE(range2 == range3);
    EXPECT_TRUE(range2 != range3);
    EXPECT_TRUE(range == range3);
    EXPECT_FALSE(range != range3);
}

TEST(test_range, test_range_equals2)
{
    const math::range<int> range{10, 25};
    const math::range<int> range2{25, 10};
    const math::range<int> range3{10, 25};

    EXPECT_NE(range, range2);
    EXPECT_NE(range2, range3);
    EXPECT_EQ(range, range3);
}

TEST(test_range, test_range_round)
{
    const math::range range{10.4f, 25.4f};
    const math::range range2{25.8f, 10.9f};

    EXPECT_EQ(math::round(range), (math::range{10.0f, 25.0f}));
    EXPECT_EQ(math::round(range2), (math::range{26.0f, 11.0f}));
}
