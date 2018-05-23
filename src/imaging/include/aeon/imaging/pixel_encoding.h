/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/imaging/dimension.h>
#include <aeon/common/compilers.h>
#include <cstddef>

namespace aeon::imaging
{

AEON_PACK_STRUCT_PUSH(1)
struct rgb24
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
} AEON_PACK_STRUCT_POP(1);

AEON_PACK_STRUCT_PUSH(1)
struct rgba32
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 0;
} AEON_PACK_STRUCT_POP(1);

AEON_PACK_STRUCT_PUSH(1)
struct bgr24
{
    std::uint8_t b = 0;
    std::uint8_t g = 0;
    std::uint8_t r = 0;
} AEON_PACK_STRUCT_POP(1);

enum class pixel_encoding
{
    unsigned8,
    unsigned16,
    unsigned32,
    float32,
    rgb24,
    rgba32,
    bgr24
};

static constexpr std::ptrdiff_t bytes_per_pixel_lookup[]{
    sizeof(std::uint8_t),  // unsigned8
    sizeof(std::uint16_t), // unsigned16
    sizeof(std::uint32_t), // unsigned32
    sizeof(float),         // float32
    sizeof(rgb24),         // rgb24
    sizeof(rgba32),        // rgba32
    sizeof(bgr24),         // bgr24
};

// Detect possible mismatch between the encoding enum and the lookup table.
static_assert(sizeof(bytes_per_pixel_lookup) / sizeof(bytes_per_pixel_lookup[0]) ==
              static_cast<unsigned long long>(pixel_encoding::bgr24) + 1);

constexpr auto bytes_per_pixel(const pixel_encoding encoding) noexcept
{
    return bytes_per_pixel_lookup[static_cast<unsigned int>(encoding)];
}

} // namespace aeon::imaging
