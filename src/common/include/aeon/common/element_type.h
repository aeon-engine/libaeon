// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <cstdint>
#include <cstddef>

namespace aeon::common
{

enum class element_type_name
{
    u8,
    s8,
    u16,
    s16,
    u32,
    s32,
    u64,
    s64,
    f32,
    f64,
    undefined,
};

template <typename T>
struct element_type_name_trait final
{
};

#define create_data_type_trait(type, value)                                                                            \
    template <>                                                                                                        \
    struct element_type_name_trait<type> final                                                                         \
    {                                                                                                                  \
        static constexpr auto name = value;                                                                            \
    }

create_data_type_trait(std::uint8_t, element_type_name::u8);
create_data_type_trait(std::int8_t, element_type_name::s8);
create_data_type_trait(std::uint16_t, element_type_name::u16);
create_data_type_trait(std::int16_t, element_type_name::s16);
create_data_type_trait(std::uint32_t, element_type_name::u32);
create_data_type_trait(std::int32_t, element_type_name::s32);
create_data_type_trait(std::uint64_t, element_type_name::u64);
create_data_type_trait(std::int64_t, element_type_name::s64);
create_data_type_trait(float, element_type_name::f32);
create_data_type_trait(double, element_type_name::f64);

template <typename T, std::size_t count_t, std::size_t stride_t = sizeof(T) * count_t>
struct element_type_info
{
    static_assert(count_t > 0, "element_count_t must be > 0");
    static constexpr auto name = element_type_name_trait<T>::name;
    static constexpr auto component_size = sizeof(T);
    static constexpr auto count = count_t;
    static constexpr auto size = sizeof(T) * count_t;
    static constexpr auto stride = stride_t;
};

struct element_type final
{
    constexpr element_type() noexcept
        : name{element_type_name::undefined}
        , component_size{0}
        , count{0}
        , size{0}
        , stride{0}
    {
    }

    template <typename T, int count_t, int size_t>
    constexpr element_type(element_type_info<T, count_t, size_t> info) noexcept
        : name{info.name}
        , component_size{info.component_size}
        , count{info.count}
        , size{info.size}
        , stride{info.stride}
    {
        static_assert(count_t > 0, "element_count_t must be > 0");
        static_assert(info.component_size > 0, "component_size must be > 0");
        static_assert(info.size > 0, "size must be > 0");
        static_assert(info.stride > 0, "stride must be > 0");
    }

    template <typename T, int count_t, int size_t>
    constexpr auto operator=(element_type_info<T, count_t, size_t> info) noexcept -> element_type &
    {
        static_assert(count_t > 0, "element_count_t must be > 0");
        static_assert(info.component_size > 0, "component_size must be > 0");
        static_assert(info.size > 0, "size must be > 0");
        static_assert(info.stride > 0, "stride must be > 0");

        name = info.name;
        component_size = info.component_size;
        count = info.count;
        size = info.size;
        stride = info.stride;
        return *this;
    }

    [[nodiscard]] auto valid() const noexcept
    {
        return name != element_type_name::undefined && component_size > 0 && count > 0 && size > 0 && stride > 0;
    }

    element_type_name name;
    std::size_t component_size;
    std::size_t count;
    std::size_t size;
    std::size_t stride;

    static constexpr auto u8_1 = element_type_info<std::uint8_t, 1>{}; // 1 element of uint8_t
    static constexpr auto u8_2 = element_type_info<std::uint8_t, 2>{}; // 2 elements of uint8_t
    static constexpr auto u8_3 = element_type_info<std::uint8_t, 3>{}; // 3 elements of uint8_t
    static constexpr auto u8_4 = element_type_info<std::uint8_t, 4>{}; // 4 elements of uint8_t

    static constexpr auto u8_1_stride_4 =
        element_type_info<std::uint8_t, 1, 4 * sizeof(std::uint8_t)>{}; // 1 element of uint8_t, with a stride of 4

    /*!
     * 1 element of uint8_t, with a stride of 4
     * This can be used for example with an RGB image that has a stride of 4 bytes.
     */
    static constexpr auto u8_3_stride_4 = element_type_info<std::uint8_t, 3, 4>{};

    static constexpr auto s8_1 = element_type_info<std::int8_t, 1>{}; // 1 element of int8_t
    static constexpr auto s8_2 = element_type_info<std::int8_t, 2>{}; // 2 elements of int8_t
    static constexpr auto s8_3 = element_type_info<std::int8_t, 3>{}; // 3 elements of int8_t
    static constexpr auto s8_4 = element_type_info<std::int8_t, 4>{}; // 4 elements of int8_t

    static constexpr auto us8_1_stride_4 =
        element_type_info<std::int8_t, 1, 4>{}; // 1 element of int8_t, with a stride of 4
    static constexpr auto s8_3_stride_4 =
        element_type_info<std::int8_t, 3, 4>{}; // 3 elements of uint8_t, with a stride of 4

    static constexpr auto u16_1 = element_type_info<std::uint16_t, 1>{}; // 1 element of uint16_t

    static constexpr auto u16_1_stride_4 =
        element_type_info<std::uint16_t, 1, 4>{}; // 1 element of uint16_t, with a stride of 4

    static constexpr auto u16_2 = element_type_info<std::uint16_t, 2>{}; // 2 elements of uint16_t
    static constexpr auto u16_3 = element_type_info<std::uint16_t, 3>{}; // 3 elements of uint16_t
    static constexpr auto u16_4 = element_type_info<std::uint16_t, 4>{}; // 4 elements of uint16_t

    static constexpr auto s16_1 = element_type_info<std::int16_t, 1>{}; // 1 element of int16_t
    static constexpr auto s16_2 = element_type_info<std::int16_t, 2>{}; // 2 elements of int16_t
    static constexpr auto s16_3 = element_type_info<std::int16_t, 3>{}; // 3 elements of int16_t
    static constexpr auto s16_4 = element_type_info<std::int16_t, 4>{}; // 4 elements of int16_t

    static constexpr auto s16_1_stride_4 =
        element_type_info<std::int16_t, 1, 4>{}; // 1 element of int16_t, with a stride of 4

    static constexpr auto u32_1 = element_type_info<std::uint32_t, 1>{}; // 1 element of uint32_t
    static constexpr auto u32_2 = element_type_info<std::uint32_t, 2>{}; // 2 elements of uint32_t
    static constexpr auto u32_3 = element_type_info<std::uint32_t, 3>{}; // 3 elements of uint32_t
    static constexpr auto u32_4 = element_type_info<std::uint32_t, 4>{}; // 4 elements of uint32_t

    static constexpr auto u32_1_stride_8 =
        element_type_info<std::uint32_t, 1, 8>{}; // 1 element of uint32_t, with a stride of 8

    static constexpr auto s32_1 = element_type_info<std::int32_t, 1>{}; // 1 element of int32_t
    static constexpr auto s32_2 = element_type_info<std::int32_t, 2>{}; // 2 elements of int32_t
    static constexpr auto s32_3 = element_type_info<std::int32_t, 3>{}; // 3 elements of int32_t
    static constexpr auto s32_4 = element_type_info<std::int32_t, 4>{}; // 4 elements of int32_t

    static constexpr auto s32_1_stride_8 =
        element_type_info<std::int32_t, 1, 8>{}; // 1 element of int32_t, with a stride of 8

    static constexpr auto u64_1 = element_type_info<std::uint64_t, 1>{}; // 1 element of uint64_t
    static constexpr auto u64_2 = element_type_info<std::uint64_t, 2>{}; // 2 elements of uint64_t
    static constexpr auto u64_3 = element_type_info<std::uint64_t, 3>{}; // 3 elements of uint64_t
    static constexpr auto u64_4 = element_type_info<std::uint64_t, 4>{}; // 4 elements of uint64_t

    static constexpr auto s64_1 = element_type_info<std::int64_t, 1>{}; // 1 element of int64_t
    static constexpr auto s64_2 = element_type_info<std::int64_t, 2>{}; // 2 elements of int64_t
    static constexpr auto s64_3 = element_type_info<std::int64_t, 3>{}; // 3 elements of int64_t
    static constexpr auto s64_4 = element_type_info<std::int64_t, 4>{}; // 4 elements of int64_t

    static constexpr auto f32_1 = element_type_info<float, 1>{}; // 1 element of float
    static constexpr auto f32_2 = element_type_info<float, 2>{}; // 2 elements of float
    static constexpr auto f32_3 = element_type_info<float, 3>{}; // 3 elements of float
    static constexpr auto f32_4 = element_type_info<float, 4>{}; // 4 elements of float

    static constexpr auto f32_1_stride_8 = element_type_info<float, 1, 8>{}; // 1 element of float, with a stride of 8

    static constexpr auto f64_1 = element_type_info<double, 1>{}; // 1 element of double
    static constexpr auto f64_2 = element_type_info<double, 2>{}; // 2 elements of double
    static constexpr auto f64_3 = element_type_info<double, 3>{}; // 3 elements of double
    static constexpr auto f64_4 = element_type_info<double, 4>{}; // 4 elements of double
};

inline constexpr auto operator==(const element_type &lhs, const element_type &rhs) noexcept -> bool
{
    return lhs.name == rhs.name && lhs.component_size == rhs.component_size && lhs.count == rhs.count &&
           lhs.size == rhs.size && lhs.stride == rhs.stride;
}

inline constexpr auto operator!=(const element_type &lhs, const element_type &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

/*!
 * Calculate the offset of an element within an array of bytes
 * \param[in] type - An element type
 * \param[in] stride - The stride in bytes (Typically width * type.stride)
 * \param[in] x - The x position
 * \param[in] y - The y position
 * \return The offset in bytes that an element would be at
 */
[[nodiscard]] inline constexpr auto offset_of(const element_type &type, const std::size_t stride, const std::int64_t x,
                                              const std::int64_t y) noexcept -> std::size_t
{
    aeon_assert(x >= 0, "X must be >= 0");
    aeon_assert(y >= 0, "Y must be >= 0");
    aeon_assert(stride > 0, "stride must be >= 0");

    return stride * y + type.stride * x;
}

} // namespace aeon::common
