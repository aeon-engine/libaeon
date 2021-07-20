// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/math/rectangle.h>
#include <aeon/common/container.h>
#include <numeric>
#include <tuple>
#include <stdexcept>
#include <vector>

namespace aeon::imaging::utils
{

namespace internal
{

[[nodiscard]] inline auto determine_atlas(const std::vector<image_view> &images,
                                          const std::vector<std::size_t> &indices,
                                          std::vector<math::rectangle<image::dimensions_type>> &rectangles,
                                          const math::size2d<image::dimensions_type> minimum_distance,
                                          const math::size2d<image::dimensions_type> destination_dimensions) -> bool
{
    image::dimensions_type x_offset = 0;
    std::vector<image::dimensions_type> y_positions(math::width(destination_dimensions), 0);

    for (const auto index : indices)
    {
        const auto &img = images[index];

        if (!math::contains(math::rectangle{0, 0, math::dimensions(img)},
                            math::rectangle{0, 0, destination_dimensions}))
            return false;

        if (x_offset + math::width(img) + math::width(minimum_distance) >= math::width(destination_dimensions))
            x_offset = 0;

        auto y_offset = 0;
        for (auto i = 0; i < math::width(img) + math::width(minimum_distance); ++i)
        {
            const auto value = y_positions[x_offset + i];
            if (value > y_offset)
                y_offset = value;
        }

        const auto position = math::vector2<image::dimensions_type>{x_offset, y_offset};

        if (!math::contains(math::translated(math::rectangle{0, 0, math::dimensions(img)}, position),
                            math::rectangle{0, 0, destination_dimensions}))
            return false;

        rectangles[index] = {position, math::dimensions(img)};

        for (auto i = 0; i < math::width(img) + math::width(minimum_distance); ++i)
        {
            y_positions[x_offset + i] = y_offset + math::height(img) + math::height(minimum_distance);
        }

        x_offset += math::width(img) + math::width(minimum_distance);
    }

    return true;
}

} // namespace internal

struct atlas_result
{
    image img;
    std::vector<math::rectangle<image::dimensions_type>> positions;
};

[[nodiscard]] inline auto create_atlas(const std::vector<image_view> &images,
                                       const math::size2d<image::dimensions_type> minimum_distance = {1, 1},
                                       const math::size2d<image::dimensions_type> initial_dimensions = {128, 128})
    -> atlas_result
{
    if (std::empty(images))
        throw std::invalid_argument{"No images given"};

    std::vector<std::size_t> indices(std::size(images));
    std::iota(std::begin(indices), std::end(indices), 0);

    std::ranges::sort(indices,
                      [&images](const auto lhs, const auto rhs)
                      {
                          const auto lhs_dimensions = math::dimensions(images[lhs]);
                          const auto rhs_dimensions = math::dimensions(images[rhs]);

                          return std::tie(rhs_dimensions.height, lhs_dimensions.width) <
                                 std::tie(lhs_dimensions.height, rhs_dimensions.width);
                      });

    const auto element_type = math::element_type(images[0]);
    const auto format = imaging::pixel_format(images[0]);

    atlas_result result;
    result.positions.resize(std::size(images));

    auto dimensions = initial_dimensions;

    while (!internal::determine_atlas(images, indices, result.positions, minimum_distance, dimensions))
    {
        dimensions *= 2;
    }

    result.img = image{element_type, format, dimensions};

    for (auto i = 0ull; i < std::size(images); ++i)
    {
        const auto &source_image = images[i];
        if (element_type != math::element_type(source_image) || format != imaging::pixel_format(source_image))
            throw std::invalid_argument{"Image format mismatch."};

        math::blit(source_image, result.img, math::left_top(result.positions[i]));
    }

    return result;
}

[[nodiscard]] inline auto create_atlas(const std::vector<image> &images,
                                       const math::size2d<image::dimensions_type> minimum_distance = {1, 1},
                                       const math::size2d<image::dimensions_type> initial_dimensions = {128, 128})
{
    const auto image_views = common::container::auto_transform<image_view>(images);
    return create_atlas(image_views, minimum_distance, initial_dimensions);
}

} // namespace aeon::imaging::utils
