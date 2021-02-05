// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding_traits.h>
#include <aeon/common/assert.h>

namespace aeon::imaging
{

inline dynamic_image_descriptor::dynamic_image_descriptor() noexcept
    : dynamic_image_descriptor{pixel_encoding::unsigned8, {0, 0}, 0}
{
}

inline dynamic_image_descriptor::dynamic_image_descriptor(const pixel_encoding encoding,
                                                          const math::size2d<dimension> dimensions) noexcept
    : dynamic_image_descriptor{encoding, dimensions,
                               static_cast<std::ptrdiff_t>(math::width(dimensions) * bytes_per_pixel(encoding))}
{
}

inline dynamic_image_descriptor::dynamic_image_descriptor(const pixel_encoding encoding, const dimension width,
                                                          const dimension height) noexcept
    : dynamic_image_descriptor{encoding,
                               {width, height},
                               static_cast<std::ptrdiff_t>(width * bytes_per_pixel(encoding))}
{
}

inline dynamic_image_descriptor::dynamic_image_descriptor(const pixel_encoding encoding,
                                                          const math::size2d<dimension> dimensions,
                                                          const std::ptrdiff_t stride) noexcept
    : encoding_{encoding}
    , dimensions_{dimensions}
    , stride_{stride}
{
}

template <typename T>
inline dynamic_image_descriptor::dynamic_image_descriptor(const image_descriptor<T> &descriptor) noexcept
    : encoding_{pixel_encoding_trait<T>::encoding()}
    , dimensions_{imaging::dimensions(descriptor)}
    , stride_{imaging::stride(descriptor)}
{
}

inline dynamic_image_descriptor::~dynamic_image_descriptor() = default;

[[nodiscard]] inline auto dynamic_image_descriptor::encoding() const noexcept -> pixel_encoding
{
    return encoding_;
}

[[nodiscard]] inline auto dynamic_image_descriptor::width() const noexcept -> dimension
{
    return math::width(dimensions_);
}

[[nodiscard]] inline auto dynamic_image_descriptor::height() const noexcept -> dimension
{
    return math::height(dimensions_);
}

[[nodiscard]] inline auto dynamic_image_descriptor::dimensions() const noexcept -> math::size2d<dimension>
{
    return dimensions_;
}

[[nodiscard]] inline auto dynamic_image_descriptor::stride() const noexcept -> std::ptrdiff_t
{
    return stride_;
}

[[nodiscard]] inline auto null(const dynamic_image_descriptor &descriptor) noexcept -> bool
{
    return stride(descriptor) == 0 && math::null(dimensions(descriptor));
}

[[nodiscard]] inline auto valid(const dynamic_image_descriptor &descriptor) noexcept -> bool
{
    return !null(descriptor);
}

[[nodiscard]] inline auto encoding(const dynamic_image_descriptor &descriptor) noexcept -> pixel_encoding
{
    return descriptor.encoding();
}

[[nodiscard]] inline auto width(const dynamic_image_descriptor &descriptor) noexcept -> dimension
{
    return descriptor.width();
}

[[nodiscard]] inline auto height(const dynamic_image_descriptor &descriptor) noexcept -> dimension
{
    return descriptor.height();
}

[[nodiscard]] inline auto dimensions(const dynamic_image_descriptor &descriptor) noexcept -> math::size2d<dimension>
{
    return descriptor.dimensions();
}

[[nodiscard]] inline auto rectangle(const dynamic_image_descriptor &descriptor) noexcept -> math::rectangle<dimension>
{
    return math::rect(dimensions(descriptor));
}

[[nodiscard]] inline auto stride(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t
{
    return descriptor.stride();
}

[[nodiscard]] inline auto continuous(const dynamic_image_descriptor &descriptor) noexcept -> bool
{
    return stride(descriptor) == bytes_per_pixel(encoding(descriptor)) * width(descriptor);
}

[[nodiscard]] inline auto contains(const dynamic_image_descriptor &descriptor,
                                   const math::vector2<dimension> coord) noexcept -> bool
{
    return math::contains(coord, dimensions(descriptor));
}

[[nodiscard]] inline auto at_offset(const math::vector2<dimension> coord,
                                    const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t
{
    return stride(descriptor) * coord.y + bytes_per_pixel(encoding(descriptor)) * coord.x;
}

[[nodiscard]] inline auto size(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t
{
    return stride(descriptor) * height(descriptor);
}

template <typename T>
[[nodiscard]] inline auto descriptor(const dynamic_image_descriptor &descriptor) noexcept -> image_descriptor<T>
{
    aeon_assert(encoding(descriptor) == pixel_encoding_trait<T>::encoding(), "Encoding mismatch.");
    return image_descriptor<T>{dimensions(descriptor), stride(descriptor)};
}

inline auto operator==(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept -> bool
{
    return encoding(lhs) == encoding(rhs) && dimensions(lhs) == dimensions(rhs) && stride(lhs) == stride(rhs);
}

inline auto operator!=(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::imaging
