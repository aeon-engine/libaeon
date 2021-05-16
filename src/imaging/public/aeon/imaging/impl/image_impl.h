// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/mat.h>

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

inline image::image(const image_view &view)
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

template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view) noexcept -> image
{
    return swizzle_copy(view, encoding(view));
}

template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view, const pixel_encoding encoding) noexcept -> image
{
    // Currently strides are not supported. They may be in the future.
    if (!view.element_type().continuous() || !math::continuous(view))
        std::abort();

    if (view.element_type().is_undefined())
        std::abort();

    auto new_element_type = view.element_type();
    new_element_type.count = sizeof...(components);
    new_element_type.size = new_element_type.component_size * new_element_type.count;
    new_element_type.stride = new_element_type.size;

    image new_image{new_element_type, encoding, dimensions(view)};

    switch (view.element_type().name)
    {
        case common::element_type_name::u8:
            math::internal::swizzle_copy<std::uint8_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::s8:
            math::internal::swizzle_copy<std::int8_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::u16:
            math::internal::swizzle_copy<std::uint16_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::s16:
            math::internal::swizzle_copy<std::int16_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::u32:
            math::internal::swizzle_copy<std::uint32_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::s32:
            math::internal::swizzle_copy<std::int32_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::u64:
            math::internal::swizzle_copy<std::uint64_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::s64:
            math::internal::swizzle_copy<std::int64_t, image, components...>(view, new_image);
            break;
        case common::element_type_name::f32:
            math::internal::swizzle_copy<float, image, components...>(view, new_image);
            break;
        case common::element_type_name::f64:
            math::internal::swizzle_copy<double, image, components...>(view, new_image);
            break;
        default:
            std::abort();
    }

    return new_image;
}

} // namespace aeon::imaging
