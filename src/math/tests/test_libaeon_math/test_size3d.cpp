// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

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

TEST(test_size3d, test_size3d_interpolate)
{
    const math::size3d value1{50, 100, 200};
    const math::size3d value2{50u, 100u, 200u};
    const math::size3d value3{50.0f, 100.0f, 200.0f};
    const math::size3d value4{50.0, 100.0, 200.0};

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.0f)), (math::size3d{0, 0, 0}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.0f)), (math::size3d{0u, 0u, 0u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.0f)), (math::size3d{0.0f, 0.0f, 0.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.0f)), (math::size3d{0.0, 0.0, 0.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.25f)), (math::size3d{12, 25, 50}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.25f)), (math::size3d{12u, 25u, 50u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.25f)), (math::size3d{12.5f, 25.0f, 50.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.25f)), (math::size3d{12.5, 25.0, 50.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.5f)), (math::size3d{25, 50, 100}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.5f)), (math::size3d{25u, 50u, 100u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.5f)), (math::size3d{25.0f, 50.0f, 100.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.5f)), (math::size3d{25.0, 50.0, 100.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 1.0f)), value1);
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 1.0f)), value2);
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 1.0f)), value3);
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 1.0f)), value4);

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.0)), (math::size3d{0, 0, 0}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.0)), (math::size3d{0u, 0u, 0u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.0)), (math::size3d{0.0f, 0.0f, 0.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.0)), (math::size3d{0.0, 0.0, 0.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.25)), (math::size3d{12, 25, 50}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.25)), (math::size3d{12u, 25u, 50u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.25)), (math::size3d{12.5f, 25.0f, 50.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.25)), (math::size3d{12.5, 25.0, 50.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 0.5)), (math::size3d{25, 50, 100}));
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 0.5)), (math::size3d{25u, 50u, 100u}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 0.5)), (math::size3d{25.0f, 50.0f, 100.0f}));
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 0.5)), (math::size3d{25.0, 50.0, 100.0}));

    EXPECT_EQ((math::interpolate(math::size3d{0, 0, 0}, value1, 1.0)), value1);
    EXPECT_EQ((math::interpolate(math::size3d{0u, 0u, 0u}, value2, 1.0)), value2);
    EXPECT_EQ((math::interpolate(math::size3d{0.0f, 0.0f, 0.0f}, value3, 1.0)), value3);
    EXPECT_EQ((math::interpolate(math::size3d{0.0, 0.0, 0.0}, value4, 1.0)), value4);
}
