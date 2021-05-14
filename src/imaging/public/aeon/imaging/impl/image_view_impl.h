// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::imaging
{

inline image_view::image_view() noexcept
    : mat_view{}
    , encoding_{pixel_encoding::undefined}
{
}

inline image_view::image_view(const common::element_type type, const pixel_encoding encoding,
                              const math::size2d<dimensions_type> dimensions, underlying_type *data) noexcept
    : mat_view{type, dimensions, data}
    , encoding_{encoding}
{
}

inline image_view::image_view(const common::element_type type, const pixel_encoding encoding,
                              const dimensions_type width, const dimensions_type height, underlying_type *data) noexcept
    : mat_view{type, width, height, data}
    , encoding_{encoding}
{
}

inline image_view::image_view(const common::element_type type, const pixel_encoding encoding,
                              const math::size2d<dimensions_type> dimensions, const stride_type stride,
                              underlying_type *data) noexcept
    : mat_view{type, dimensions, stride, data}
    , encoding_{encoding}
{
}

inline image_view::image_view(const common::element_type type, const pixel_encoding encoding,
                              const dimensions_type width, const dimensions_type height, const stride_type stride,
                              underlying_type *data) noexcept
    : mat_view{type, width, height, stride, data}
    , encoding_{encoding}
{
}

inline void image_view::encoding(const pixel_encoding encoding) noexcept
{
    encoding_ = encoding;
}

inline auto image_view::encoding() const noexcept -> pixel_encoding
{
    return encoding_;
}

[[nodiscard]] inline auto make_view(image_view &view, const math::rectangle<int> &rect) noexcept -> image_view
{
    aeon_assert(math::contains(rect, math::rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within image.");
    return image_view{element_type(view), encoding(view), width(rect),
                      height(rect),       stride(view),   math::at(view, left(rect), top(rect))};
}

} // namespace aeon::imaging
