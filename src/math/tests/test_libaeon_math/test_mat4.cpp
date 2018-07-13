/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>
#include <aeon/math/mat4.h>
#include <aeon/math/math.h>

using namespace aeon;

TEST(test_mat4, test_mat4_default)
{
    math::mat4 mat;
}

TEST(test_mat4, test_mat4_zero)
{
    const auto mat = math::mat4::zero();
}

TEST(test_mat4, test_mat4_identity)
{
    const auto mat = math::mat4::indentity();
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

    EXPECT_EQ(mat.m00, mat.at(0, 0));
    EXPECT_EQ(mat.m01, mat.at(1, 0));
    EXPECT_EQ(mat.m02, mat.at(2, 0));
    EXPECT_EQ(mat.m03, mat.at(3, 0));

    EXPECT_EQ(mat.m10, mat.at(0, 1));
    EXPECT_EQ(mat.m11, mat.at(1, 1));
    EXPECT_EQ(mat.m12, mat.at(2, 1));
    EXPECT_EQ(mat.m13, mat.at(3, 1));

    EXPECT_EQ(mat.m20, mat.at(0, 2));
    EXPECT_EQ(mat.m21, mat.at(1, 2));
    EXPECT_EQ(mat.m22, mat.at(2, 2));
    EXPECT_EQ(mat.m23, mat.at(3, 2));

    EXPECT_EQ(mat.m30, mat.at(0, 3));
    EXPECT_EQ(mat.m31, mat.at(1, 3));
    EXPECT_EQ(mat.m32, mat.at(2, 3));
    EXPECT_EQ(mat.m33, mat.at(3, 3));
}

TEST(test_mat4, test_mat4_decompose)
{
    const auto expected_translation = math::vector3<float>{10.0f, 20.0f, 30.0f};

    auto matrix = math::mat4::indentity();
    matrix *= math::mat4::rotate(math::degree_to_radian(90.0f), {1.0f, 0.0f, 0.0f});
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
    const auto vec = mat * math::vector4<float>{};

    EXPECT_EQ(expected_vec, vec);
}

TEST(test_mat4, test_mat4_multiply_multiple_with_vector)
{
    const auto expected_vec = math::vector4<float>{20.0f, 40.0f, 80.0f, 1.0f};
    const auto expected_vec2 = math::vector4<float>{160.0f, 320.0f, 640.0f, 1.0f};
    auto mat = math::mat4::translate(expected_vec.x, expected_vec.y, expected_vec.z);
    mat *= math::mat4::translate(expected_vec2.x, expected_vec2.y, expected_vec2.z);

    const auto vec = mat * math::vector4<float>{};

    auto expected = expected_vec + expected_vec2;
    expected.w = 1.0f;

    EXPECT_EQ(expected, vec);
}
