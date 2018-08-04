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
#include <aeon/math/mat3.h>
#include <aeon/math/mat3_stream.h>

using namespace aeon;

TEST(test_mat3, test_mat3_default)
{
    math::mat3 mat;
}

TEST(test_mat3, test_mat3_zero)
{
    const auto mat = math::mat3::zero();
}

TEST(test_mat3, test_mat3_identity)
{
    const auto mat = math::mat3::indentity();
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
