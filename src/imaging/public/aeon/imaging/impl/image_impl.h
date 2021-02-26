// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::imaging
{

inline image::image() noexcept
    : image_view{}
    , data_{}
{
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions) noexcept
    : image_view{type, encoding, dimensions, nullptr}
    , data_(math::width(dimensions) * type.stride * math::height(dimensions))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height) noexcept
    : image_view{type, encoding, width, height, nullptr}
    , data_(width * type.stride * height)
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride) noexcept
    : image_view{type, encoding, dimensions, stride, nullptr}
    , data_(stride * math::height(dimensions))
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height, const stride_type stride) noexcept
    : image_view{type, encoding, width, height, stride, nullptr}
    , data_(stride * height)
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions, std::vector<underlying_type> data) noexcept
    : image_view{type, encoding, dimensions, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height, std::vector<underlying_type> data) noexcept
    : image_view{type, encoding, width, height, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride,
                    std::vector<underlying_type> data) noexcept
    : image_view{type, encoding, dimensions, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height, const stride_type stride, std::vector<underlying_type> data) noexcept
    : image_view{type, encoding, width, height, stride, nullptr}
    , data_{std::move(data)}
{
    mat_view::data_ptr_ = std::data(data_);
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions, const underlying_type *data)
    : image_view{type, encoding, dimensions, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height, const underlying_type *data)
    : image_view{type, encoding, width, height, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const common::element_type type, const pixel_encoding encoding,
                    const math::size2d<dimensions_type> dimensions, const stride_type stride,
                    const underlying_type *data)
    : image_view{type, encoding, dimensions, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const common::element_type type, const pixel_encoding encoding, const dimensions_type width,
                    const dimensions_type height, const stride_type stride, const underlying_type *data)
    : image_view{type, encoding, width, height, stride, nullptr}
    , data_{}
{
    copy_from_pointer(data);
}

inline image::image(const iimage &view)
    : image_view{math::element_type(view), imaging::encoding(view), math::dimensions(view), math::stride(view), nullptr}
    , data_{}
{
    copy_from_pointer(std::data(view));
}

inline auto image::clone() const -> image
{
    return image{type_, encoding_, dimensions_, stride_, data_};
}

inline void image::clear() noexcept
{
    encoding_ = pixel_encoding::undefined;
    type_ = {};
    data_ptr_ = nullptr;
    dimensions_ = {};
    stride_ = 0;

    // Force data deletion. Clear does not guarantee deallocation.
    decltype(data_)().swap(data_);
}

inline void image::copy_from_pointer(const underlying_type *data)
{
    const auto size = mat_view::size();
    data_.resize(size);
    mat_view::data_ptr_ = std::data(data_);
    std::copy_n(data, size, std::begin(data_));
}

} // namespace aeon::imaging
