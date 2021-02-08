// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/mat3.h>
#include <aeon/common/assert.h>

namespace aeon::math
{

template <typename T>
inline constexpr mat_view_base<T>::mat_view_base() noexcept
    : type_{}
    , data_ptr_{nullptr}
    , dimensions_{}
    , stride_{0}
{
}

template <typename T>
inline constexpr mat_view_base<T>::mat_view_base(const common::element_type type,
                                                 const size2d<dimensions_type> dimensions,
                                                 underlying_type *data) noexcept
    : mat_view_base{type, dimensions, math::width(dimensions) * type.size, data}
{
}

template <typename T>
inline constexpr mat_view_base<T>::mat_view_base(const common::element_type type, const dimensions_type width,
                                                 const dimensions_type height, underlying_type *data) noexcept
    : mat_view_base{type, size2d{width, height}, data}
{
}

template <typename T>
inline constexpr mat_view_base<T>::mat_view_base(const common::element_type type,
                                                 const size2d<dimensions_type> dimensions, const stride_type stride,
                                                 underlying_type *data) noexcept
    : type_{type}
    , data_ptr_{data}
    , dimensions_{dimensions}
    , stride_{stride}
{
}

template <typename T>
inline constexpr mat_view_base<T>::mat_view_base(const common::element_type type, const dimensions_type width,
                                                 const dimensions_type height, const stride_type stride,
                                                 underlying_type *data) noexcept
    : mat_view_base{type, size2d{width, height}, stride, data}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::element_type() const noexcept -> common::element_type
{
    return type_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::width() const noexcept -> dimensions_type
{
    return math::width(dimensions_);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::height() const noexcept -> dimensions_type
{
    return math::height(dimensions_);
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::dimensions() const noexcept -> size2d<dimensions_type>
{
    return dimensions_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::stride() const noexcept -> stride_type
{
    return stride_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::size() const noexcept -> size_type
{
    return static_cast<size_type>(stride_ * height());
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::ssize() const noexcept -> ssize_type
{
    return static_cast<ssize_type>(stride_ * height());
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const vector2<dimensions_type> coord) noexcept -> value_type *
{
    aeon_assert(valid(*this), "Matrix view is not valid.");
    return &data_ptr_[stride_ * coord.y + type_.size * coord.x];
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const vector2<dimensions_type> coord) const noexcept
    -> const value_type *
{
    aeon_assert(valid(*this), "Matrix view is not valid.");
    return &data_ptr_[stride_ * coord.y + type_.size * coord.x];
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const dimensions_type column_index,
                                                         const dimensions_type row_index) noexcept -> value_type *
{
    return at(vector2{column_index, row_index});
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const dimensions_type column_index,
                                                         const dimensions_type row_index) const noexcept
    -> const value_type *
{
    return at(vector2{column_index, row_index});
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const vector2<dimensions_type> coord) noexcept -> U &
{
    return *reinterpret_cast<U *>(at(coord));
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const vector2<dimensions_type> coord) const noexcept
    -> const U &
{
    return *reinterpret_cast<const U *>(at(coord));
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const dimensions_type column_index,
                                                         const dimensions_type row_index) noexcept -> U &
{
    return *reinterpret_cast<U *>(at(column_index, row_index));
}

template <typename T>
template <typename U>
[[nodiscard]] inline constexpr auto mat_view_base<T>::at(const dimensions_type column_index,
                                                         const dimensions_type row_index) const noexcept -> const U &
{
    return *reinterpret_cast<const U *>(at(column_index, row_index));
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::data() noexcept -> value_type *
{
    return data_ptr_;
}

template <typename T>
[[nodiscard]] inline constexpr auto mat_view_base<T>::data() const noexcept -> const value_type *
{
    return data_ptr_;
}

template <typename T>
[[nodiscard]] inline constexpr auto element_type(const mat_view_base<T> &view) noexcept
{
    return view.element_type();
}

template <typename T>
[[nodiscard]] inline constexpr auto width(const mat_view_base<T> &view) noexcept
{
    return view.width();
}

template <typename T>
[[nodiscard]] inline constexpr auto height(const mat_view_base<T> &view) noexcept
{
    return view.height();
}

template <typename T>
[[nodiscard]] inline constexpr auto dimensions(const mat_view_base<T> &view) noexcept
{
    return view.dimensions();
}

template <typename T>
[[nodiscard]] inline constexpr auto stride(const mat_view_base<T> &view) noexcept
{
    return view.stride();
}

template <typename T>
[[nodiscard]] inline constexpr auto continuous(const mat_view_base<T> &view) noexcept
{
    return (height(view) == 1) || (stride(view) == width(view) * element_type(view).size);
}

template <typename T>
[[nodiscard]] inline constexpr auto contains(const mat_view_base<T> &view,
                                             const vector2<typename mat_view_base<T>::dimensions_type> coord) noexcept
{
    return contains(coord, dimensions(view));
}

template <typename T>
[[nodiscard]] inline constexpr auto size(const mat_view_base<T> &view) noexcept -> typename mat_view_base<T>::size_type
{
    return stride(view) * height(view);
}

template <typename T>
[[nodiscard]] inline constexpr auto null(const mat_view_base<T> &view) noexcept -> bool
{
    return data(view) == nullptr || (stride(view) == 0 && null(dimensions(view)));
}

template <typename T>
[[nodiscard]] inline constexpr auto valid(const mat_view_base<T> &view) noexcept -> bool
{
    return !null(view);
}

template <typename T>
[[nodiscard]] inline auto make_view(const mat_view_base<T> &view, const rectangle<int> &rect) noexcept
    -> mat_view_base<T>
{
    aeon_assert(math::contains(rect, rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within image.");
    return mat_view_base<T>(element_type(view), width(rect), height(rect), stride(view),
                            view.at(left(rect), top(rect)));
}

[[nodiscard]] inline auto make_view(mat3 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 3, 3, std::data(mat)};
}

[[nodiscard]] inline auto make_view(const mat3 &mat) noexcept -> const_mat_view
{
    return const_mat_view{common::element_type::f32_1, 3, 3, std::data(mat)};
}

[[nodiscard]] inline auto make_view(mat4 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 4, 4, std::data(mat)};
}

[[nodiscard]] inline auto make_view(const mat4 &mat) noexcept -> const_mat_view
{
    return const_mat_view{common::element_type::f32_1, 4, 4, std::data(mat)};
}

} // namespace aeon::math
