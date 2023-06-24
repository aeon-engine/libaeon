// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::imaging
{

inline image_view::image_view() noexcept
    : mat_view{}
    , format_{imaging::format::undefined}
{
}

inline image_view::image_view(const common::element_type type, const imaging::format format,
                              const math::size2d<dimensions_type> dimensions, underlying_type *data) noexcept
    : mat_view{type, dimensions, data}
    , format_{format}
{
}

inline image_view::image_view(const common::element_type type, const imaging::format format,
                              const dimensions_type width, const dimensions_type height, underlying_type *data) noexcept
    : mat_view{type, width, height, data}
    , format_{format}
{
}

inline image_view::image_view(const common::element_type type, const imaging::format format,
                              const math::size2d<dimensions_type> dimensions, const stride_type stride,
                              underlying_type *data) noexcept
    : mat_view{type, dimensions, stride, data}
    , format_{format}
{
}

inline image_view::image_view(const common::element_type type, const imaging::format format,
                              const dimensions_type width, const dimensions_type height, const stride_type stride,
                              underlying_type *data) noexcept
    : mat_view{type, width, height, stride, data}
    , format_{format}
{
}

inline image_view::image_view(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                              underlying_type *data) noexcept
    : image_view{to_element_type(format), format, dimensions, data}
{
}

inline image_view::image_view(const imaging::format format, const dimensions_type width, const dimensions_type height,
                              underlying_type *data) noexcept
    : image_view{to_element_type(format), format, width, height, data}
{
}

inline image_view::image_view(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                              const stride_type stride, underlying_type *data) noexcept
    : image_view{to_element_type(format), format, dimensions, stride, data}
{
}

inline image_view::image_view(const imaging::format format, const dimensions_type width, const dimensions_type height,
                              const stride_type stride, underlying_type *data) noexcept
    : image_view{to_element_type(format), format, width, height, stride, data}
{
}

inline void image_view::format(const imaging::format format) noexcept
{
    format_ = format;
}

inline auto image_view::format() const noexcept -> imaging::format
{
    return format_;
}

[[nodiscard]] inline auto make_view(image_view &view, const math::rectangle<int> &rect) noexcept -> image_view
{
    aeon_assert(math::contains(rect, math::rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within image.");
    return image_view{element_type(view), pixel_format(view), width(rect),
                      height(rect),       stride(view),       math::at(view, left(rect), top(rect))};
}

} // namespace aeon::imaging
