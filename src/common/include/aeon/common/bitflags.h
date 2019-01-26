// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <cstdint>
#include <limits>

namespace aeon::common
{

template <typename T>
inline static constexpr auto get_bit(const T val, const unsigned int bit) noexcept
{
    return ((val & (1 << bit)) >> bit);
}

template <typename T>
inline static constexpr auto get_bit_range(const T val, const unsigned int offset, const unsigned int length) noexcept
{
    return ((val & (((1 << length) - 1) << offset)) >> offset);
}

template <typename T>
inline static constexpr void set_bit(T &val, const unsigned int bit) noexcept
{
    val |= (1 << bit);
}

template <typename T>
inline static constexpr void clear_bit(T &val, const unsigned int bit) noexcept
{
    val &= (val & ~(1 << bit));
}

template <typename T>
inline static constexpr void set_bit_flag(T &val, const T flag) noexcept
{
    val |= flag;
}

template <typename T>
inline static constexpr void clear_bit_flag(T &val, const T flag) noexcept
{
    val &= (val & (~flag));
}

template <typename T>
inline static constexpr auto check_bit_flag(const T value, const T flag) noexcept
{
    return (value & flag) == flag;
}

inline static constexpr auto get_low_nibble(const unsigned char value) noexcept
{
    return static_cast<unsigned char>(value & 0x0F);
}

inline static constexpr auto get_high_nibble(const unsigned char value) noexcept
{
    return static_cast<unsigned char>((value & 0xF0) >> 4);
}

template <typename T, typename U>
inline static constexpr auto mask(const U value) noexcept
{
    return static_cast<T>(value & std::numeric_limits<T>::max());
}

template <typename T>
inline static constexpr auto mask_u8(const T value) noexcept
{
    return mask<std::uint8_t>(value);
}

template <typename T>
inline static constexpr auto mask_u16(const T value) noexcept
{
    return mask<std::uint16_t>(value);
}

template <typename T>
inline static constexpr auto mask_u32(const T value) noexcept
{
    return mask<std::uint32_t>(value);
}

template <typename T>
inline static constexpr auto mask_u64(const T value) noexcept
{
    return mask<std::uint64_t>(value);
}

} // namespace aeon::common
