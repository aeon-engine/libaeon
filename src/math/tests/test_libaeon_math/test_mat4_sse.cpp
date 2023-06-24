// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/math/mat4.h>
#include <aeon/math/mat4_stream.h>
#include <aeon/math/math.h>
#include <gtest/gtest.h>

using namespace aeon;

#if (!defined(AEON_DISABLE_SSE))

TEST(test_mat4_sse, test_mat4_sse_multiply)
{
    // clang-format off
    const math::mat4 mat1
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    // clang-format off
    const math::mat4 mat2
    {
        17.0f, 18.0f, 19.0f, 20.0f,
        21.0f, 22.0f, 23.0f, 24.0f,
        25.0f, 26.0f, 27.0f, 28.0f,
        29.0f, 30.0f, 31.0f, 32.0f
    };
    // clang-format on

    const auto result1 = math::detail::mat4_mul(mat1, mat2);
    const auto result2 = math::detail::mat4_mul_sse(mat1, mat2);

    EXPECT_EQ(result1, result2);
}

#endif
