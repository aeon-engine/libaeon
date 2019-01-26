// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/bitflags.h>
#include <aeon/common/assert.h>
#include <array>

namespace aeon::common::utf8
{

namespace internal
{

constexpr std::array<std::uint8_t, 3> bom_signature{0xef, 0xbb, 0xbf};

inline constexpr auto is_1byte_codepoint(const std::uint8_t c) noexcept
{
    return c < 0x80;
}

inline constexpr auto is_2byte_codepoint(const std::uint8_t c) noexcept
{
    return get_bit_range(c, 5, 3) == 0b110;
}

inline constexpr auto is_3byte_codepoint(const std::uint8_t c) noexcept
{
    return get_bit_range(c, 4, 4) == 0b1110;
}

inline constexpr auto is_4byte_codepoint(const std::uint8_t c) noexcept
{
    return get_bit_range(c, 3, 5) == 0b11110;
}

template <typename iterator_t>
inline auto itr_checked_next(const iterator_t itr, const iterator_t end)
{
    if (itr == end)
        throw utf8_exception{};

    return std::next(itr);
}

} // namespace internal

inline auto bom() -> std::string
{
    return std::string{std::begin(internal::bom_signature), std::end(internal::bom_signature)};
}

template <typename iterator_t>
inline auto has_bom(const iterator_t itr, const iterator_t end)
{
    if (std::distance(itr, end) < 3)
        return false;

    auto i = itr;

    return (((itr != end) && (mask_u8(*i++)) == internal::bom_signature[0]) &&
            ((itr != end) && (mask_u8(*i++)) == internal::bom_signature[1]) &&
            ((itr != end) && (mask_u8(*i)) == internal::bom_signature[2]));
}

inline auto has_bom(const std::string &str)
{
    return has_bom(std::begin(str), std::end(str));
}

template <typename iterator_t>
inline auto skip_bom(iterator_t itr, const iterator_t end)
{
    if (!has_bom(itr, end))
        return itr;

    aeon_assert(std::distance(itr, end) >= 3, "Out of bounds.");

    std::advance(itr, 3);
    return itr;
}

inline auto strip_bom(std::string &str)
{
    if (str.size() < 3)
        return;

    if (!has_bom(std::begin(str), std::end(str)))
        return;

    string::strip_left(str, internal::bom_signature.size());
}

template <typename iterator_t>
inline auto codepoint_length(const iterator_t itr) noexcept
{
    const auto c = mask_u8(*itr);

    if (internal::is_1byte_codepoint(c))
        return 1;

    if (internal::is_2byte_codepoint(c))
        return 2;

    if (internal::is_3byte_codepoint(c))
        return 3;

    if (internal::is_4byte_codepoint(c))
        return 4;

    return 0;
}

template <typename iterator_t>
inline void advance_to_next_codepoint(iterator_t &itr, const iterator_t end) noexcept
{
    aeon_assert(itr != end, "End of range.");
    const auto length = codepoint_length(itr);
    aeon_assert(std::distance(itr, end) >= length, "Out of bounds.");
    std::advance(itr, length);
}

template <typename iterator_t>
inline auto read_codepoint(const iterator_t itr, const iterator_t end, char32_t &value)
{
    aeon_assert(itr != end, "End of range.");

    auto i = itr;

    if (i == end)
        throw utf8_exception{};

    const auto c1 = mask_u8(*i);

    if (internal::is_1byte_codepoint(c1))
    {
        value = c1;
        return std::next(i);
    }

    i = internal::itr_checked_next(i, end);
    const auto c2 = mask_u8(*i);

    if (internal::is_2byte_codepoint(c1))
    {
        value = get_bit_range(c2, 0, 6) | get_bit_range(c1, 0, 5) << 6;
        return std::next(i);
    }

    i = internal::itr_checked_next(i, end);
    const auto c3 = mask_u8(*i);

    if (internal::is_3byte_codepoint(c1))
    {
        value = get_bit_range(c3, 0, 6) | get_bit_range(c2, 0, 6) << 6 | get_bit_range(c1, 0, 4) << 12;
        return std::next(i);
    }

    i = internal::itr_checked_next(i, end);
    const auto c4 = mask_u8(*i);

    if (internal::is_4byte_codepoint(c1))
    {
        value = get_bit_range(c4, 0, 6) | get_bit_range(c3, 0, 6) << 6 | get_bit_range(c2, 0, 6) << 12 |
                get_bit_range(c1, 0, 3) << 18;
        return std::next(i);
    }

    throw utf8_exception{};
}

template <typename iterator_t>
inline auto utf8_strlen(const iterator_t itr, const iterator_t end) -> std::size_t
{
    auto i = itr;

    std::size_t length = 0u;
    while (i != end)
    {
        auto prev_itr = i;
        advance_to_next_codepoint(i, end);
        aeon_assert(i != prev_itr, "UTF-8 encoding error. Infinite loop detected.");
        ++length;
    }

    return length;
}

inline auto utf8_strlen(const std::string &str) -> std::size_t
{
    return utf8_strlen(std::begin(str), std::end(str));
}

inline auto utf8_strlensv(const std::string_view &str) -> std::size_t
{
    return utf8_strlen(std::begin(str), std::end(str));
}

template <typename iterator_t>
inline auto utf8_append(iterator_t itr, const char32_t c) -> iterator_t
{
    if (c < 0x80)
    {
        *(itr++) = mask_u8(c);
    }
    else if (c < 0x800)
    {
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 6, 5) | 0xc0);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 0, 6) | 0x80);
    }
    else if (c < 0x10000)
    {
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 12, 4) | 0xe0);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 6, 6) | 0x80);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 0, 6) | 0x80);
    }
    else
    {
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 18, 3) | 0xf0);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 12, 6) | 0x80);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 6, 6) | 0x80);
        *(itr++) = static_cast<std::uint8_t>(get_bit_range(c, 0, 6) | 0x80);
    }

    return itr;
}

inline void utf8_append(std::string &str, const char32_t c)
{
    utf8_append(std::back_inserter(str), c);
}

inline auto codepoint_to_string(const char32_t c) -> std::string
{
    std::string result;
    utf8_append(result, c);
    return result;
}

} // namespace aeon::common::utf8
