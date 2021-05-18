// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

namespace aeon::imaging
{

enum class format
{
    undefined,
    b8g8r8_uint,
    b8g8r8a8_uint,
    bc1_rgb_srgb_block,  // DXT1
    bc1_rgba_srgb_block, // DXT1
    bc2_srgb_block,      // DXT3
    bc3_srgb_block,      // DXT5
    r32_float,
    r32_uint,
    r32g32_float,
    r32g32_uint,
    r32g32b32_float,
    r32g32b32_uint,
    r32g32b32a32_float,
    r32g32b32a32_uint,
    r8_uint,
    r8g8_uint,
    r8g8b8_uint,
    r8g8b8a8_uint,
};

} // namespace aeon::imaging
