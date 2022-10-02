// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/image.h>
#include <aeon/math/simplex_noise.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_image_generator_simplex_noise)
{
    imaging::image image{imaging::format::r8_uint, 128, 128};
    math::simplex_noise::scaled_octave_noise(image, 4.0f, 0.2f, 0.05f);
    const auto rgb_image =
        imaging::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r>(image, imaging::format::r8g8b8_uint);

    imaging::file::png::save(rgb_image, "test_image_generator_simplex_noise.png");
}
