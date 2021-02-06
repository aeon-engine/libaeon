// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/math/mat.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat, test_mat_default)
{
    math::mat<float> mat;
    EXPECT_TRUE(math::null(mat));
    EXPECT_FALSE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 0);
    EXPECT_EQ(math::height(mat), 0);
    EXPECT_EQ(math::stride(mat), 0);
}

TEST(test_mat, test_add)
{
    // clang-format off
    math::mat3 mat3
    {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    // clang-format on

    const auto mat = static_cast<math::mat<float>>(math::make_view(mat3));

    EXPECT_EQ(1.0f, mat.at(0, 0));
    EXPECT_EQ(2.0f, mat.at(0, 1));
    EXPECT_EQ(3.0f, mat.at(0, 2));

    EXPECT_EQ(4.0f, mat.at(1, 0));
    EXPECT_EQ(5.0f, mat.at(1, 1));
    EXPECT_EQ(6.0f, mat.at(1, 2));

    EXPECT_EQ(7.0f, mat.at(2, 0));
    EXPECT_EQ(8.0f, mat.at(2, 1));
    EXPECT_EQ(9.0f, mat.at(2, 2));

    const auto mat_copy = mat + 10.0f;

    EXPECT_EQ(1.0f, mat.at(0, 0));
    EXPECT_EQ(2.0f, mat.at(0, 1));
    EXPECT_EQ(3.0f, mat.at(0, 2));

    EXPECT_EQ(4.0f, mat.at(1, 0));
    EXPECT_EQ(5.0f, mat.at(1, 1));
    EXPECT_EQ(6.0f, mat.at(1, 2));

    EXPECT_EQ(7.0f, mat.at(2, 0));
    EXPECT_EQ(8.0f, mat.at(2, 1));
    EXPECT_EQ(9.0f, mat.at(2, 2));

    EXPECT_EQ(11.0f, mat_copy.at(0, 0));
    EXPECT_EQ(12.0f, mat_copy.at(0, 1));
    EXPECT_EQ(13.0f, mat_copy.at(0, 2));

    EXPECT_EQ(14.0f, mat_copy.at(1, 0));
    EXPECT_EQ(15.0f, mat_copy.at(1, 1));
    EXPECT_EQ(16.0f, mat_copy.at(1, 2));

    EXPECT_EQ(17.0f, mat_copy.at(2, 0));
    EXPECT_EQ(18.0f, mat_copy.at(2, 1));
    EXPECT_EQ(19.0f, mat_copy.at(2, 2));
}
