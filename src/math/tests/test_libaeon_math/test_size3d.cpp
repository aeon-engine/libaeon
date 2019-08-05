// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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
