// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/math/mat_view.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat_view, test_mat_view_default)
{
    math::mat_view<float> mat;
    EXPECT_TRUE(math::null(mat));
    EXPECT_FALSE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 0);
    EXPECT_EQ(math::height(mat), 0);
    EXPECT_EQ(math::stride(mat), 0);
}

TEST(test_mat_view, test_mat_view_from_mat3)
{
    auto mat3 = math::mat3::indentity();
    const auto mat = math::make_view(mat3);

    EXPECT_FALSE(math::null(mat));
    EXPECT_TRUE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 3);
    EXPECT_EQ(math::height(mat), 3);
    EXPECT_EQ(math::stride(mat), aeon_signed_sizeof(float) * 3);
}

TEST(test_mat_view, test_mat_view_from_const_mat3)
{
    const auto mat3 = math::mat3::indentity();
    const auto mat = math::make_view(mat3);

    EXPECT_FALSE(math::null(mat));
    EXPECT_TRUE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 3);
    EXPECT_EQ(math::height(mat), 3);
    EXPECT_EQ(math::stride(mat), aeon_signed_sizeof(float) * 3);
}

TEST(test_mat_view, test_mat_view_from_mat4)
{
    auto mat4 = math::mat4::indentity();
    const auto mat = math::make_view(mat4);

    EXPECT_FALSE(math::null(mat));
    EXPECT_TRUE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 4);
    EXPECT_EQ(math::height(mat), 4);
    EXPECT_EQ(math::stride(mat), aeon_signed_sizeof(float) * 4);
}

TEST(test_mat_view, test_mat_view_from_const_mat4)
{
    const auto mat4 = math::mat4::indentity();
    const auto mat = math::make_view(mat4);

    EXPECT_FALSE(math::null(mat));
    EXPECT_TRUE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 4);
    EXPECT_EQ(math::height(mat), 4);
    EXPECT_EQ(math::stride(mat), aeon_signed_sizeof(float) * 4);
}

TEST(test_mat_view, test_mat_row_column_order)
{
    // clang-format off
    math::mat4 mat4
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    const auto mat = math::make_view(mat4);

    // Mat4 is column order, a mat_view is row order
    EXPECT_EQ(mat.at(0, 0), mat4.at(0, 0));
    EXPECT_EQ(mat.at(1, 0), mat4.at(0, 1));
    EXPECT_EQ(mat.at(2, 0), mat4.at(0, 2));
    EXPECT_EQ(mat.at(3, 0), mat4.at(0, 3));
    EXPECT_EQ(mat.at(0, 1), mat4.at(1, 0));
    EXPECT_EQ(mat.at(1, 1), mat4.at(1, 1));
    EXPECT_EQ(mat.at(2, 1), mat4.at(1, 2));
    EXPECT_EQ(mat.at(3, 1), mat4.at(1, 3));
    EXPECT_EQ(mat.at(0, 2), mat4.at(2, 0));
    EXPECT_EQ(mat.at(1, 2), mat4.at(2, 1));
    EXPECT_EQ(mat.at(2, 2), mat4.at(2, 2));
    EXPECT_EQ(mat.at(3, 2), mat4.at(2, 3));
    EXPECT_EQ(mat.at(0, 3), mat4.at(3, 0));
    EXPECT_EQ(mat.at(1, 3), mat4.at(3, 1));
    EXPECT_EQ(mat.at(2, 3), mat4.at(3, 2));
    EXPECT_EQ(mat.at(3, 3), mat4.at(3, 3));
}

TEST(test_mat_view, test_mat_row_column_order_const)
{
    // clang-format off
    const math::mat4 mat4
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    const auto mat = math::make_view(mat4);

    // Mat4 is column order, a mat_view is row order
    EXPECT_EQ(mat.at(0, 0), mat4.at(0, 0));
    EXPECT_EQ(mat.at(1, 0), mat4.at(0, 1));
    EXPECT_EQ(mat.at(2, 0), mat4.at(0, 2));
    EXPECT_EQ(mat.at(3, 0), mat4.at(0, 3));
    EXPECT_EQ(mat.at(0, 1), mat4.at(1, 0));
    EXPECT_EQ(mat.at(1, 1), mat4.at(1, 1));
    EXPECT_EQ(mat.at(2, 1), mat4.at(1, 2));
    EXPECT_EQ(mat.at(3, 1), mat4.at(1, 3));
    EXPECT_EQ(mat.at(0, 2), mat4.at(2, 0));
    EXPECT_EQ(mat.at(1, 2), mat4.at(2, 1));
    EXPECT_EQ(mat.at(2, 2), mat4.at(2, 2));
    EXPECT_EQ(mat.at(3, 2), mat4.at(2, 3));
    EXPECT_EQ(mat.at(0, 3), mat4.at(3, 0));
    EXPECT_EQ(mat.at(1, 3), mat4.at(3, 1));
    EXPECT_EQ(mat.at(2, 3), mat4.at(3, 2));
    EXPECT_EQ(mat.at(3, 3), mat4.at(3, 3));
}

TEST(test_mat_view, test_make_view)
{
    // clang-format off
    const math::mat4 mat4
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    const auto mat = math::make_view(mat4);
    const auto sub_mat = math::make_view(mat, math::rectangle<int>{1, 1, 3, 3});

    EXPECT_EQ(math::width(sub_mat), 2);
    EXPECT_EQ(math::height(sub_mat), 2);

    // Mat4 is column order, a mat_view is row order
    EXPECT_EQ(sub_mat.at(0, 0), mat4.at(1, 1));
    EXPECT_EQ(sub_mat.at(0, 1), mat4.at(2, 1));
    EXPECT_EQ(sub_mat.at(1, 0), mat4.at(1, 2));
    EXPECT_EQ(sub_mat.at(1, 1), mat4.at(2, 2));
}

TEST(test_mat_view, test_equals)
{
    // clang-format off
    const math::mat4 mat4
    {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.0f,  6.0f,  7.0f,  8.0f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    // clang-format on

    const auto mat = math::make_view(mat4);
    const auto mat2 = math::make_view(mat4);

    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat != mat2);
}

TEST(test_mat_view, test_equals2)
{
    // clang-format off
    const math::mat4 mat4
    {
        1.0f,     2.0f,  10.0f, 30.0f,
        3.0f,     4.0f,  20.0f, 40.0f,
        100.0f, 300.0f,   1.0f,  2.0f,
        200.0f, 400.0f,   3.0f,  4.0f
    };
    // clang-format on

    const auto mat = math::make_view(math::make_view(mat4), math::rectangle<int>{0, 0, 2, 2});
    const auto mat2 = math::make_view(math::make_view(mat4), math::rectangle<int>{2, 2, 4, 4});

    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat != mat2);
}

TEST(test_mat_view, test_add)
{
    // clang-format off
    math::mat3 mat3
    {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    // clang-format on

    auto mat = math::make_view(mat3);
    mat += 10.0f;

    EXPECT_EQ(11.0f, mat.at(0, 0));
    EXPECT_EQ(12.0f, mat.at(0, 1));
    EXPECT_EQ(13.0f, mat.at(0, 2));

    EXPECT_EQ(14.0f, mat.at(1, 0));
    EXPECT_EQ(15.0f, mat.at(1, 1));
    EXPECT_EQ(16.0f, mat.at(1, 2));

    EXPECT_EQ(17.0f, mat.at(2, 0));
    EXPECT_EQ(18.0f, mat.at(2, 1));
    EXPECT_EQ(19.0f, mat.at(2, 2));
}

TEST(test_mat_view, test_subtract)
{
    // clang-format off
    math::mat3 mat3
    {
        10.0f, 20.0f, 30.0f,
        40.0f, 50.0f, 60.0f,
        70.0f, 80.0f, 90.0f
    };
    // clang-format on

    auto mat = math::make_view(mat3);
    mat -= 10.0f;

    EXPECT_EQ(0.0f, mat.at(0, 0));
    EXPECT_EQ(10.0f, mat.at(0, 1));
    EXPECT_EQ(20.0f, mat.at(0, 2));

    EXPECT_EQ(30.0f, mat.at(1, 0));
    EXPECT_EQ(40.0f, mat.at(1, 1));
    EXPECT_EQ(50.0f, mat.at(1, 2));

    EXPECT_EQ(60.0f, mat.at(2, 0));
    EXPECT_EQ(70.0f, mat.at(2, 1));
    EXPECT_EQ(80.0f, mat.at(2, 2));
}