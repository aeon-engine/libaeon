// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>

namespace aeon::imaging::filters
{

namespace detail
{

template <typename T>
struct resize_bilinear_impl
{
    static auto process(const image_view &img, const common::element_type element_type,
                        const math::size2d<image::dimensions_type> size) -> image
    {
        const auto source_stride = math::stride(img);
        image new_image{element_type, pixel_format(img), size};
        const auto dest_stride = math::stride(new_image);

        const auto *const src = std::data(img);
        auto *const dst = std::data(new_image);

        const float x_ratio = static_cast<float>(width(img) - 1) / static_cast<float>(width(size));
        const float y_ratio = static_cast<float>(height(img) - 1) / static_cast<float>(height(size));

        for (auto i = 0; i < height(size); ++i)
        {
            for (auto j = 0; j < width(size); ++j)
            {
                const auto x = static_cast<int>(x_ratio * j);
                const auto y = static_cast<int>(y_ratio * i);
                const auto x_diff = (x_ratio * j) - x;
                const auto y_diff = (y_ratio * i) - y;

                const auto A = *reinterpret_cast<const T *>(src + common::offset_of(element_type, source_stride, x, y));
                const auto B =
                    *reinterpret_cast<const T *>(src + common::offset_of(element_type, source_stride, x + 1, y));
                const auto C =
                    *reinterpret_cast<const T *>(src + common::offset_of(element_type, source_stride, x, y + 1));
                const auto D =
                    *reinterpret_cast<const T *>(src + common::offset_of(element_type, source_stride, x + 1, y + 1));

                // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
                *reinterpret_cast<T *>(dst + common::offset_of(element_type, dest_stride, j, i)) =
                    static_cast<T>(((A * (1.0f - x_diff) * (1.0f - y_diff)) + (B * (x_diff) * (1.0f - y_diff)) +
                                    (C * (y_diff) * (1.0f - x_diff)) + (D * (x_diff * y_diff))));
            }
        }

        return new_image;
    }
};

} // namespace detail

[[nodiscard]] inline auto resize_bilinear(const image_view &img, const math::size2d<image::dimensions_type> size)
    -> image
{
    const auto element_type = math::element_type(img);
    const auto format = pixel_format(img);

    if (element_type == common::element_type::u8_3 || element_type == common::element_type::u8_3_stride_4)
    {
        if (format == format::r8g8b8_uint)
            return detail::resize_bilinear_impl<rgb24>::process(img, element_type, size);
        else if (format == format::b8g8r8_uint)
            return detail::resize_bilinear_impl<bgr24>::process(img, element_type, size);
    }
    else if (element_type == common::element_type::u8_4)
    {
        if (format == format::r8g8b8a8_uint)
            return detail::resize_bilinear_impl<rgba32>::process(img, element_type, size);
        else if (format == format::b8g8r8a8_uint)
            return detail::resize_bilinear_impl<bgra32>::process(img, element_type, size);
    }
    else if (element_type == common::element_type::f32_1 || element_type == common::element_type::f32_1_stride_8)
    {
        return detail::resize_bilinear_impl<float>::process(img, element_type, size);
    }
    else if (element_type == common::element_type::f64_1)
    {
        return detail::resize_bilinear_impl<double>::process(img, element_type, size);
    }

    throw std::runtime_error{"Unsupported format."};
}

} // namespace aeon::imaging::filters
