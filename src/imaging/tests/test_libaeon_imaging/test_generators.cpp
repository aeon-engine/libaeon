// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/image.h>
#include <aeon/math/simplex_noise.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_image_generator_simplex_noise)
{
    imaging::image image{common::element_type::u8_1, imaging::pixel_encoding::monochrome, 128, 128};
    math::simplex_noise::scaled_octave_noise(image, 4.0f, 0.2f, 0.05f);
    const auto rgb_image = imaging::convert::to_rgb_copy(image);
    imaging::file::png::save(rgb_image, "test_image_generator_simplex_noise.png");
}
