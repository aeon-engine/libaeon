// Distributed under the BSD 2-Clause License - Copyright 2019-2021 Robin Degen

#pragma once

#include <aeon/common/element_type.h>
#include <cstdlib>

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

[[nodiscard]] constexpr auto to_element_type(const format format) noexcept -> common::element_type
{
    switch (format)
    {
        case format::b8g8r8_uint:
            return common::element_type::u8_3;
        case format::b8g8r8a8_uint:
            return common::element_type::u8_4;
        case format::r32_float:
            return common::element_type::f32_1;
        case format::r32_uint:
            return common::element_type::u32_1;
        case format::r32g32_float:
            return common::element_type::f32_2;
        case format::r32g32_uint:
            return common::element_type::u32_2;
        case format::r32g32b32_float:
            return common::element_type::f32_3;
        case format::r32g32b32_uint:
            return common::element_type::u32_3;
        case format::r32g32b32a32_float:
            return common::element_type::f32_4;
        case format::r32g32b32a32_uint:
            return common::element_type::u32_4;
        case format::r8_uint:
            return common::element_type::u8_1;
        case format::r8g8_uint:
            return common::element_type::u8_2;
        case format::r8g8b8_uint:
            return common::element_type::u8_3;
        case format::r8g8b8a8_uint:
            return common::element_type::u8_4;
        case format::undefined:
        case format::bc1_rgb_srgb_block:
        case format::bc1_rgba_srgb_block:
        case format::bc2_srgb_block:
        case format::bc3_srgb_block:
            return common::element_type::undefined;
        default:
            std::abort();
    }
}

} // namespace aeon::imaging
