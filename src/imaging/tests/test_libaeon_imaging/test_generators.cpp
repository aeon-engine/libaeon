// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/imaging/generators/simplex_noise.h>
#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/imaging/filters/resize.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/image.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_image_generator_perlin_noise)
{
    const imaging::image_descriptor<float> d{128, 128};
    imaging::image image{d};

    imaging::generators::simplex_noise(image, 4.0f, 0.2f, 0.05f);

    const auto rgb_image = imaging::convert::to_rgb24(image);

    imaging::file::png::save(rgb_image, "test_image_generator_perlin_noise.png");
}

TEST(test_imaging, test_image_generator_scale_perlin_noise)
{
    const imaging::image_descriptor<float> d{128, 128};
    imaging::image image{d};

    imaging::generators::simplex_noise(image, 4.0f, 0.2f, 0.05f);
    image = imaging::filters::resize_bilinear(image, {250, 500});

    const auto rgb_image = imaging::convert::to_rgb24(image);

    imaging::file::png::save(rgb_image, "test_image_generator_perlin_noise_scaled.png");
}
