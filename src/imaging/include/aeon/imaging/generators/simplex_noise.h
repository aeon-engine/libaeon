// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/math/simplex_noise.h>
#include <cassert>

namespace aeon::imaging::generators
{

inline void simplex_noise(image_view<float> &image_view, const float octaves, const float persistence,
                          const float scale) noexcept
{
    const auto image_width = width(image_view);
    const auto image_height = height(image_view);

    for (auto y = 0; y < image_height; ++y)
    {
        for (auto x = 0; x < image_width; ++x)
        {
            image_view.at({x, y}) = math::simplex_noise::scaled_octave_noise_2d(
                octaves, persistence, scale, 0.0f, 1.0f, static_cast<float>(x), static_cast<float>(y));
        }
    }
}

} // namespace aeon::imaging::generators
