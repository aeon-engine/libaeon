// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/converters/convert_encoding.h>

namespace aeon::imaging::convert
{

[[nodiscard]] auto to_rgb24(const dynamic_image &img) -> image<rgb24>
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return to_rgb24<std::uint8_t>(img.get_image<std::uint8_t>());
        case pixel_encoding::unsigned16:
            return to_rgb24<std::uint16_t>(img.get_image<std::uint16_t>());
        case pixel_encoding::unsigned32:
            return to_rgb24<std::uint32_t>(img.get_image<std::uint32_t>());
        case pixel_encoding::float32:
            return to_rgb24<float>(img.get_image<float>());
        case pixel_encoding::rgb24:
            return img.get_image<rgb24>().clone();
        case pixel_encoding::rgba32:
            return to_rgb24<rgba32>(img.get_image<rgba32>());
        case pixel_encoding::bgr24:
            return to_rgb24<bgr24>(img.get_image<bgr24>());
        case pixel_encoding::bgra32:
            return to_rgb24<bgra32>(img.get_image<bgra32>());
        default:
            throw convert_exception();
    }
}

[[nodiscard]] auto to_bgr24(const dynamic_image &img) -> image<bgr24>
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return to_bgr24<std::uint8_t>(img.get_image<std::uint8_t>());
        case pixel_encoding::unsigned16:
            return to_bgr24<std::uint16_t>(img.get_image<std::uint16_t>());
        case pixel_encoding::unsigned32:
            return to_bgr24<std::uint32_t>(img.get_image<std::uint32_t>());
        case pixel_encoding::float32:
            return to_bgr24<float>(img.get_image<float>());
        case pixel_encoding::rgb24:
            return to_bgr24<rgb24>(img.get_image<rgb24>());
        case pixel_encoding::rgba32:
            return to_bgr24<rgba32>(img.get_image<rgba32>());
        case pixel_encoding::bgr24:
            return img.get_image<bgr24>().clone();
        case pixel_encoding::bgra32:
            return to_bgr24<bgra32>(img.get_image<bgra32>());
        default:
            throw convert_exception();
    }
}

[[nodiscard]] auto to_rgba32(const dynamic_image &img) -> image<rgba32>
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return to_rgba32<std::uint8_t>(img.get_image<std::uint8_t>());
        case pixel_encoding::unsigned16:
            return to_rgba32<std::uint16_t>(img.get_image<std::uint16_t>());
        case pixel_encoding::unsigned32:
            return to_rgba32<std::uint32_t>(img.get_image<std::uint32_t>());
        case pixel_encoding::float32:
            return to_rgba32<float>(img.get_image<float>());
        case pixel_encoding::rgb24:
            return to_rgba32<rgb24>(img.get_image<rgb24>());
        case pixel_encoding::rgba32:
            return img.get_image<rgba32>().clone();
        case pixel_encoding::bgr24:
            return to_rgba32<bgr24>(img.get_image<bgr24>());
        case pixel_encoding::bgra32:
            return to_rgba32<bgra32>(img.get_image<bgra32>());
        default:
            throw convert_exception();
    }
}

[[nodiscard]] auto to_bgra32(const dynamic_image &img) -> image<bgra32>
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return to_bgra32<std::uint8_t>(img.get_image<std::uint8_t>());
        case pixel_encoding::unsigned16:
            return to_bgra32<std::uint16_t>(img.get_image<std::uint16_t>());
        case pixel_encoding::unsigned32:
            return to_bgra32<std::uint32_t>(img.get_image<std::uint32_t>());
        case pixel_encoding::float32:
            return to_bgra32<float>(img.get_image<float>());
        case pixel_encoding::rgb24:
            return to_bgra32<rgb24>(img.get_image<rgb24>());
        case pixel_encoding::rgba32:
            return to_bgra32<rgba32>(img.get_image<rgba32>());
        case pixel_encoding::bgr24:
            return to_bgra32<bgr24>(img.get_image<bgr24>());
        case pixel_encoding::bgra32:
            return img.get_image<bgra32>().clone();
        default:
            throw convert_exception();
    }
}

} // namespace aeon::imaging::convert
