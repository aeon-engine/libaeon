// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

template <typename T, std::size_t count_t, std::size_t stride_t = sizeof(T) * count_t,
          std::size_t component_size_t = sizeof(T), std::size_t full_size_t = sizeof(T) * count_t>
struct element_type_info
{
    static constexpr auto name = element_type_name_trait<T>::name;
    static constexpr auto component_size = component_size_t;
    static constexpr auto count = count_t;
    static constexpr auto size = full_size_t;
    static constexpr auto stride = stride_t;
};

struct element_type final
{
    constexpr element_type() noexcept
        : name{element_type_name::undefined}
        , component_size{0ull}
        , count{0ull}
        , size{0ull}
        , stride{0ull}
    {
    }

    template <typename T, std::size_t count_t, std::size_t stride_t, std::size_t component_size_t,
              std::size_t full_size_t>
    constexpr element_type(element_type_info<T, count_t, stride_t, component_size_t, full_size_t> info) noexcept
        : name{info.name}
        , component_size{info.component_size}
        , count{info.count}
        , size{info.size}
        , stride{info.stride}
    {
    }

    template <typename T, std::size_t count_t, std::size_t stride_t, std::size_t component_size_t,
              std::size_t full_size_t>
    constexpr auto operator=(element_type_info<T, count_t, stride_t, component_size_t, full_size_t> info) noexcept
        -> element_type &
    {
        name = info.name;
        component_size = info.component_size;
        count = info.count;
        size = info.size;
        stride = info.stride;
        return *this;
    }

    /*!
     * The data is either compressed, or laid out in a way that a typical element size and stride don't make sense.
     */
    [[nodiscard]] auto is_undefined() const noexcept
    {
        return name == element_type_name::undefined && component_size == 0 && count == 0 && size == 0 && stride == 0;
    }

    [[nodiscard]] auto valid() const noexcept
    {
        return (name != element_type_name::undefined && component_size > 0 && count > 0 && size > 0 && stride > 0) ||
               is_undefined();
    }

    /*!
     * Check if the component is continuous (stride == size).
     * \return True if the component is continuous
     */
    [[nodiscard]] auto continuous() const noexcept
    {
        return stride == size;
    }

    element_type_name name;
    std::size_t component_size;
    std::size_t count;
    std::size_t size;
    std::size_t stride;

    static constexpr auto undefined =
        element_type_info<std::uint8_t, 0ull, 0ull, 0ull,
                          0ull>{}; // The data is either compressed, or laid out in a way that a
                                   // typical element size and stride don't make sense.

    static constexpr auto u8_1 = element_type_info<std::uint8_t, 1ull>{}; // 1 element of uint8_t
    static constexpr auto u8_2 = element_type_info<std::uint8_t, 2ull>{}; // 2 elements of uint8_t
    static constexpr auto u8_3 = element_type_info<std::uint8_t, 3ull>{}; // 3 elements of uint8_t
    static constexpr auto u8_4 = element_type_info<std::uint8_t, 4ull>{}; // 4 elements of uint8_t

    static constexpr auto u8_1_stride_4 =
        element_type_info<std::uint8_t, 1ull,
                          4ull * sizeof(std::uint8_t)>{}; // 1 element of uint8_t, with a stride of 4

    /*!
     * 1 element of uint8_t, with a stride of 4
     * This can be used for example with an RGB image that has a stride of 4 bytes.
     */
    static constexpr auto u8_3_stride_4 = element_type_info<std::uint8_t, 3ull, 4ull>{};

    static constexpr auto s8_1 = element_type_info<std::int8_t, 1ull>{}; // 1 element of int8_t
    static constexpr auto s8_2 = element_type_info<std::int8_t, 2ull>{}; // 2 elements of int8_t
    static constexpr auto s8_3 = element_type_info<std::int8_t, 3ull>{}; // 3 elements of int8_t
    static constexpr auto s8_4 = element_type_info<std::int8_t, 4ull>{}; // 4 elements of int8_t

    static constexpr auto us8_1_stride_4 =
        element_type_info<std::int8_t, 1ull, 4ull>{}; // 1 element of int8_t, with a stride of 4
    static constexpr auto s8_3_stride_4 =
        element_type_info<std::int8_t, 3ull, 4ull>{}; // 3 elements of uint8_t, with a stride of 4

    static constexpr auto u16_1 = element_type_info<std::uint16_t, 1ull>{}; // 1 element of uint16_t

    static constexpr auto u16_1_stride_4 =
        element_type_info<std::uint16_t, 1ull, 4ull>{}; // 1 element of uint16_t, with a stride of 4

    static constexpr auto u16_2 = element_type_info<std::uint16_t, 2ull>{}; // 2 elements of uint16_t
    static constexpr auto u16_3 = element_type_info<std::uint16_t, 3ull>{}; // 3 elements of uint16_t
    static constexpr auto u16_4 = element_type_info<std::uint16_t, 4ull>{}; // 4 elements of uint16_t

    static constexpr auto s16_1 = element_type_info<std::int16_t, 1ull>{}; // 1 element of int16_t
    static constexpr auto s16_2 = element_type_info<std::int16_t, 2ull>{}; // 2 elements of int16_t
    static constexpr auto s16_3 = element_type_info<std::int16_t, 3ull>{}; // 3 elements of int16_t
    static constexpr auto s16_4 = element_type_info<std::int16_t, 4ull>{}; // 4 elements of int16_t

    static constexpr auto s16_1_stride_4 =
        element_type_info<std::int16_t, 1ull, 4ull>{}; // 1 element of int16_t, with a stride of 4

    static constexpr auto u32_1 = element_type_info<std::uint32_t, 1ull>{}; // 1 element of uint32_t
    static constexpr auto u32_2 = element_type_info<std::uint32_t, 2ull>{}; // 2 elements of uint32_t
    static constexpr auto u32_3 = element_type_info<std::uint32_t, 3ull>{}; // 3 elements of uint32_t
    static constexpr auto u32_4 = element_type_info<std::uint32_t, 4ull>{}; // 4 elements of uint32_t

    static constexpr auto u32_1_stride_8 =
        element_type_info<std::uint32_t, 1ull, 8ull>{}; // 1 element of uint32_t, with a stride of 8

    static constexpr auto s32_1 = element_type_info<std::int32_t, 1ull>{}; // 1 element of int32_t
    static constexpr auto s32_2 = element_type_info<std::int32_t, 2ull>{}; // 2 elements of int32_t
    static constexpr auto s32_3 = element_type_info<std::int32_t, 3ull>{}; // 3 elements of int32_t
    static constexpr auto s32_4 = element_type_info<std::int32_t, 4ull>{}; // 4 elements of int32_t

    static constexpr auto s32_1_stride_8 =
        element_type_info<std::int32_t, 1ull, 8ull>{}; // 1 element of int32_t, with a stride of 8

    static constexpr auto u64_1 = element_type_info<std::uint64_t, 1ull>{}; // 1 element of uint64_t
    static constexpr auto u64_2 = element_type_info<std::uint64_t, 2ull>{}; // 2 elements of uint64_t
    static constexpr auto u64_3 = element_type_info<std::uint64_t, 3ull>{}; // 3 elements of uint64_t
    static constexpr auto u64_4 = element_type_info<std::uint64_t, 4ull>{}; // 4 elements of uint64_t

    static constexpr auto s64_1 = element_type_info<std::int64_t, 1ull>{}; // 1 element of int64_t
    static constexpr auto s64_2 = element_type_info<std::int64_t, 2ull>{}; // 2 elements of int64_t
    static constexpr auto s64_3 = element_type_info<std::int64_t, 3ull>{}; // 3 elements of int64_t
    static constexpr auto s64_4 = element_type_info<std::int64_t, 4ull>{}; // 4 elements of int64_t

    static constexpr auto f32_1 = element_type_info<float, 1ull>{}; // 1 element of float
    static constexpr auto f32_2 = element_type_info<float, 2ull>{}; // 2 elements of float
    static constexpr auto f32_3 = element_type_info<float, 3ull>{}; // 3 elements of float
    static constexpr auto f32_4 = element_type_info<float, 4ull>{}; // 4 elements of float

    static constexpr auto f32_1_stride_8 =
        element_type_info<float, 1ull, 8ull>{}; // 1 element of float, with a stride of 8

    static constexpr auto f64_1 = element_type_info<double, 1ull>{}; // 1 element of double
    static constexpr auto f64_2 = element_type_info<double, 2ull>{}; // 2 elements of double
    static constexpr auto f64_3 = element_type_info<double, 3ull>{}; // 3 elements of double
    static constexpr auto f64_4 = element_type_info<double, 4ull>{}; // 4 elements of double
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
