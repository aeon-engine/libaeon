// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>

namespace aeon::imaging::convert
{

template <typename T>
inline auto remove_stride(const image_view<T> &img) -> image<T>
{
    const image_descriptor<T> d{width(img), height(img)};
    image<T> new_image{d};

    const auto src_data = img.template data<std::uint8_t>();
    const auto dst_data = new_image.template data<std::uint8_t>();

    for (auto y = 0; y < height(img); ++y)
    {
        const auto offset = y * stride_y(img);
        const auto src_scanline = &src_data[offset];
        const auto src_scanline_end = &src_data[offset + width(img) * stride_x(img)];

        const auto dst_offset = y * stride_y(new_image);
        const auto dst_scanline = &dst_data[dst_offset];

        std::copy(src_scanline, src_scanline_end, dst_scanline);
    }

    return new_image;
}

inline auto remove_stride(const dynamic_image &img) -> dynamic_image
{
    return process_image_to_copy(img, remove_stride);
}

} // namespace aeon::imaging::convert
