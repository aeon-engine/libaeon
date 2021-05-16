// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/math/mat.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_mat, test_mat_default)
{
    math::mat mat;
    EXPECT_TRUE(math::null(mat));
    EXPECT_FALSE(math::valid(mat));
    EXPECT_TRUE(math::continuous(mat));
    EXPECT_EQ(math::width(mat), 0);
    EXPECT_EQ(math::height(mat), 0);
    EXPECT_EQ(math::stride(mat), 0);
    EXPECT_EQ(common::element_type_name::undefined, math::element_type(mat).name);
    EXPECT_EQ(0, math::element_type(mat).count);
    EXPECT_EQ(0.0f, math::element_type(mat).size);
}

TEST(test_mat, test_clone)
{
    // clang-format off
    math::mat3 mat3
    {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };
    // clang-format on

    const auto mat = static_cast<math::mat>(math::make_view(mat3));
    EXPECT_EQ(common::element_type_name::f32, math::element_type(mat).name);
    EXPECT_EQ(1, math::element_type(mat).count);
    EXPECT_EQ(sizeof(float), math::element_type(mat).size);

    const auto mat2 = mat.clone();
    EXPECT_EQ(math::element_type(mat), math::element_type(mat2));
    EXPECT_TRUE(mat == mat2);
    EXPECT_FALSE(mat != mat2);
}

TEST(test_mat, test_swizzle_copy_3)
{
    std::array<std::uint32_t, 1> data{10};

    math::mat_view mat{
        common::element_type::u32_1, {1, 1}, reinterpret_cast<math::mat_view::underlying_type *>(std::data(data))};

    const auto mat_result = math::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r>(mat);
    EXPECT_EQ(common::element_type::u32_3, mat_result.element_type());
    EXPECT_EQ(1, mat_result.width());
    EXPECT_EQ(1, mat_result.height());

    const auto result_data = math::at<std::uint32_t>(mat_result, math::vector2{0, 0});
    EXPECT_EQ(data[0], result_data[0]);
    EXPECT_EQ(data[0], result_data[1]);
    EXPECT_EQ(data[0], result_data[2]);
}

TEST(test_mat, test_swizzle_change)
{
    std::array<std::uint32_t, 1> data{10};

    math::mat_view mat{
        common::element_type::u32_1, {1, 1}, reinterpret_cast<math::mat_view::underlying_type *>(std::data(data))};

    auto mat_result = math::swizzle_copy<math::swizzle_x, math::swizzle_one, math::swizzle_zero>(mat);
    auto result_data = math::at<std::uint32_t>(mat_result, math::vector2{0, 0});
    EXPECT_EQ(data[0], result_data[0]);
    EXPECT_EQ(1u, result_data[1]);
    EXPECT_EQ(0u, result_data[2]);

    mat_result = math::swizzle_copy<math::swizzle_max, math::swizzle_min, math::swizzle_x>(mat);
    result_data = math::at<std::uint32_t>(mat_result, math::vector2{0, 0});
    EXPECT_EQ(0xffffffffu, result_data[0]);
    EXPECT_EQ(0u, result_data[1]);
    EXPECT_EQ(data[0], result_data[2]);
}
