// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/file/bmp_file.h>
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

[[nodiscard]] static auto calculate_stride(const bitmap_info_header &info_header) noexcept -> std::size_t
{
    return ((info_header.width * info_header.bitcount + 31) / 32) * 4ull;
}

} // namespace detail

[[nodiscard]] auto load(const std::filesystem::path &path) -> image
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    return load(stream);
}

[[nodiscard]] auto load(streams::idynamic_stream &stream) -> image
{
    detail::bitmap_file_header header{};

    if (stream.read(reinterpret_cast<std::byte *>(&header), aeon_signed_sizeof(detail::bitmap_file_header)) !=
        aeon_signed_sizeof(detail::bitmap_file_header))
        throw load_exception{};

    if (header.type != detail::expected_bitmap_type)
        throw load_exception{};

    detail::bitmap_info_header info_header{};

    if (stream.read(reinterpret_cast<std::byte *>(&info_header), aeon_signed_sizeof(detail::bitmap_info_header)) !=
        aeon_signed_sizeof(detail::bitmap_info_header))
        throw load_exception{};

    if (!stream.seekg(header.offbits, streams::seek_direction::begin))
        throw load_exception{};

    std::vector<std::byte> pixel_data(info_header.size_image);

    if (stream.read(reinterpret_cast<std::byte *>(pixel_data.data()), info_header.size_image) != info_header.size_image)
        throw load_exception{};

    auto img = image{common::element_type::u8_3,
                     format::b8g8r8_uint,
                     info_header.width,
                     info_header.height,
                     detail::calculate_stride(info_header),
                     std::move(pixel_data)};

    math::invert_vertically(img);

    return img;
}

} // namespace aeon::imaging::file::bmp
