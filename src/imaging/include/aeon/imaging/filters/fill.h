// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/math/rectangle.h>

namespace aeon::imaging::filters
{

template <typename T>
inline void fill(image_view<T> &img, const T color)
{
    const auto w = imaging::width(img);
    const auto h = imaging::height(img);

    for (auto y = 0; y < h; ++y)
    {
        for (auto x = 0; x < w; ++x)
        {
            img.at({x, y}) = color;
        }
    }
}

template <typename T>
inline void fill(dynamic_image &img, const T color)
{
    process_image(img, fill, color);
}

template <typename T>
inline void fill(image_view<T> &img, const math::rectangle<dimension> rect, const T color)
{
    aeon_assert(math::contains(rect, rectangle(img)), "Rectangle does not fit within image.");

    for (auto y = math::top(rect); y < math::bottom(rect); ++y)
    {
        for (auto x = math::left(rect); x < math::right(rect); ++x)
        {
            img.at({x, y}) = color;
        }
    }
}

template <typename T>
inline void fill(dynamic_image &img, const math::rectangle<dimension> rect, const T color)
{
    process_image(img, fill, rect, color);
}

} // namespace aeon::imaging::filters
