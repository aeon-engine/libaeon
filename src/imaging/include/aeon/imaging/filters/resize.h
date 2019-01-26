// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>

namespace aeon::imaging::filters
{

template <typename T>
inline auto resize_bilinear(const image_view<T> &img, const math::size2d<dimension> size) -> image<T>
{
    image new_image(image_descriptor<T>{size});
    const auto dst = new_image.data();

    const float x_ratio = static_cast<float>(width(img) - 1) / width(size);
    const float y_ratio = static_cast<float>(height(img) - 1) / height(size);
    auto offset = 0;
    for (auto i = 0; i < height(size); ++i)
    {
        for (auto j = 0; j < width(size); ++j)
        {
            const auto x = static_cast<int>(x_ratio * j);
            const auto y = static_cast<int>(y_ratio * i);
            const auto x_diff = (x_ratio * j) - x;
            const auto y_diff = (y_ratio * i) - y;

            const auto &A = img.at({x, y});
            const auto &B = img.at({x + 1, y});
            const auto &C = img.at({x, y + 1});
            const auto &D = img.at({x + 1, y + 1});

            // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
            dst[offset++] = static_cast<T>((A * (1.0f - x_diff) * (1.0f - y_diff)) + (B * (x_diff) * (1.0f - y_diff)) +
                                           (C * (y_diff) * (1.0f - x_diff)) + (D * (x_diff * y_diff)));
        }
    }

    return new_image;
}

inline auto resize_bilinear(const dynamic_image &img, const math::size2d<dimension> size) -> dynamic_image
{
    return process_image_to_copy(img, resize_bilinear, size);
}

} // namespace aeon::imaging::filters
