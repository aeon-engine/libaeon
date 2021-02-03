// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::imaging
{

template <typename T>
inline image_descriptor<T>::image_descriptor(const math::size2d<dimension> dimensions) noexcept
    : image_descriptor{dimensions, sizeof(T), static_cast<std::ptrdiff_t>(math::width(dimensions) * sizeof(T))}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor(const dimension width, const dimension height) noexcept
    : image_descriptor{{width, height}, sizeof(T), static_cast<std::ptrdiff_t>(width * sizeof(T))}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor(const math::size2d<dimension> dimensions,
                                             const std::ptrdiff_t stride_y) noexcept
    : image_descriptor{dimensions, sizeof(T), stride_y}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor(const math::size2d<dimension> dimensions, const std::ptrdiff_t stride_x,
                                             const std::ptrdiff_t stride_y) noexcept
    : dimensions_{dimensions}
    , stride_x_{stride_x}
    , stride_y_{stride_y}
{
}

template <typename T>
inline image_descriptor<T>::image_descriptor() noexcept
    : dimensions_{}
    , stride_x_{}
    , stride_y_{}
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
[[nodiscard]] inline auto image_descriptor<T>::stride_x() const noexcept -> std::ptrdiff_t
{
    return stride_x_;
}

template <typename T>
[[nodiscard]] inline auto image_descriptor<T>::stride_y() const noexcept -> std::ptrdiff_t
{
    return stride_y_;
}

template <typename T>
[[nodiscard]] inline auto null(const image_descriptor<T> &descriptor) noexcept -> bool
{
    return stride_x(descriptor) == 0 && stride_y(descriptor) == 0 && math::null(dimensions(descriptor));
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
[[nodiscard]] inline auto stride_x(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.stride_x();
}

template <typename T>
[[nodiscard]] inline auto stride_y(const image_descriptor<T> &descriptor) noexcept
{
    return descriptor.stride_y();
}

template <typename T>
[[nodiscard]] inline auto continuous(const image_descriptor<T> &descriptor) noexcept
{
    return stride_x(descriptor) == aeon_signed_sizeof(T) &&
           stride_y(descriptor) == aeon_signed_sizeof(T) * width(descriptor);
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
    return stride_y(descriptor) * coord.y + stride_x(descriptor) * coord.x;
}

template <typename T>
[[nodiscard]] inline auto size(const image_descriptor<T> &descriptor) noexcept -> std::ptrdiff_t
{
    return stride_y(descriptor) * height(descriptor);
}

template <typename T>
inline auto operator==(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept
{
    return dimensions(lhs) == dimensions(rhs) && stride_x(lhs) == stride_x(rhs) && stride_y(lhs) == stride_y(rhs);
}

template <typename T>
inline auto operator!=(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace aeon::imaging
