// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/math/mat3.h>
#include <aeon/math/mat3_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat3, test_mat3_default)
{
    [[maybe_unused]] math::mat3 mat;
}

TEST(test_mat3, test_mat3_zero)
{
    [[maybe_unused]] const auto mat = math::mat3::zero();
}

TEST(test_mat3, test_mat3_identity)
{
    [[maybe_unused]] const auto mat = math::mat3::indentity();
}

TEST(test_mat3, test_mat3_equals)
{
    EXPECT_EQ(math::mat3::indentity(), math::mat3::indentity());
    EXPECT_NE((math::mat3{}), math::mat3::indentity());
}

TEST(test_mat3, test_mat3_multiply_identity)
{
    const auto mat = math::mat3::indentity();
    const auto mat2 = mat * math::mat3::indentity();
    const auto mat3 = math::mat3::indentity() * mat2;
    EXPECT_EQ(mat2, math::mat3::indentity());
    EXPECT_EQ(mat3, math::mat3::indentity());
}

TEST(test_mat3, test_mat3_multiply_rotation_with_identity)
{
    const auto mat = math::mat3::rotate(45.0f);
    const auto mat2 = mat * math::mat3::indentity();
    const auto mat3 = math::mat3::indentity() * mat2;
    EXPECT_EQ(mat2, mat);
    EXPECT_EQ(mat3, mat);
}

TEST(test_mat3, test_mat3_at)
{
    // clang-format off
    math::mat3 mat
    {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    // clang-format on

    EXPECT_EQ(mat[0][0], mat.at(0, 0));
    EXPECT_EQ(mat[0][1], mat.at(0, 1));
    EXPECT_EQ(mat[0][2], mat.at(0, 2));

    EXPECT_EQ(mat[1][0], mat.at(1, 0));
    EXPECT_EQ(mat[1][1], mat.at(1, 1));
    EXPECT_EQ(mat[1][2], mat.at(1, 2));

    EXPECT_EQ(mat[2][0], mat.at(2, 0));
    EXPECT_EQ(mat[2][1], mat.at(2, 1));
    EXPECT_EQ(mat[2][2], mat.at(2, 2));
}

TEST(test_mat3, test_mat3_determinant)
{
    EXPECT_EQ(1, math::determinant(math::mat3::indentity()));

    const auto mat = math::mat3::scale(2);
    EXPECT_EQ(4, math::determinant(mat));

    const auto mat2 = math::mat3::scale(3);
    EXPECT_EQ(9, math::determinant(mat2));
}
