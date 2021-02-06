// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/assert.h>

namespace aeon::imaging
{

template <typename T>
inline image_view<T>::image_view() noexcept
    : descriptor_{}
    , data_ptr_{}
{
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> &descriptor, std::byte *data) noexcept
    : descriptor_{descriptor}
    , data_ptr_{data}
{
    aeon_assert(data, "Data is nullptr.");
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> &descriptor, const std::byte *data) noexcept
    : descriptor_{descriptor}
    , data_ptr_{const_cast<std::byte *>(data)}
{
    aeon_assert(data, "Data is nullptr.");
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> &descriptor) noexcept
    : descriptor_{descriptor}
    , data_ptr_{}
{
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::~image_view() noexcept = default;

template <typename T>
[[nodiscard]] inline auto image_view<T>::descriptor() const noexcept -> image_descriptor<T>
{
    return descriptor_;
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::data() noexcept -> T *
{
    return reinterpret_cast<T *>(data_ptr_);
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::data() const noexcept -> const T *
{
    return reinterpret_cast<const T *>(data_ptr_);
}

template <typename T>
template <typename U>
[[nodiscard]] inline auto image_view<T>::data() noexcept -> U *
{
    return reinterpret_cast<U *>(data_ptr_);
}

template <typename T>
template <typename U>
[[nodiscard]] inline auto image_view<T>::data() const noexcept -> const U *
{
    return reinterpret_cast<const U *>(data_ptr_);
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::data(const math::vector2<dimension> coord) noexcept -> T *
{
    aeon_assert(contains(descriptor_, coord), "Given coordinate was out of bounds.");
    return reinterpret_cast<T *>(data_ptr_ + at_offset(coord, descriptor_));
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::data(const math::vector2<dimension> coord) const noexcept -> const T *
{
    aeon_assert(contains(descriptor_, coord), "Given coordinate was out of bounds.");
    return reinterpret_cast<const T *>(data_ptr_ + at_offset(coord, descriptor_));
}

template <typename T>
template <typename U>
[[nodiscard]] inline auto image_view<T>::data(const math::vector2<dimension> coord) noexcept -> U *
{
    return reinterpret_cast<U *>(data(coord));
}

template <typename T>
template <typename U>
[[nodiscard]] inline auto image_view<T>::data(const math::vector2<dimension> coord) const noexcept -> const U *
{
    return reinterpret_cast<const U *>(data(coord));
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::at(const math::vector2<dimension> coord) noexcept -> T &
{
    return *data(coord);
}

template <typename T>
[[nodiscard]] inline auto image_view<T>::at(const math::vector2<dimension> coord) const noexcept -> const T &
{
    return *data(coord);
}

template <typename T>
[[nodiscard]] inline auto descriptor(const image_view<T> &view) noexcept -> image_descriptor<T>
{
    return view.descriptor();
}

template <typename T>
[[nodiscard]] inline auto width(const image_view<T> &view) noexcept
{
    return width(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto height(const image_view<T> &view) noexcept
{
    return height(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto dimensions(const image_view<T> &view) noexcept
{
    return dimensions(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto rectangle(const image_view<T> &view) noexcept
{
    return rectangle(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto stride(const image_view<T> &view) noexcept
{
    return stride(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto continuous(const image_view<T> &view) noexcept
{
    return continuous(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto contains(const image_view<T> &view, const math::vector2<dimension> coord) noexcept
{
    return contains(descriptor(view), coord);
}

template <typename T>
[[nodiscard]] inline auto size(const image_view<T> &view) noexcept -> std::ptrdiff_t
{
    return size(descriptor(view));
}

template <typename T>
[[nodiscard]] inline auto null(const image_view<T> &view) noexcept -> bool
{
    return null(descriptor(view)) || view.data() == nullptr;
}

template <typename T>
[[nodiscard]] inline auto valid(const image_view<T> &view) noexcept -> bool
{
    return !null(view);
}

template <typename T>
[[nodiscard]] inline auto make_view(const image_view<T> &view, const math::rectangle<int> &rect) noexcept
    -> image_view<T>
{
    aeon_assert(math::contains(rect, rectangle(view)), "View rectangle does not fit within image.");

    const image_descriptor<T> descriptor{math::size(rect), stride(view)};
    const auto data_offset =
        view.template data<std::byte>() + math::top(rect) * stride(view) + math::left(rect) * sizeof(T);
    return image_view{descriptor, data_offset};
}

} // namespace aeon::imaging
