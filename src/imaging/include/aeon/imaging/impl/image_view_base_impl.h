// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/assert.h>

namespace aeon::imaging
{

template <typename T>
inline image_view_base<T>::image_view_base() noexcept
    : descriptor_{}
{
}

template <typename T>
inline image_view_base<T>::image_view_base(const image_descriptor<T> &descriptor) noexcept
    : descriptor_{descriptor}
{
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view_base<T>::~image_view_base() noexcept = default;

template <typename T>
[[nodiscard]] inline auto image_view_base<T>::descriptor() const noexcept -> image_descriptor<T>
{
    return descriptor_;
}

template <typename T>
[[nodiscard]] inline auto descriptor(const image_view_base<T> &view) noexcept -> image_descriptor<T>
{
    return view.descriptor();
}

template <typename T>
[[nodiscard]] inline auto width(const image_view_base<T> &view) noexcept
{
    return width(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto height(const image_view_base<T> &view) noexcept
{
    return height(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto dimensions(const image_view_base<T> &view) noexcept
{
    return dimensions(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto rectangle(const image_view_base<T> &view) noexcept
{
    return rectangle(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto stride(const image_view_base<T> &view) noexcept
{
    return stride(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto continuous(const image_view_base<T> &view) noexcept
{
    return continuous(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto contains(const image_view_base<T> &view, const math::vector2<dimension> coord) noexcept
{
    return contains(descriptor(view), coord);
}

template <typename T>
[[nodiscard]] inline auto size(const image_view_base<T> &view) noexcept -> std::ptrdiff_t
{
    return size(descriptor(view));
}

} // namespace aeon::imaging
