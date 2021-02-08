// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

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

template <typename T, int count_t>
struct element_type_info
{
    static_assert(count_t > 0, "element_count_t must be > 0");
    using type = T;
    static constexpr auto name = element_type_name_trait<type>::name;
    static constexpr auto count = count_t;
    static constexpr auto size = sizeof(type) * count;
};

struct element_type final
{
    constexpr element_type() noexcept
        : name{element_type_name::undefined}
        , count{0}
        , size{0}
    {
    }

    template <typename T, int count_t>
    constexpr element_type(element_type_info<T, count_t> info) noexcept
        : name{info.name}
        , count{info.count}
        , size{info.size}
    {
        static_assert(count_t > 0, "element_count_t must be > 0");
        static_assert(info.size > 0, "size must be > 0");
    }

    template <typename T, int count_t>
    constexpr auto operator=(element_type_info<T, count_t> info) noexcept -> element_type &
    {
        static_assert(count_t > 0, "element_count_t must be > 0");
        static_assert(info.size > 0, "size must be > 0");

        name = info.name;
        count = info.count;
        size = info.size;
        return *this;
    }

    [[nodiscard]] auto valid() const noexcept
    {
        return name != element_type_name::undefined && count > 0 && size > 0;
    }

    static constexpr auto u8_1 = element_type_info<std::uint8_t, 1>{};
    static constexpr auto u8_2 = element_type_info<std::uint8_t, 2>{};
    static constexpr auto u8_3 = element_type_info<std::uint8_t, 3>{};
    static constexpr auto u8_4 = element_type_info<std::uint8_t, 4>{};

    static constexpr auto s8_1 = element_type_info<std::int8_t, 1>{};
    static constexpr auto s8_2 = element_type_info<std::int8_t, 2>{};
    static constexpr auto s8_3 = element_type_info<std::int8_t, 3>{};
    static constexpr auto s8_4 = element_type_info<std::int8_t, 4>{};

    static constexpr auto u16_1 = element_type_info<std::uint16_t, 1>{};
    static constexpr auto u16_2 = element_type_info<std::uint16_t, 2>{};
    static constexpr auto u16_3 = element_type_info<std::uint16_t, 3>{};
    static constexpr auto u16_4 = element_type_info<std::uint16_t, 4>{};

    static constexpr auto s16_1 = element_type_info<std::int16_t, 1>{};
    static constexpr auto s16_2 = element_type_info<std::int16_t, 2>{};
    static constexpr auto s16_3 = element_type_info<std::int16_t, 3>{};
    static constexpr auto s16_4 = element_type_info<std::int16_t, 4>{};

    static constexpr auto u32_1 = element_type_info<std::uint32_t, 1>{};
    static constexpr auto u32_2 = element_type_info<std::uint32_t, 2>{};
    static constexpr auto u32_3 = element_type_info<std::uint32_t, 3>{};
    static constexpr auto u32_4 = element_type_info<std::uint32_t, 4>{};

    static constexpr auto s32_1 = element_type_info<std::int32_t, 1>{};
    static constexpr auto s32_2 = element_type_info<std::int32_t, 2>{};
    static constexpr auto s32_3 = element_type_info<std::int32_t, 3>{};
    static constexpr auto s32_4 = element_type_info<std::int32_t, 4>{};

    static constexpr auto u64_1 = element_type_info<std::uint64_t, 1>{};
    static constexpr auto u64_2 = element_type_info<std::uint64_t, 2>{};
    static constexpr auto u64_3 = element_type_info<std::uint64_t, 3>{};
    static constexpr auto u64_4 = element_type_info<std::uint64_t, 4>{};

    static constexpr auto s64_1 = element_type_info<std::int64_t, 1>{};
    static constexpr auto s64_2 = element_type_info<std::int64_t, 2>{};
    static constexpr auto s64_3 = element_type_info<std::int64_t, 3>{};
    static constexpr auto s64_4 = element_type_info<std::int64_t, 4>{};

    static constexpr auto f32_1 = element_type_info<float, 1>{};
    static constexpr auto f32_2 = element_type_info<float, 2>{};
    static constexpr auto f32_3 = element_type_info<float, 3>{};
    static constexpr auto f32_4 = element_type_info<float, 4>{};

    static constexpr auto f64_1 = element_type_info<double, 1>{};
    static constexpr auto f64_2 = element_type_info<double, 2>{};
    static constexpr auto f64_3 = element_type_info<double, 3>{};
    static constexpr auto f64_4 = element_type_info<double, 4>{};

    element_type_name name;
    int count;
    std::size_t size;
};

inline constexpr auto operator==(const element_type &lhs, const element_type &rhs) noexcept -> bool
{
    return lhs.name == rhs.name && lhs.count == rhs.count && lhs.size == rhs.size;
}

inline constexpr auto operator!=(const element_type &lhs, const element_type &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::common
