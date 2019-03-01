// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/imaging/converters/convert_pixel.h>
#include <aeon/common/assert.h>

namespace aeon::imaging::convert
{

namespace internal
{

template <typename from_t, typename to_t>
[[nodiscard]] inline auto to_pixel_encoding(const image_view<from_t> &img, to_t (*converter)(const from_t))
    -> image<to_t>
{
    aeon_assert(!null(img), "Given image can not be null.");
    aeon_assert(continuous(img), "to_pixel_encoding only works on continuous images.");

    const image_descriptor<to_t> d{width(img), height(img)};
    image<to_t> new_image(d);

    const auto src_image_data = img.data();
    const auto new_image_data = new_image.data();

    const auto dims = width(img) * height(img);

    for (auto i = 0; i < dims; ++i)
    {
        new_image_data[i] = converter(src_image_data[i]);
    }

    return new_image;
}

} // namespace internal

class convert_exception : public imaging_exception
{
};

[[nodiscard]] auto to_rgb24(const dynamic_image &img) -> image<rgb24>;
[[nodiscard]] auto to_bgr24(const dynamic_image &img) -> image<bgr24>;
[[nodiscard]] auto to_rgba32(const dynamic_image &img) -> image<rgba32>;
[[nodiscard]] auto to_bgra32(const dynamic_image &img) -> image<bgra32>;

template <typename T>
[[nodiscard]] inline auto to_rgb24(const image_view<T> &img) -> image<rgb24>
{
    return internal::to_pixel_encoding<T, rgb24>(img, pixel<T>::to_rgb24);
}

template <typename T>
[[nodiscard]] inline auto to_bgr24(const image_view<T> &img) -> image<bgr24>
{
    return internal::to_pixel_encoding<T, bgr24>(img, pixel<T>::to_bgr24);
}

template <typename T>
[[nodiscard]] inline auto to_rgba32(const image_view<T> &img) -> image<rgba32>
{
    return internal::to_pixel_encoding<T, rgba32>(img, pixel<T>::to_rgba32);
}

template <typename T>
[[nodiscard]] inline auto to_bgra32(const image_view<T> &img) -> image<bgra32>
{
    return internal::to_pixel_encoding<T, bgra32>(img, pixel<T>::to_bgra32);
}

} // namespace aeon::imaging::convert
