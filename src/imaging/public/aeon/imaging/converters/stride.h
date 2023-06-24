// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/imaging/image.h>

namespace aeon::imaging::convert
{

[[nodiscard]] inline auto remove_stride(const image_view &img) -> image
{
    const auto element_type = math::element_type(img);
    image new_image{element_type, pixel_format(img), math::dimensions(img)};

    const auto *const src_data = std::data(img);
    auto *const dst_data = std::data(new_image);

    for (auto y = 0; y < height(img); ++y)
    {
        const auto offset = y * stride(img);
        const auto *const src_scanline = &src_data[offset];
        const auto *const src_scanline_end = &src_data[offset + width(img) * element_type.size];

        const auto dst_offset = y * stride(new_image);
        auto *const dst_scanline = &dst_data[dst_offset];

        std::copy(src_scanline, src_scanline_end, dst_scanline);
    }

    return new_image;
}

} // namespace aeon::imaging::convert
