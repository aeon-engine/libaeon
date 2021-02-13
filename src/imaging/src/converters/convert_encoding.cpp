// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/imaging/converters/convert_pixel.h>

namespace aeon::imaging::convert
{

namespace detail
{

template <typename src_t, typename dst_t>
auto convert_impl(const image_view &img, const common::element_type dst_element_type, const pixel_encoding dst_encoding)
    -> image
{
    image dest_image{dst_element_type, dst_encoding, math::dimensions(img)};

    const auto src_width = math::width(img);
    const auto src_height = math::height(img);
    const auto src_stride = math::stride(img);
    const auto src_element_type = math::element_type(img);

    const auto dst_stride = math::stride(dest_image);

    const auto *const src_data = std::data(img);
    auto *dst_data = std::data(dest_image);

    for (auto y = 0; y < src_height; ++y)
    {
        for (auto x = 0; x < src_width; ++x)
        {
            const auto *const src =
                reinterpret_cast<const src_t *>(src_data + common::offset_of(src_element_type, src_stride, x, y));
            auto *dst = reinterpret_cast<dst_t *>(dst_data + common::offset_of(dst_element_type, dst_stride, x, y));

            if constexpr (std::is_same_v<dst_t, rgb24>)
            {
                *dst = pixel<src_t>::to_rgb24(*src);
            }
            else if constexpr (std::is_same_v<dst_t, rgba32>)
            {
                *dst = pixel<src_t>::to_rgba32(*src);
            }
            else if constexpr (std::is_same_v<dst_t, bgr24>)
            {
                *dst = pixel<src_t>::to_bgr24(*src);
            }
            else if constexpr (std::is_same_v<dst_t, bgra32>)
            {
                *dst = pixel<src_t>::to_bgra32(*src);
            }
            else
            {
                static_assert(true, "Unknown destination type.");
            }
        }
    }

    return dest_image;
}

} // namespace detail

auto to_rgb_copy(const image_view &img) -> image
{
    const auto encoding = imaging::encoding(img);
    const auto element_type = math::element_type(img);

    switch (encoding)
    {
        case pixel_encoding::monochrome:
        {
            if (element_type == common::element_type::u8_1 || element_type == common::element_type::u8_1_stride_4)
                return detail::convert_impl<std::uint8_t, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);
            else if (element_type == common::element_type::u16_1 ||
                     element_type == common::element_type::u16_1_stride_4)
                return detail::convert_impl<std::uint16_t, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);
            else if (element_type == common::element_type::u32_1 ||
                     element_type == common::element_type::u32_1_stride_8)
                return detail::convert_impl<std::uint32_t, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);
            else if (element_type == common::element_type::f32_1 ||
                     element_type == common::element_type::f32_1_stride_8)
                return detail::convert_impl<float, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);

            break;
        }
        case pixel_encoding::rgb:
            return image{img};
        case pixel_encoding::rgba:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<rgba32, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);

            break;
        }
        case pixel_encoding::bgr:
        {
            if (element_type == common::element_type::u8_3 || element_type == common::element_type::u8_3_stride_4)
                return detail::convert_impl<bgr24, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);

            break;
        }
        case pixel_encoding::bgra:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<bgra32, rgb24>(img, common::element_type::u8_3, pixel_encoding::rgb);

            break;
        }
        case pixel_encoding::undefined:
        default:
            throw convert_exception{};
    }

    throw convert_exception{};
}

auto to_bgr_copy(const image_view &img) -> image
{
    const auto encoding = imaging::encoding(img);
    const auto element_type = math::element_type(img);

    switch (encoding)
    {
        case pixel_encoding::monochrome:
        {
            if (element_type == common::element_type::u8_1 || element_type == common::element_type::u8_1_stride_4)
                return detail::convert_impl<std::uint8_t, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);
            else if (element_type == common::element_type::u16_1 ||
                     element_type == common::element_type::u16_1_stride_4)
                return detail::convert_impl<std::uint16_t, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);
            else if (element_type == common::element_type::u32_1 ||
                     element_type == common::element_type::u32_1_stride_8)
                return detail::convert_impl<std::uint32_t, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);
            else if (element_type == common::element_type::f32_1 ||
                     element_type == common::element_type::f32_1_stride_8)
                return detail::convert_impl<float, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);

            break;
        }
        case pixel_encoding::rgb:
        {
            if (element_type == common::element_type::u8_3 || element_type == common::element_type::u8_3_stride_4)
                return detail::convert_impl<rgb24, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);

            break;
        }
        case pixel_encoding::rgba:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<rgba32, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);

            break;
        }
        case pixel_encoding::bgr:
            return image{img};
        case pixel_encoding::bgra:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<bgra32, bgr24>(img, common::element_type::u8_3, pixel_encoding::bgr);

            break;
        }
        case pixel_encoding::undefined:
        default:
            throw convert_exception{};
    }

    throw convert_exception{};
}

auto to_rgba_copy(const image_view &img) -> image
{
    const auto encoding = imaging::encoding(img);
    const auto element_type = math::element_type(img);

    switch (encoding)
    {
        case pixel_encoding::monochrome:
        {
            if (element_type == common::element_type::u8_1 || element_type == common::element_type::u8_1_stride_4)
                return detail::convert_impl<std::uint8_t, rgba32>(img, common::element_type::u8_4,
                                                                  pixel_encoding::rgba);
            else if (element_type == common::element_type::u16_1 ||
                     element_type == common::element_type::u16_1_stride_4)
                return detail::convert_impl<std::uint16_t, rgba32>(img, common::element_type::u8_4,
                                                                   pixel_encoding::rgba);
            else if (element_type == common::element_type::u32_1 ||
                     element_type == common::element_type::u32_1_stride_8)
                return detail::convert_impl<std::uint32_t, rgba32>(img, common::element_type::u8_4,
                                                                   pixel_encoding::rgba);
            else if (element_type == common::element_type::f32_1 ||
                     element_type == common::element_type::f32_1_stride_8)
                return detail::convert_impl<float, rgba32>(img, common::element_type::u8_4, pixel_encoding::rgba);

            break;
        }
        case pixel_encoding::rgb:
        {
            if (element_type == common::element_type::u8_3 || element_type == common::element_type::u8_3_stride_4)
                return detail::convert_impl<rgb24, rgba32>(img, common::element_type::u8_4, pixel_encoding::rgba);

            break;
        }
        case pixel_encoding::rgba:
            return image{img};
        case pixel_encoding::bgr:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<bgr24, rgba32>(img, common::element_type::u8_4, pixel_encoding::rgba);

            break;
        }
        case pixel_encoding::bgra:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<bgra32, rgba32>(img, common::element_type::u8_4, pixel_encoding::rgba);

            break;
        }
        case pixel_encoding::undefined:
        default:
            throw convert_exception{};
    }

    throw convert_exception{};
}

auto to_bgra_copy(const image_view &img) -> image
{
    const auto encoding = imaging::encoding(img);
    const auto element_type = math::element_type(img);

    switch (encoding)
    {
        case pixel_encoding::monochrome:
        {
            if (element_type == common::element_type::u8_1 || element_type == common::element_type::u8_1_stride_4)
                return detail::convert_impl<std::uint8_t, bgra32>(img, common::element_type::u8_4,
                                                                  pixel_encoding::bgra);
            else if (element_type == common::element_type::u16_1 ||
                     element_type == common::element_type::u16_1_stride_4)
                return detail::convert_impl<std::uint16_t, bgra32>(img, common::element_type::u8_4,
                                                                   pixel_encoding::bgra);
            else if (element_type == common::element_type::u32_1 ||
                     element_type == common::element_type::u32_1_stride_8)
                return detail::convert_impl<std::uint32_t, bgra32>(img, common::element_type::u8_4,
                                                                   pixel_encoding::bgra);
            else if (element_type == common::element_type::f32_1 ||
                     element_type == common::element_type::f32_1_stride_8)
                return detail::convert_impl<float, bgra32>(img, common::element_type::u8_4, pixel_encoding::bgra);

            break;
        }
        case pixel_encoding::rgb:
        {
            if (element_type == common::element_type::u8_3 || element_type == common::element_type::u8_3_stride_4)
                return detail::convert_impl<rgb24, bgra32>(img, common::element_type::u8_4, pixel_encoding::bgra);

            break;
        }
        case pixel_encoding::rgba:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<rgba32, bgra32>(img, common::element_type::u8_4, pixel_encoding::bgra);

            break;
        }
        case pixel_encoding::bgr:
        {
            if (element_type == common::element_type::u8_4)
                return detail::convert_impl<bgr24, bgra32>(img, common::element_type::u8_4, pixel_encoding::bgra);

            break;
        }
        case pixel_encoding::bgra:
            return image{img};
        case pixel_encoding::undefined:
        default:
            throw convert_exception{};
    }

    throw convert_exception{};
}

} // namespace aeon::imaging::convert
