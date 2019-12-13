// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding_traits.h>
#include <aeon/common/assert.h>
#include <cstdint>

namespace aeon::imaging
{

namespace internal
{

template <typename T>
[[nodiscard]] inline auto create_typed_image(const dynamic_image_descriptor &dynamic_descriptor)
    -> std::unique_ptr<image_base>
{
    return std::make_unique<image<T>>(descriptor<T>(dynamic_descriptor));
}

[[nodiscard]] inline auto create_image(const dynamic_image_descriptor &dynamic_descriptor)
    -> std::unique_ptr<image_base>
{
    switch (encoding(dynamic_descriptor))
    {
        case pixel_encoding::unsigned8:
            return internal::create_typed_image<std::uint8_t>(dynamic_descriptor);
        case pixel_encoding::unsigned16:
            return internal::create_typed_image<std::uint16_t>(dynamic_descriptor);
        case pixel_encoding::unsigned32:
            return internal::create_typed_image<std::uint32_t>(dynamic_descriptor);
        case pixel_encoding::float32:
            return internal::create_typed_image<float>(dynamic_descriptor);
        case pixel_encoding::rgb24:
            return internal::create_typed_image<rgb24>(dynamic_descriptor);
        case pixel_encoding::rgba32:
            return internal::create_typed_image<rgba32>(dynamic_descriptor);
        case pixel_encoding::bgr24:
            return internal::create_typed_image<bgr24>(dynamic_descriptor);
        case pixel_encoding::bgra32:
            return internal::create_typed_image<bgra32>(dynamic_descriptor);
        default:
            aeon_assert_fail("Unexpected encoding.");
            throw imaging_exception{};
    }
}

} // namespace internal

inline dynamic_image::dynamic_image(const dynamic_image_descriptor &dynamic_descriptor)
    : dynamic_descriptor_{dynamic_descriptor}
    , image_{internal::create_image(dynamic_descriptor)}
{
}

template <typename T>
inline dynamic_image::dynamic_image(image<T> &&image)
    : dynamic_descriptor_(image.descriptor())
    , image_{image.move_to_dynamic_image()}
{
}

template <typename T>
inline dynamic_image::dynamic_image(image_view<T> &&image)
    : dynamic_descriptor_(image.descriptor())
    , image_{std::make_unique<image_view<T>>{descriptor{image}, image.data()}}
{
}

template <typename T>
inline dynamic_image::dynamic_image(std::unique_ptr<image<T>> image)
    : dynamic_descriptor_(image.descriptor())
    , image_{std::move(image)}
{
}

template <typename T>
inline dynamic_image::dynamic_image(std::unique_ptr<image_view<T>> image)
    : dynamic_descriptor_(image.descriptor())
    , image_{std::move(image)}
{
}

inline dynamic_image::~dynamic_image() = default;

[[nodiscard]] inline auto dynamic_image::descriptor() const noexcept -> dynamic_image_descriptor
{
    return dynamic_descriptor_;
}

template <typename T>
[[nodiscard]] inline auto dynamic_image::get_image() noexcept -> imaging::image<T> &
{
    aeon_assert(pixel_encoding_trait<T>::encoding() == encoding(dynamic_descriptor_), "Encoding mismatch.");
    return *static_cast<image<T> *>(image_.get());
}

template <typename T>
[[nodiscard]] inline auto dynamic_image::get_image() const noexcept -> const imaging::image<T> &
{
    aeon_assert(pixel_encoding_trait<T>::encoding() == encoding(dynamic_descriptor_), "Encoding mismatch.");
    return *static_cast<const image<T> *>(image_.get());
}

[[nodiscard]] inline auto dynamic_image::raw_data() noexcept -> std::byte *
{
    return image_->raw_data();
}

[[nodiscard]] inline auto dynamic_image::raw_data() const noexcept -> const std::byte *
{
    return image_->raw_data();
}

[[nodiscard]] inline auto descriptor(const dynamic_image &image) noexcept -> dynamic_image_descriptor
{
    return image.descriptor();
}

[[nodiscard]] inline auto null(const dynamic_image &image) noexcept -> bool
{
    return null(descriptor(image));
}

[[nodiscard]] inline auto valid(const dynamic_image &image) noexcept -> bool
{
    return valid(descriptor(image));
}

[[nodiscard]] inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding
{
    return encoding(descriptor(image));
}

[[nodiscard]] inline auto width(const dynamic_image &image) noexcept -> dimension
{
    return width(descriptor(image));
}

[[nodiscard]] inline auto height(const dynamic_image &image) noexcept -> dimension
{
    return height(descriptor(image));
}

[[nodiscard]] inline auto dimensions(const dynamic_image &image) noexcept -> math::size2d<dimension>
{
    return dimensions(descriptor(image));
}

[[nodiscard]] inline auto rectangle(const dynamic_image &image) noexcept -> math::rectangle<dimension>
{
    return rectangle(descriptor(image));
}

[[nodiscard]] inline auto stride_x(const dynamic_image &image) noexcept -> std::ptrdiff_t
{
    return stride_x(descriptor(image));
}

[[nodiscard]] inline auto stride_y(const dynamic_image &image) noexcept -> std::ptrdiff_t
{
    return stride_y(descriptor(image));
}

[[nodiscard]] inline auto continuous(const dynamic_image &image) noexcept -> bool
{
    return continuous(descriptor(image));
}

[[nodiscard]] inline auto contains(const dynamic_image &image, const math::vector2<dimension> coord) noexcept -> bool
{
    return contains(descriptor(image), coord);
}

[[nodiscard]] inline auto size(const dynamic_image &image) noexcept -> std::ptrdiff_t
{
    return size(descriptor(image));
}

template <typename T>
[[nodiscard]] inline auto view(dynamic_image &image) noexcept -> image_view<T> &
{
    return image.get_image<T>();
}

template <typename T>
[[nodiscard]] inline auto view(const dynamic_image &image) noexcept -> const image_view<T> &
{
    return image.get_image<T>();
}

[[nodiscard]] inline auto raw_data(dynamic_image &image) noexcept -> std::byte *
{
    return image.raw_data();
}

[[nodiscard]] inline auto raw_data(const dynamic_image &image) noexcept -> const std::byte *
{
    return image.raw_data();
}

} // namespace aeon::imaging
