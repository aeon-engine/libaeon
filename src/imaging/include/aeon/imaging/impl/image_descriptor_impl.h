// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::imaging
{

template <typename T>
inline image_descriptor<T>::image_descriptor(const math::size2d<dimension> dimensions) noexcept
    : image_descriptor{dimensions, static_cast<std::ptrdiff_t>(math::width(dimensions) * sizeof(T))}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor(const dimension width, const dimension height) noexcept
    : image_descriptor{{width, height}, static_cast<std::ptrdiff_t>(width * sizeof(T))}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor(const math::size2d<dimension> dimensions,
                                             const std::ptrdiff_t stride) noexcept
    : dimensions_{dimensions}
    , stride_{stride}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor() noexcept
    : dimensions_{}
    , stride_{}
{
}

template <typename T>
inline image_descriptor<T>::~image_descriptor() = default;

template <typename T>
[[nodiscard]] inline auto image_descriptor<T>::width() const noexcept -> dimension
{
    return math::width(dimensions_);
}

template <typename T>
[[nodiscard]] inline auto image_descriptor<T>::height() const noexcept -> dimension
{
    return math::height(dimensions_);
}

template <typename T>
[[nodiscard]] inline auto image_descriptor<T>::dimensions() const noexcept -> math::size2d<dimension>
{
    return dimensions_;
}

template <typename T>
[[nodiscard]] inline auto image_descriptor<T>::stride() const noexcept -> std::ptrdiff_t
{
    return stride_;
}

template <typename T>
[[nodiscard]] inline auto null(const image_descriptor<T> &descriptor) noexcept -> bool
{
    return stride(descriptor) == 0 && math::null(dimensions(descriptor));
}

template <typename T>
[[nodiscard]] inline auto valid(const image_descriptor<T> &descriptor) noexcept -> bool
{
    return !null(descriptor);
}

template <typename T>
[[nodiscard]] inline auto width(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.width();
}

template <typename T>
[[nodiscard]] inline auto height(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.height();
}

template <typename T>
[[nodiscard]] inline auto dimensions(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.dimensions();
}

template <typename T>
[[nodiscard]] inline auto rectangle(const image_descriptor<T> &descriptor) noexcept -> math::rectangle<dimension>
{
    return math::rect(dimensions(descriptor));
}

template <typename T>
[[nodiscard]] inline auto stride(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.stride();
}

template <typename T>
[[nodiscard]] inline auto continuous(const image_descriptor<T> &descriptor) noexcept
{
    return stride(descriptor) == aeon_signed_sizeof(T) * width(descriptor);
}

template <typename T>
[[nodiscard]] inline auto contains(const image_descriptor<T> &descriptor, const math::vector2<dimension> coord) noexcept
{
    return math::contains(coord, dimensions(descriptor));
}

template <typename T>
[[nodiscard]] inline auto at_offset(const math::vector2<dimension> coord,
                                    const image_descriptor<T> &descriptor) noexcept -> std::ptrdiff_t
{
    return stride(descriptor) * coord.y + sizeof(T) * coord.x;
}

template <typename T>
[[nodiscard]] inline auto size(const image_descriptor<T> &descriptor) noexcept -> std::ptrdiff_t
{
    return stride(descriptor) * height(descriptor);
}

template <typename T>
inline auto operator==(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept
{
    return dimensions(lhs) == dimensions(rhs) && stride(lhs) == stride(rhs);
}

template <typename T>
inline auto operator!=(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace aeon::imaging
