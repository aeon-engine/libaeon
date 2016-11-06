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
namespace endianness
{

template <typename T>
T swap16(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint16_t), "swap16 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint16_t>::type swap_type;

    swap_type swap =
        (((*(static_cast<swap_type *>(&val)) & 0x00FF) << 8) | ((*(static_cast<swap_type *>(&val)) & 0xFF00) >> 8));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap32(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint32_t), "swap32 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint32_t>::type swap_type;

    swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x000000FF) << 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000FF00) << 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00FF0000) >> 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0xFF000000) >> 24));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap64(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint64_t), "swap64 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint64_t>::type swap_type;

    swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00000000000000FFULL) << 56) |
                      ((*(static_cast<swap_type *>(&val)) & 0x000000000000FF00ULL) << 40) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000000000FF0000ULL) << 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00000000FF000000ULL) << 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x000000FF00000000ULL) >> 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000FF0000000000ULL) >> 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00FF000000000000ULL) >> 40) |
                      ((*(static_cast<swap_type *>(&val)) & 0xFF00000000000000ULL) >> 56));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap(T val)
{
    switch (sizeof(T))
    {
        case 1:
            return val;
        case 2:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint16_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00FF) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF00) >> 8));

            return *(static_cast<T *>(&swap));
        }
        case 4:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint32_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x000000FF) << 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000FF00) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00FF0000) >> 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF000000) >> 24));

            return *(static_cast<T *>(&swap));
        }
        case 8:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint64_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00000000000000FFULL) << 56) |
                              ((*(static_cast<swap_type *>(&val)) & 0x000000000000FF00ULL) << 40) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000000000FF0000ULL) << 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00000000FF000000ULL) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x000000FF00000000ULL) >> 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000FF0000000000ULL) >> 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00FF000000000000ULL) >> 40) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF00000000000000ULL) >> 56));

            return *(static_cast<T *>(&swap));
        }
        default:
            throw std::runtime_error("Unsupported type for endianness swap.");
    }

    throw std::runtime_error("Unsupported type for endianness swap.");
}

} // namespace endianness
} // namespace utility
} // namespace aeon
