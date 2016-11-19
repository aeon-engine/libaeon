/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{

template <typename T>
inline static auto get_bit(T val, unsigned int bit)
{
    return ((val & (1 << bit)) >> bit);
}

template <typename T>
inline static auto get_bit_range(T val, unsigned int offset, unsigned int length)
{
    return ((val & (((1 << length) - 1) << offset)) >> offset);
}

template <typename T>
inline static void set_bit(T &val, unsigned int bit)
{
    val |= (1 << bit);
}

template <typename T>
inline static void clear_bit(T &val, unsigned int bit)
{
    val &= (val & ~(1 << bit));
}

template <typename T>
inline static void set_bit_flag(T &val, T flag)
{
    val |= flag;
}

template <typename T>
inline static void clear_bit_flag(T &val, T flag)
{
    val &= (val & (~flag));
}

template <typename T>
inline static auto check_bit_flag(T value, T flag)
{
    return (value & flag) == flag;
}

inline static auto get_low_nibble(unsigned char value)
{
    return static_cast<unsigned char>(value & 0x0F);
}

inline static auto get_high_nibble(unsigned char value)
{
    return static_cast<unsigned char>((value & 0xF0) >> 4);
}

} // namespace utility
} // namespace aeon
