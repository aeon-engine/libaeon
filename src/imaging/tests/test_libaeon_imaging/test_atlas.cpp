// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/utils/atlas.h>
#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/common/container.h>
#include <gtest/gtest.h>
#include <random>
#include <vector>

using namespace aeon;

TEST(test_imaging, test_atlas)
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> size_dist(10, 100);
    std::uniform_int_distribution<> pixel_dist(0, 255);

    const auto image_count = 200;

    std::vector<imaging::image> images;
    images.reserve(image_count);

    for (auto i = 0; i < image_count; ++i)
    {
        const math::size2d<imaging::image::dimensions_type> size{size_dist(gen), size_dist(gen)};
        imaging::image image{imaging::format::r8g8b8_uint, size};
        math::fill(image, imaging::rgb24{static_cast<std::uint8_t>(pixel_dist(gen)),
                                         static_cast<std::uint8_t>(pixel_dist(gen)),
                                         static_cast<std::uint8_t>(pixel_dist(gen))});
        images.push_back(std::move(image));
    }

    const auto result = imaging::utils::create_atlas(images);

    // Verify if none of the rectangles overlap
    for (auto i = 0ull; i < std::size(result.positions); ++i)
    {
        for (auto j = 0ull; j < std::size(result.positions); ++j)
        {
            if (i == j)
                continue;

            ASSERT_FALSE(math::overlaps(result.positions[i], result.positions[j]));
        }
    }

    imaging::file::png::save(result.img, "atlas.png");
}
