// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/math/mat4.h>
#include <aeon/math/mat4_stream.h>
#include <aeon/math/math.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat4, test_mat4_default)
{
    [[maybe_unused]] math::mat4 mat;
}

TEST(test_mat4, test_mat4_zero)
{
    [[maybe_unused]] const auto mat = math::mat4::zero();
}

TEST(test_mat4, test_mat4_identity)
{
    [[maybe_unused]] const auto mat = math::mat4::indentity();
}

TEST(test_mat4, test_mat4_multiply_identity)
{
    const auto mat = math::mat4::indentity();
    const auto mat2 = mat * math::mat4::indentity();
    const auto mat3 = math::mat4::indentity() * mat2;
    EXPECT_EQ(mat2, math::mat4::indentity());
    EXPECT_EQ(mat3, math::mat4::indentity());
}

TEST(test_mat4, test_mat4_multiply_position_with_identity)
{
    const auto mat = math::mat4::translate(math::vector3<float>{400, 300, 0});
    const auto mat2 = mat * math::mat4::indentity();
    const auto mat3 = math::mat4::indentity() * mat2;
    EXPECT_EQ(mat2, mat);
    EXPECT_EQ(mat3, mat);
}

TEST(test_mat4, test_mat4_equals)
{
    EXPECT_EQ(math::mat4::indentity(), math::mat4::indentity());
    EXPECT_NE((math::mat4{}), math::mat4::indentity());
}

TEST(test_mat4, test_mat4_at)
{
    // clang-format off
    math::mat4 mat
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    EXPECT_EQ(mat[0][0], mat.at(0, 0));
    EXPECT_EQ(mat[0][1], mat.at(0, 1));
    EXPECT_EQ(mat[0][2], mat.at(0, 2));
    EXPECT_EQ(mat[0][3], mat.at(0, 3));
    EXPECT_EQ(mat[1][0], mat.at(1, 0));
    EXPECT_EQ(mat[1][1], mat.at(1, 1));
    EXPECT_EQ(mat[1][2], mat.at(1, 2));
    EXPECT_EQ(mat[1][3], mat.at(1, 3));
    EXPECT_EQ(mat[2][0], mat.at(2, 0));
    EXPECT_EQ(mat[2][1], mat.at(2, 1));
    EXPECT_EQ(mat[2][2], mat.at(2, 2));
    EXPECT_EQ(mat[2][3], mat.at(2, 3));
    EXPECT_EQ(mat[3][0], mat.at(3, 0));
    EXPECT_EQ(mat[3][1], mat.at(3, 1));
    EXPECT_EQ(mat[3][2], mat.at(3, 2));
    EXPECT_EQ(mat[3][3], mat.at(3, 3));
}

TEST(test_mat4, test_mat4_decompose)
{
    const auto expected_translation = math::vector3<float>{10.0f, 20.0f, 30.0f};

    auto matrix = math::mat4::indentity();
    matrix *= math::mat4::rotate(math::unitf<math::degree>{90.0f}, {1.0f, 0.0f, 0.0f});
    matrix *= math::mat4::translate(expected_translation);

    math::vector3<float> translation;
    math::vector3<float> scale;
    math::quaternion orientation;
    math::decompose(matrix, translation, scale, orientation);

    EXPECT_FLOAT_EQ(expected_translation.x, translation.x);
    EXPECT_FLOAT_EQ(expected_translation.y, translation.y);
    EXPECT_FLOAT_EQ(expected_translation.z, translation.z);
}

TEST(test_mat4, test_mat4_identity_quaternion)
{
    const auto mat = math::mat4{math::quaternion::indentity()};
    EXPECT_EQ(mat, math::mat4::indentity());
}

TEST(test_mat4, test_mat4_multiply_vector)
{
    const auto expected_vec = math::vector4<float>{10.0f, 20.0f, 30.0f, 1.0f};
    const auto mat = math::mat4::translate(expected_vec.x, expected_vec.y, expected_vec.z);
    const auto vec = mat * math::vector4<float>{0.0f, 0.0f, 0.0f, 1.0f};

    EXPECT_EQ(expected_vec, vec);
}

TEST(test_mat4, test_mat4_multiply_multiple_with_vector)
{
    const auto expected_vec = math::vector4<float>{20.0f, 40.0f, 80.0f, 1.0f};
    const auto expected_vec2 = math::vector4<float>{160.0f, 320.0f, 640.0f, 1.0f};
    auto mat = math::mat4::translate(expected_vec.x, expected_vec.y, expected_vec.z);
    mat *= math::mat4::translate(expected_vec2.x, expected_vec2.y, expected_vec2.z);

    const auto vec = mat * math::vector4<float>{0.0f, 0.0f, 0.0f, 1.0f};

    auto expected = expected_vec + expected_vec2;
    expected.w = 1.0f;

    EXPECT_EQ(expected, vec);
}

TEST(test_mat4, test_mat4_determinant)
{
    EXPECT_EQ(1, math::determinant(math::mat4::indentity()));

    const auto mat = math::mat4::scale(2);
    EXPECT_EQ(8, math::determinant(mat));

    const auto mat2 = math::mat4::scale(3);
    EXPECT_EQ(27, math::determinant(mat2));
}
