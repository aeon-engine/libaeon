// Copyright (c) 2012-2019 Robin Degen

#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/filters/invert.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/compilers.h>
#include <aeon/common/literals.h>
#include <aeon/common/signed_sizeof.h>
#include <cstdint>

namespace aeon::imaging::file::bmp
{

namespace detail
{

static const auto expected_bitmap_type = 0x4D42_uint16_t;

AEON_PACK_STRUCT_PUSH(1)
struct bitmap_file_header
{
    std::uint16_t type;
    std::uint32_t size;
    std::uint16_t reserved1;
    std::uint16_t reserved2;
    std::uint32_t offbits;
} AEON_PACK_STRUCT_POP(1);

AEON_PACK_STRUCT_PUSH(1)
struct bitmap_info_header
{
    std::uint32_t size;
    std::int32_t width;
    std::int32_t height;
    std::uint16_t planes;
    std::uint16_t bitcount;
    std::uint32_t compression;
    std::uint32_t size_image;
    std::int32_t x_pels_per_meter;
    std::int32_t y_pels_per_meter;
    std::uint32_t clr_used;
    std::uint32_t clr_important;
} AEON_PACK_STRUCT_POP(1);

[[nodiscard]] static auto calculate_stride(const bitmap_info_header &info_header) noexcept
{
    return 4 * ((info_header.width * info_header.bitcount + 31) / 32);
}

} // namespace detail

[[nodiscard]] auto load(const std::filesystem::path &path) -> dynamic_image
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    return load(stream);
}

[[nodiscard]] auto load(streams::idynamic_stream &stream) -> dynamic_image
{
    detail::bitmap_file_header header{};

    if (stream.read(reinterpret_cast<char *>(&header), aeon_signed_sizeof(detail::bitmap_file_header)) !=
        aeon_signed_sizeof(detail::bitmap_file_header))
        throw load_exception();

    if (header.type != detail::expected_bitmap_type)
        throw load_exception();

    detail::bitmap_info_header info_header{};

    if (stream.read(reinterpret_cast<char *>(&info_header), aeon_signed_sizeof(detail::bitmap_info_header)) !=
        aeon_signed_sizeof(detail::bitmap_info_header))
        throw load_exception();

    if (!stream.seekg(header.offbits, streams::seek_direction::begin))
        throw load_exception();

    std::vector<std::byte> pixel_data(info_header.size_image);

    if (stream.read(reinterpret_cast<char *>(pixel_data.data()), info_header.size_image) != info_header.size_image)
        throw load_exception();

    const auto d =
        image_descriptor<bgr24>{{static_cast<dimension>(info_header.width), static_cast<dimension>(info_header.height)},
                                static_cast<dimension>(detail::calculate_stride(info_header))};

    const auto img = image<bgr24>{d, std::move(pixel_data)};
    return dynamic_image(filters::invert_vertically(img));
}

} // namespace aeon::imaging::file::bmp
