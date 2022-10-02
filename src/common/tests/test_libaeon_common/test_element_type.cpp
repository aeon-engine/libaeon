// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/element_type.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_element_type, test_element_type_names)
{
    EXPECT_EQ(common::element_type_name::s8, common::element_type::s8_1.name);
    EXPECT_EQ(common::element_type_name::s8, common::element_type::s8_2.name);
    EXPECT_EQ(common::element_type_name::s8, common::element_type::s8_3.name);
    EXPECT_EQ(common::element_type_name::s8, common::element_type::s8_4.name);
    EXPECT_EQ(common::element_type_name::u8, common::element_type::u8_1.name);
    EXPECT_EQ(common::element_type_name::u8, common::element_type::u8_2.name);
    EXPECT_EQ(common::element_type_name::u8, common::element_type::u8_3.name);
    EXPECT_EQ(common::element_type_name::u8, common::element_type::u8_4.name);

    EXPECT_EQ(common::element_type_name::s16, common::element_type::s16_1.name);
    EXPECT_EQ(common::element_type_name::s16, common::element_type::s16_2.name);
    EXPECT_EQ(common::element_type_name::s16, common::element_type::s16_3.name);
    EXPECT_EQ(common::element_type_name::s16, common::element_type::s16_4.name);
    EXPECT_EQ(common::element_type_name::u16, common::element_type::u16_1.name);
    EXPECT_EQ(common::element_type_name::u16, common::element_type::u16_2.name);
    EXPECT_EQ(common::element_type_name::u16, common::element_type::u16_3.name);
    EXPECT_EQ(common::element_type_name::u16, common::element_type::u16_4.name);

    EXPECT_EQ(common::element_type_name::s32, common::element_type::s32_1.name);
    EXPECT_EQ(common::element_type_name::s32, common::element_type::s32_2.name);
    EXPECT_EQ(common::element_type_name::s32, common::element_type::s32_3.name);
    EXPECT_EQ(common::element_type_name::s32, common::element_type::s32_4.name);
    EXPECT_EQ(common::element_type_name::u32, common::element_type::u32_1.name);
    EXPECT_EQ(common::element_type_name::u32, common::element_type::u32_2.name);
    EXPECT_EQ(common::element_type_name::u32, common::element_type::u32_3.name);
    EXPECT_EQ(common::element_type_name::u32, common::element_type::u32_4.name);

    EXPECT_EQ(common::element_type_name::s64, common::element_type::s64_1.name);
    EXPECT_EQ(common::element_type_name::s64, common::element_type::s64_2.name);
    EXPECT_EQ(common::element_type_name::s64, common::element_type::s64_3.name);
    EXPECT_EQ(common::element_type_name::s64, common::element_type::s64_4.name);
    EXPECT_EQ(common::element_type_name::u64, common::element_type::u64_1.name);
    EXPECT_EQ(common::element_type_name::u64, common::element_type::u64_2.name);
    EXPECT_EQ(common::element_type_name::u64, common::element_type::u64_3.name);
    EXPECT_EQ(common::element_type_name::u64, common::element_type::u64_4.name);

    EXPECT_EQ(common::element_type_name::f32, common::element_type::f32_1.name);
    EXPECT_EQ(common::element_type_name::f32, common::element_type::f32_2.name);
    EXPECT_EQ(common::element_type_name::f32, common::element_type::f32_3.name);
    EXPECT_EQ(common::element_type_name::f32, common::element_type::f32_4.name);

    EXPECT_EQ(common::element_type_name::f64, common::element_type::f64_1.name);
    EXPECT_EQ(common::element_type_name::f64, common::element_type::f64_2.name);
    EXPECT_EQ(common::element_type_name::f64, common::element_type::f64_3.name);
    EXPECT_EQ(common::element_type_name::f64, common::element_type::f64_4.name);
}

TEST(test_element_type, test_element_type_sizes)
{
    EXPECT_EQ(sizeof(std::int8_t) * 1, common::element_type::s8_1.size);
    EXPECT_EQ(sizeof(std::int8_t) * 2, common::element_type::s8_2.size);
    EXPECT_EQ(sizeof(std::int8_t) * 3, common::element_type::s8_3.size);
    EXPECT_EQ(sizeof(std::int8_t) * 4, common::element_type::s8_4.size);
    EXPECT_EQ(sizeof(std::uint8_t) * 1, common::element_type::u8_1.size);
    EXPECT_EQ(sizeof(std::uint8_t) * 2, common::element_type::u8_2.size);
    EXPECT_EQ(sizeof(std::uint8_t) * 3, common::element_type::u8_3.size);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, common::element_type::u8_4.size);

    EXPECT_EQ(sizeof(std::int16_t) * 1, common::element_type::s16_1.size);
    EXPECT_EQ(sizeof(std::int16_t) * 2, common::element_type::s16_2.size);
    EXPECT_EQ(sizeof(std::int16_t) * 3, common::element_type::s16_3.size);
    EXPECT_EQ(sizeof(std::int16_t) * 4, common::element_type::s16_4.size);
    EXPECT_EQ(sizeof(std::uint16_t) * 1, common::element_type::u16_1.size);
    EXPECT_EQ(sizeof(std::uint16_t) * 2, common::element_type::u16_2.size);
    EXPECT_EQ(sizeof(std::uint16_t) * 3, common::element_type::u16_3.size);
    EXPECT_EQ(sizeof(std::uint16_t) * 4, common::element_type::u16_4.size);

    EXPECT_EQ(sizeof(std::int32_t) * 1, common::element_type::s32_1.size);
    EXPECT_EQ(sizeof(std::int32_t) * 2, common::element_type::s32_2.size);
    EXPECT_EQ(sizeof(std::int32_t) * 3, common::element_type::s32_3.size);
    EXPECT_EQ(sizeof(std::int32_t) * 4, common::element_type::s32_4.size);
    EXPECT_EQ(sizeof(std::uint32_t) * 1, common::element_type::u32_1.size);
    EXPECT_EQ(sizeof(std::uint32_t) * 2, common::element_type::u32_2.size);
    EXPECT_EQ(sizeof(std::uint32_t) * 3, common::element_type::u32_3.size);
    EXPECT_EQ(sizeof(std::uint32_t) * 4, common::element_type::u32_4.size);

    EXPECT_EQ(sizeof(std::int64_t) * 1, common::element_type::s64_1.size);
    EXPECT_EQ(sizeof(std::int64_t) * 2, common::element_type::s64_2.size);
    EXPECT_EQ(sizeof(std::int64_t) * 3, common::element_type::s64_3.size);
    EXPECT_EQ(sizeof(std::int64_t) * 4, common::element_type::s64_4.size);
    EXPECT_EQ(sizeof(std::uint64_t) * 1, common::element_type::u64_1.size);
    EXPECT_EQ(sizeof(std::uint64_t) * 2, common::element_type::u64_2.size);
    EXPECT_EQ(sizeof(std::uint64_t) * 3, common::element_type::u64_3.size);
    EXPECT_EQ(sizeof(std::uint64_t) * 4, common::element_type::u64_4.size);

    EXPECT_EQ(sizeof(float) * 1, common::element_type::f32_1.size);
    EXPECT_EQ(sizeof(float) * 2, common::element_type::f32_2.size);
    EXPECT_EQ(sizeof(float) * 3, common::element_type::f32_3.size);
    EXPECT_EQ(sizeof(float) * 4, common::element_type::f32_4.size);

    EXPECT_EQ(sizeof(double) * 1, common::element_type::f64_1.size);
    EXPECT_EQ(sizeof(double) * 2, common::element_type::f64_2.size);
    EXPECT_EQ(sizeof(double) * 3, common::element_type::f64_3.size);
    EXPECT_EQ(sizeof(double) * 4, common::element_type::f64_4.size);

    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_1_stride_4.size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_1_stride_4.size);
}

TEST(test_element_type, test_element_type_component_size)
{
    EXPECT_EQ(sizeof(std::int8_t), common::element_type::s8_1.component_size);
    EXPECT_EQ(sizeof(std::int8_t), common::element_type::s8_2.component_size);
    EXPECT_EQ(sizeof(std::int8_t), common::element_type::s8_3.component_size);
    EXPECT_EQ(sizeof(std::int8_t), common::element_type::s8_4.component_size);
    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_1.component_size);
    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_2.component_size);
    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_3.component_size);
    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_4.component_size);

    EXPECT_EQ(sizeof(std::int16_t), common::element_type::s16_1.component_size);
    EXPECT_EQ(sizeof(std::int16_t), common::element_type::s16_2.component_size);
    EXPECT_EQ(sizeof(std::int16_t), common::element_type::s16_3.component_size);
    EXPECT_EQ(sizeof(std::int16_t), common::element_type::s16_4.component_size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_1.component_size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_2.component_size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_3.component_size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_4.component_size);

    EXPECT_EQ(sizeof(std::int32_t), common::element_type::s32_1.component_size);
    EXPECT_EQ(sizeof(std::int32_t), common::element_type::s32_2.component_size);
    EXPECT_EQ(sizeof(std::int32_t), common::element_type::s32_3.component_size);
    EXPECT_EQ(sizeof(std::int32_t), common::element_type::s32_4.component_size);
    EXPECT_EQ(sizeof(std::uint32_t), common::element_type::u32_1.component_size);
    EXPECT_EQ(sizeof(std::uint32_t), common::element_type::u32_2.component_size);
    EXPECT_EQ(sizeof(std::uint32_t), common::element_type::u32_3.component_size);
    EXPECT_EQ(sizeof(std::uint32_t), common::element_type::u32_4.component_size);

    EXPECT_EQ(sizeof(std::int64_t), common::element_type::s64_1.component_size);
    EXPECT_EQ(sizeof(std::int64_t), common::element_type::s64_2.component_size);
    EXPECT_EQ(sizeof(std::int64_t), common::element_type::s64_3.component_size);
    EXPECT_EQ(sizeof(std::int64_t), common::element_type::s64_4.component_size);
    EXPECT_EQ(sizeof(std::uint64_t), common::element_type::u64_1.component_size);
    EXPECT_EQ(sizeof(std::uint64_t), common::element_type::u64_2.component_size);
    EXPECT_EQ(sizeof(std::uint64_t), common::element_type::u64_3.component_size);
    EXPECT_EQ(sizeof(std::uint64_t), common::element_type::u64_4.component_size);

    EXPECT_EQ(sizeof(float), common::element_type::f32_1.component_size);
    EXPECT_EQ(sizeof(float), common::element_type::f32_2.component_size);
    EXPECT_EQ(sizeof(float), common::element_type::f32_3.component_size);
    EXPECT_EQ(sizeof(float), common::element_type::f32_4.component_size);

    EXPECT_EQ(sizeof(double), common::element_type::f64_1.component_size);
    EXPECT_EQ(sizeof(double), common::element_type::f64_2.component_size);
    EXPECT_EQ(sizeof(double), common::element_type::f64_3.component_size);
    EXPECT_EQ(sizeof(double), common::element_type::f64_4.component_size);

    EXPECT_EQ(sizeof(std::uint8_t), common::element_type::u8_1_stride_4.component_size);
    EXPECT_EQ(sizeof(std::uint16_t), common::element_type::u16_1_stride_4.component_size);
}

TEST(test_element_type, test_element_type_strides)
{
    EXPECT_EQ(sizeof(std::int8_t) * 1, common::element_type::s8_1.stride);
    EXPECT_EQ(sizeof(std::int8_t) * 2, common::element_type::s8_2.stride);
    EXPECT_EQ(sizeof(std::int8_t) * 3, common::element_type::s8_3.stride);
    EXPECT_EQ(sizeof(std::int8_t) * 4, common::element_type::s8_4.stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 1, common::element_type::u8_1.stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 2, common::element_type::u8_2.stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 3, common::element_type::u8_3.stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, common::element_type::u8_4.stride);

    EXPECT_EQ(sizeof(std::int16_t) * 1, common::element_type::s16_1.stride);
    EXPECT_EQ(sizeof(std::int16_t) * 2, common::element_type::s16_2.stride);
    EXPECT_EQ(sizeof(std::int16_t) * 3, common::element_type::s16_3.stride);
    EXPECT_EQ(sizeof(std::int16_t) * 4, common::element_type::s16_4.stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 1, common::element_type::u16_1.stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 2, common::element_type::u16_2.stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 3, common::element_type::u16_3.stride);
    EXPECT_EQ(sizeof(std::uint16_t) * 4, common::element_type::u16_4.stride);

    EXPECT_EQ(sizeof(std::int32_t) * 1, common::element_type::s32_1.stride);
    EXPECT_EQ(sizeof(std::int32_t) * 2, common::element_type::s32_2.stride);
    EXPECT_EQ(sizeof(std::int32_t) * 3, common::element_type::s32_3.stride);
    EXPECT_EQ(sizeof(std::int32_t) * 4, common::element_type::s32_4.stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 1, common::element_type::u32_1.stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 2, common::element_type::u32_2.stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 3, common::element_type::u32_3.stride);
    EXPECT_EQ(sizeof(std::uint32_t) * 4, common::element_type::u32_4.stride);

    EXPECT_EQ(sizeof(std::int64_t) * 1, common::element_type::s64_1.stride);
    EXPECT_EQ(sizeof(std::int64_t) * 2, common::element_type::s64_2.stride);
    EXPECT_EQ(sizeof(std::int64_t) * 3, common::element_type::s64_3.stride);
    EXPECT_EQ(sizeof(std::int64_t) * 4, common::element_type::s64_4.stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 1, common::element_type::u64_1.stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 2, common::element_type::u64_2.stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 3, common::element_type::u64_3.stride);
    EXPECT_EQ(sizeof(std::uint64_t) * 4, common::element_type::u64_4.stride);

    EXPECT_EQ(sizeof(float) * 1, common::element_type::f32_1.stride);
    EXPECT_EQ(sizeof(float) * 2, common::element_type::f32_2.stride);
    EXPECT_EQ(sizeof(float) * 3, common::element_type::f32_3.stride);
    EXPECT_EQ(sizeof(float) * 4, common::element_type::f32_4.stride);

    EXPECT_EQ(sizeof(double) * 1, common::element_type::f64_1.stride);
    EXPECT_EQ(sizeof(double) * 2, common::element_type::f64_2.stride);
    EXPECT_EQ(sizeof(double) * 3, common::element_type::f64_3.stride);
    EXPECT_EQ(sizeof(double) * 4, common::element_type::f64_4.stride);

    EXPECT_EQ(sizeof(std::uint8_t) * 4, common::element_type::u8_1_stride_4.stride);
    EXPECT_EQ(sizeof(std::uint8_t) * 4, common::element_type::u16_1_stride_4.stride);
}

TEST(test_element_type, test_element_type_ctor)
{
    const common::element_type t{common::element_type::f32_4};
    EXPECT_EQ(common::element_type_name::f32, t.name);
    EXPECT_EQ(4ull, t.count);
    EXPECT_EQ(sizeof(float) * 4, t.size);
}

TEST(test_element_type, test_element_type_assign)
{
    const common::element_type t = common::element_type::f32_4;
    EXPECT_EQ(common::element_type_name::f32, t.name);
    EXPECT_EQ(4ull, t.count);
    EXPECT_EQ(sizeof(float) * 4, t.size);
}

TEST(test_element_type, test_element_type_compare)
{
    const common::element_type t{common::element_type::f32_4};
    const common::element_type t2{common::element_type::f32_4};
    const common::element_type t3{common::element_type::f32_3};
    const common::element_type t4{common::element_type::u32_4};

    EXPECT_TRUE(t == t2);
    EXPECT_FALSE(t != t2);

    EXPECT_FALSE(t == t3);
    EXPECT_FALSE(t2 == t3);
    EXPECT_TRUE(t != t3);
    EXPECT_TRUE(t2 != t3);

    EXPECT_FALSE(t == t4);
    EXPECT_FALSE(t2 == t4);
    EXPECT_FALSE(t3 == t4);
    EXPECT_TRUE(t != t4);
    EXPECT_TRUE(t2 != t4);
    EXPECT_TRUE(t3 != t4);

    const common::element_type t5{common::element_type::u8_4};
    const common::element_type t6{common::element_type::u8_3_stride_4};

    EXPECT_TRUE(t5 != t6);
    EXPECT_FALSE(t5 == t6);
    EXPECT_TRUE(t6 != t5);
    EXPECT_FALSE(t6 == t5);
}

TEST(test_element_type, test_element_type_copy)
{
    const common::element_type t{common::element_type::f32_4};
    const auto t2 = t;

    EXPECT_TRUE(t == t2);
    EXPECT_FALSE(t != t2);
}

TEST(test_element_type, test_element_offset_of)
{
    const common::element_type t{common::element_type::f32_4};
    const auto width = 4;
    const auto stride = t.stride * width;

    EXPECT_EQ(0ull, common::offset_of(t, stride, 0, 0));
    EXPECT_EQ(sizeof(float) * 4, common::offset_of(t, stride, 1, 0));
    EXPECT_EQ(sizeof(float) * 8, common::offset_of(t, stride, 2, 0));
    EXPECT_EQ(sizeof(float) * 12, common::offset_of(t, stride, 3, 0));
    EXPECT_EQ(sizeof(float) * 16, common::offset_of(t, stride, 0, 1));
}

TEST(test_element_type, test_element_offset_of_with_stride_element)
{
    const common::element_type t{common::element_type::u8_3_stride_4};
    const auto width = 4ull;
    const auto stride = t.stride * width;

    EXPECT_EQ(0ull, common::offset_of(t, stride, 0, 0));
    EXPECT_EQ(4ull, common::offset_of(t, stride, 1, 0));
    EXPECT_EQ(8ull, common::offset_of(t, stride, 2, 0));
    EXPECT_EQ(12ull, common::offset_of(t, stride, 3, 0));
    EXPECT_EQ(16ull, common::offset_of(t, stride, 0, 1));
}
