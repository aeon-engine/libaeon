// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/math/mat3.h>
#include <aeon/math/mat3_stream.h>
#include <aeon/math/math.h>

using namespace aeon;

#if (!defined(AEON_DISABLE_SSE))

TEST(test_mat3_sse, test_mat3_sse_multiply)
{
    // clang-format off
    const math::mat3 mat1
    {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    // clang-format on

    // clang-format off
    const math::mat3 mat2
    {
        10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f,
        16.0f, 17.0f, 18.0f
    };
    // clang-format on

    const auto result1 = math::detail::mat3_mul(mat1, mat2);
    const auto result2 = math::detail::mat3_mul_sse(mat1, mat2);

    EXPECT_EQ(result1, result2);
}

#endif
