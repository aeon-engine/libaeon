// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/math/mat_view.h>
#include <aeon/common/signed_sizeof.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat_view, test_mat_view_default)
{
    math::mat_view mat;
    EXPECT_TRUE(math::null(mat));
    EXPECT_FALSE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 0);
    EXPECT_EQ(math::height(mat), 0);
    EXPECT_EQ(math::stride(mat), 0);
}

TEST(test_mat_view, test_const_mat_view_default)
{
    const math::mat_view mat;
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
    EXPECT_EQ(math::stride(mat), sizeof(float) * 3);
    EXPECT_EQ(math::stride(mat), math::element_type(mat).size * 3);
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
    EXPECT_EQ(math::stride(mat), sizeof(float) * 4);
    EXPECT_EQ(math::stride(mat), math::element_type(mat).size * 4);
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
    EXPECT_EQ(*at<float>(mat, 0, 0), mat4.at(0, 0));
    EXPECT_EQ(*at<float>(mat, 1, 0), mat4.at(0, 1));
    EXPECT_EQ(*at<float>(mat, 2, 0), mat4.at(0, 2));
    EXPECT_EQ(*at<float>(mat, 3, 0), mat4.at(0, 3));
    EXPECT_EQ(*at<float>(mat, 0, 1), mat4.at(1, 0));
    EXPECT_EQ(*at<float>(mat, 1, 1), mat4.at(1, 1));
    EXPECT_EQ(*at<float>(mat, 2, 1), mat4.at(1, 2));
    EXPECT_EQ(*at<float>(mat, 3, 1), mat4.at(1, 3));
    EXPECT_EQ(*at<float>(mat, 0, 2), mat4.at(2, 0));
    EXPECT_EQ(*at<float>(mat, 1, 2), mat4.at(2, 1));
    EXPECT_EQ(*at<float>(mat, 2, 2), mat4.at(2, 2));
    EXPECT_EQ(*at<float>(mat, 3, 2), mat4.at(2, 3));
    EXPECT_EQ(*at<float>(mat, 0, 3), mat4.at(3, 0));
    EXPECT_EQ(*at<float>(mat, 1, 3), mat4.at(3, 1));
    EXPECT_EQ(*at<float>(mat, 2, 3), mat4.at(3, 2));
    EXPECT_EQ(*at<float>(mat, 3, 3), mat4.at(3, 3));
}

TEST(test_mat_view, test_make_view)
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

    auto mat = math::make_view(mat4);
    const auto sub_mat = math::make_view(mat, math::rectangle<int>{1, 1, 3, 3});

    EXPECT_EQ(math::width(sub_mat), 2);
    EXPECT_EQ(math::height(sub_mat), 2);

    // Mat4 is column order, a mat_view is row order
    EXPECT_EQ(*at<float>(sub_mat, 0, 0), mat4.at(1, 1));
    EXPECT_EQ(*at<float>(sub_mat, 0, 1), mat4.at(2, 1));
    EXPECT_EQ(*at<float>(sub_mat, 1, 0), mat4.at(1, 2));
    EXPECT_EQ(*at<float>(sub_mat, 1, 1), mat4.at(2, 2));
}

TEST(test_mat_view, test_equals)
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

    auto mat = math::make_view(mat4);
    auto mat2 = math::make_view(mat4);

    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat != mat2);
}

TEST(test_mat_view, test_equals2)
{
    // clang-format off
    math::mat4 mat4
    {
        1.0f,     2.0f,  10.0f, 30.0f,
        3.0f,     4.0f,  20.0f, 40.0f,
        100.0f, 300.0f,   1.0f,  2.0f,
        200.0f, 400.0f,   3.0f,  4.0f
    };
    // clang-format on

    auto mat4_view = math::make_view(mat4);

    auto mat = math::make_view(mat4_view, math::rectangle<int>{0, 0, 2, 2});
    auto mat2 = math::make_view(mat4_view, math::rectangle<int>{2, 2, 4, 4});

    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat != mat2);
}

TEST(test_mat_view, test_swizzle_2)
{
    std::array<std::uint32_t, 2> original_data{10, 20};

    auto data = original_data;
    math::mat_view mat{
        common::element_type::u32_2, {1, 1}, reinterpret_cast<math::mat_view::underlying_type *>(std::data(data))};

    math::swizzle<math::swizzle_r, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 2>{10, 20}));

    data = original_data;
    math::swizzle<math::swizzle_g, math::swizzle_r>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 2>{20, 10}));

    data = original_data;
    math::swizzle<math::swizzle_r, math::swizzle_r>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 2>{10, 10}));

    data = original_data;
    math::swizzle<math::swizzle_g, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 2>{20, 20}));
}

TEST(test_mat_view, test_swizzle_3)
{
    std::array<std::uint32_t, 3> original_data{10, 20, 30};

    auto data = original_data;
    math::mat_view mat{
        common::element_type::u32_3, {1, 1}, reinterpret_cast<math::mat_view::underlying_type *>(std::data(data))};

    math::swizzle<math::swizzle_r, math::swizzle_g, math::swizzle_b>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{10, 20, 30}));

    data = original_data;
    math::swizzle<math::swizzle_b, math::swizzle_g, math::swizzle_r>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{30, 20, 10}));

    data = original_data;
    math::swizzle<math::swizzle_b, math::swizzle_r, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{30, 10, 20}));

    data = original_data;
    math::swizzle<math::swizzle_b, math::swizzle_b, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{30, 30, 20}));

    data = original_data;
    math::swizzle<math::swizzle_r, math::swizzle_r, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{10, 10, 20}));

    data = original_data;
    math::swizzle<math::swizzle_r, math::swizzle_r, math::swizzle_r>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{10, 10, 10}));

    data = original_data;
    math::swizzle<math::swizzle_g, math::swizzle_g, math::swizzle_g>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{20, 20, 20}));

    data = original_data;
    math::swizzle<math::swizzle_b, math::swizzle_b, math::swizzle_b>(mat);
    EXPECT_EQ(data, (std::array<std::uint32_t, 3>{30, 30, 30}));
}
