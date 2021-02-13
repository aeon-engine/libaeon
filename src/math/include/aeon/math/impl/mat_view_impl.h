// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/mat3.h>
#include <aeon/common/assert.h>

namespace aeon::math
{

inline mat_view::mat_view() noexcept
    : type_{}
    , data_ptr_{nullptr}
    , dimensions_{}
    , stride_{0}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          underlying_type *data) noexcept
    : mat_view{type, dimensions, math::width(dimensions) * type.size, data}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          underlying_type *data) noexcept
    : mat_view{type, size2d{width, height}, data}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          const stride_type stride, underlying_type *data) noexcept
    : type_{type}
    , data_ptr_{data}
    , dimensions_{dimensions}
    , stride_{stride}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          const stride_type stride, underlying_type *data) noexcept
    : mat_view{type, size2d{width, height}, stride, data}
{
}

[[nodiscard]] inline auto mat_view::element_type() const noexcept -> common::element_type
{
    return type_;
}

[[nodiscard]] inline auto mat_view::width() const noexcept -> dimensions_type
{
    return math::width(dimensions_);
}

[[nodiscard]] inline auto mat_view::height() const noexcept -> dimensions_type
{
    return math::height(dimensions_);
}

[[nodiscard]] inline auto mat_view::dimensions() const noexcept -> size2d<dimensions_type>
{
    return dimensions_;
}

[[nodiscard]] inline auto mat_view::stride() const noexcept -> stride_type
{
    return stride_;
}

[[nodiscard]] inline auto mat_view::size() const noexcept -> size_type
{
    return static_cast<size_type>(stride_ * height());
}

[[nodiscard]] inline auto mat_view::data() noexcept -> underlying_type *
{
    return data_ptr_;
}

[[nodiscard]] inline auto mat_view::data() const noexcept -> const underlying_type *
{
    return data_ptr_;
}

[[nodiscard]] inline auto make_view(mat_view &view, const rectangle<int> &rect) noexcept -> mat_view
{
    aeon_assert(math::contains(rect, rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within matrix.");
    return mat_view{element_type(view), width(rect), height(rect), stride(view), at(view, left(rect), top(rect))};
}

[[nodiscard]] inline auto make_view(mat3 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 3, 3, std::data(mat)};
}

[[nodiscard]] inline auto make_view(mat4 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 4, 4, std::data(mat)};
}

} // namespace aeon::math
