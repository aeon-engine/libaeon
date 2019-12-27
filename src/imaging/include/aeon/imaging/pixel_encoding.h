// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/dimension.h>
#include <aeon/common/compilers.h>

namespace aeon::imaging
{

AEON_PACK_STRUCT_PUSH(1)
struct rgb24
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(rgb24) == 3, "Alignment problem: rgb24 must be 3 bytes in size.");

AEON_PACK_STRUCT_PUSH(1)
struct rgba32
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(rgba32) == 4, "Alignment problem: rgba32 must be 4 bytes in size.");

AEON_PACK_STRUCT_PUSH(1)
struct bgr24
{
    std::uint8_t b = 0;
    std::uint8_t g = 0;
    std::uint8_t r = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(bgr24) == 3, "Alignment problem: bgr24 must be 3 bytes in size.");

AEON_PACK_STRUCT_PUSH(1)
struct bgra32
{
    std::uint8_t b = 0;
    std::uint8_t g = 0;
    std::uint8_t r = 0;
    std::uint8_t a = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(bgra32) == 4, "Alignment problem: bgra32 must be 4 bytes in size.");

enum class pixel_encoding : std::uint32_t
{
    unsigned8 = 0,
    unsigned16 = 1,
    unsigned32 = 2,
    float32 = 3,
    rgb24 = 4,
    rgba32 = 5,
    bgr24 = 6,
    bgra32 = 7
};

inline auto operator*(const rgb24 lhs, const float rhs) noexcept -> rgb24;
inline auto operator*=(rgb24 &lhs, const float rhs) noexcept -> rgb24;
inline auto operator*(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator*=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator+(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator+=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator-(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator-=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24;
inline auto operator==(const rgb24 lhs, const rgb24 rhs) noexcept -> bool;
inline auto operator!=(const rgb24 lhs, const rgb24 rhs) noexcept -> bool;

inline auto operator*(const rgba32 lhs, const float rhs) noexcept -> rgba32;
inline auto operator*=(rgba32 &lhs, const float rhs) noexcept -> rgba32;
inline auto operator*(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator*=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator+(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator+=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator-(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator-=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32;
inline auto operator==(const rgba32 lhs, const rgba32 rhs) noexcept -> bool;
inline auto operator!=(const rgba32 lhs, const rgba32 rhs) noexcept -> bool;

inline auto operator*(const bgr24 lhs, const float rhs) noexcept -> bgr24;
inline auto operator*=(bgr24 &lhs, const float rhs) noexcept -> bgr24;
inline auto operator*(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator*=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator+(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator+=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator-(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator-=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24;
inline auto operator==(const bgr24 lhs, const bgr24 rhs) noexcept -> bool;
inline auto operator!=(const bgr24 lhs, const bgr24 rhs) noexcept -> bool;

inline auto operator*(const bgra32 lhs, const float rhs) noexcept -> bgra32;
inline auto operator*=(bgra32 &lhs, const float rhs) noexcept -> bgra32;
inline auto operator*(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator*=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator+(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator+=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator-(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator-=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32;
inline auto operator==(const bgra32 lhs, const bgra32 rhs) noexcept -> bool;
inline auto operator!=(const bgra32 lhs, const bgra32 rhs) noexcept -> bool;

} // namespace aeon::imaging

#include <aeon/imaging/impl/pixel_encoding_impl.h>
