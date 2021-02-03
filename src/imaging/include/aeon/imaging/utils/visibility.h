// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/pixel_math.h>

namespace aeon::imaging::utils
{

template <typename T>
[[nodiscard]] inline auto is_full_alpha(image_view<T> &img) -> bool
{
    if constexpr (std::is_same_v<T, bgra32> || std::is_same_v<T, rgba32>)
    {
        const auto w = imaging::width(img);
        const auto h = imaging::height(img);

        for (auto y = 0; y < h; ++y)
        {
            for (auto x = 0; x < w; ++x)
            {
                if (pixel_math<T>::alpha(img.at({x, y})) != pixel_math<T>::min())
                    return false;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

[[nodiscard]] inline auto is_full_alpha(dynamic_image &img) -> bool
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
        case pixel_encoding::unsigned16:
        case pixel_encoding::unsigned32:
        case pixel_encoding::float32:
        case pixel_encoding::rgb24:
        case pixel_encoding::bgr24:
            return false;
        case pixel_encoding::rgba32:
            return is_full_alpha(view<rgba32>(img));
        case pixel_encoding::bgra32:
            return is_full_alpha(view<bgra32>(img));
        default:
            throw imaging_exception{};
    }
}

} // namespace aeon::imaging::utils
