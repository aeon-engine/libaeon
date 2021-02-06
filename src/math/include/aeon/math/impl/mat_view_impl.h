// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/mat3.h>
#include <aeon/common/assert.h>
#include <aeon/common/signed_sizeof.h>

namespace aeon::math
{

template <typename T>
inline constexpr mat_view<T>::mat_view() noexcept
    : data_ptr_{nullptr}
    , dimensions_{}
    , stride_{0}
{
}

template <typename T>
inline constexpr mat_view<T>::mat_view(const size2d<dimensions_type> dimensions, element_type *data) noexcept
    : mat_view{dimensions, math::width(dimensions) * sizeof(T), reinterpret_cast<underlying_type *>(data)}
{
}

template <typename T>
inline constexpr mat_view<T>::mat_view(const dimensions_type width, const dimensions_type height,
                                       element_type *data) noexcept
    : mat_view{size2d{width, height}, data}
{
}

template <typename T>
inline constexpr mat_view<T>::mat_view(const size2d<dimensions_type> dimensions, const std::ptrdiff_t stride,
                                       underlying_type *data) noexcept
    : data_ptr_{data}
    , dimensions_{dimensions}
    , stride_{stride}
{
}

template <typename T>
inline constexpr mat_view<T>::mat_view(const dimensions_type width, const dimensions_type height,
                                       const std::ptrdiff_t stride, underlying_type *data) noexcept
    : mat_view{size2d{width, height}, stride, data}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::width() const noexcept -> dimensions_type
{
    return math::width(dimensions_);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::height() const noexcept -> dimensions_type
{
    return math::height(dimensions_);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::dimensions() const noexcept -> size2d<dimensions_type>
{
    return dimensions_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::stride() const noexcept -> stride_type
{
    return stride_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::size() const noexcept -> size_type
{
    return static_cast<size_type>(stride_ * height());
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::ssize() const noexcept -> ssize_type
{
    return static_cast<ssize_type>(stride_ * height());
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::at(const vector2<dimensions_type> coord) noexcept -> value_type &
{
    // Note: X and Y are swapped due to column ordering
    return reinterpret_cast<value_type &>(ptr<std::byte>()[stride_ * coord.y + sizeof(T) * coord.x]);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::at(const vector2<dimensions_type> coord) const noexcept -> value_type
{
    // Note: X and Y are swapped due to column ordering
    return reinterpret_cast<const value_type &>(ptr<const std::byte>()[stride_ * coord.y + sizeof(T) * coord.x]);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::at(const dimensions_type column_index,
                                                    const dimensions_type row_index) noexcept -> value_type &
{
    return at(vector2{column_index, row_index});
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::at(const dimensions_type column_index,
                                                    const dimensions_type row_index) const noexcept -> value_type
{
    return at(vector2{column_index, row_index});
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::data() noexcept -> underlying_type *
{
    return data_ptr_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::data() const noexcept -> const underlying_type *
{
    return data_ptr_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::ptr() noexcept -> value_type *
{
    return ptr<value_type>();
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view<T>::ptr() const noexcept -> const value_type *
{
    return ptr<value_type>();
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view<T>::ptr() noexcept -> U *
{
    return reinterpret_cast<U *>(data_ptr_);
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view<T>::ptr() const noexcept -> const U *
{
    return reinterpret_cast<const U *>(data_ptr_);
}

template <typename T>
[[nodiscard]] inline constexpr auto width(const mat_view<T> &view) noexcept
{
    return view.width();
}

template <typename T>
[[nodiscard]] inline constexpr auto height(const mat_view<T> &view) noexcept
{
    return view.height();
}

template <typename T>
[[nodiscard]] inline constexpr auto dimensions(const mat_view<T> &view) noexcept
{
    return view.dimensions();
}

template <typename T>
[[nodiscard]] inline constexpr auto stride(const mat_view<T> &view) noexcept
{
    return view.stride();
}

template <typename T>
[[nodiscard]] inline constexpr auto continuous(const mat_view<T> &view) noexcept
{
    return (height(view) == 1) || (stride(view) == aeon_signed_sizeof(T) * width(view));
}

template <typename T>
[[nodiscard]] inline constexpr auto contains(const mat_view<T> &view,
                                             const vector2<typename mat_view<T>::dimensions_type> coord) noexcept
{
    return contains(coord, dimensions(view));
}

template <typename T>
[[nodiscard]] inline constexpr auto size(const mat_view<T> &view) noexcept -> typename mat_view<T>::size_type
{
    return stride(view) * height(view);
}

template <typename T>
[[nodiscard]] inline constexpr auto null(const mat_view<T> &view) noexcept -> bool
{
    return ptr(view) == nullptr || (stride(view) == 0 && null(dimensions(view)));
}

template <typename T>
[[nodiscard]] inline constexpr auto valid(const mat_view<T> &view) noexcept -> bool
{
    return !null(view);
}

template <typename T>
[[nodiscard]] inline constexpr auto make_view(const mat_view<T> &view, const rectangle<int> &rect) noexcept
    -> mat_view<T>
{
    aeon_assert(math::contains(rect, rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within image.");
    const auto data_offset = view.template ptr<std::byte>() + top(rect) * stride(view) + left(rect) * sizeof(T);
    return mat_view<T>{width(rect), height(rect), stride(view), data_offset};
}

[[nodiscard]] inline constexpr auto make_view(mat3 &mat) noexcept -> mat_view<float>
{
    return mat_view{3, 3, ptr(mat)};
}

[[nodiscard]] inline constexpr auto make_view(const mat3 &mat) noexcept -> mat_view<const float>
{
    return mat_view{3, 3, ptr(mat)};
}

[[nodiscard]] inline constexpr auto make_view(mat4 &mat) noexcept -> mat_view<float>
{
    return mat_view{4, 4, ptr(mat)};
}

[[nodiscard]] inline constexpr auto make_view(const mat4 &mat) noexcept -> mat_view<const float>
{
    return mat_view{4, 4, ptr(mat)};
}

template <typename T>
[[nodiscard]] inline constexpr auto ptr(mat_view<T> &mat) noexcept -> typename mat_view<T>::value_type *
{
    return mat.ptr();
}

template <typename T>
[[nodiscard]] inline constexpr auto ptr(const mat_view<T> &mat) noexcept -> const typename mat_view<T>::value_type *
{
    return mat.ptr();
}

} // namespace aeon::math
