// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <cstddef>

namespace aeon::imaging
{

/*!
 * Base class for image. This is mainly used to have a common base for images
 * of different templated pixel types.
 */
class image_base
{
public:
    virtual ~image_base() = default;

    image_base(const image_base &) = delete;
    auto operator=(const image_base &) -> image_base & = delete;

    image_base(image_base &&) noexcept = default;
    auto operator=(image_base &&) noexcept -> image_base & = default;

    [[nodiscard]] virtual auto raw_data() noexcept -> std::byte * = 0;
    [[nodiscard]] virtual auto raw_data() const noexcept -> const std::byte * = 0;

protected:
    image_base() = default;
};

} // namespace aeon::imaging
