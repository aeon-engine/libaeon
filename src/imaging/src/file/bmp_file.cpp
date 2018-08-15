/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/filters/invert.h>
#include <aeon/streams/file_stream.h>
#include <aeon/common/compilers.h>
#include <aeon/common/literals.h>
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

auto calculate_stride(const bitmap_info_header &info_header) noexcept
{
    return 4 * ((info_header.width * info_header.bitcount + 31) / 32);
}

} // namespace detail

auto load(const std::filesystem::path &path) -> dynamic_image
{
    auto stream = streams::file_stream{path, streams::access_mode::read, streams::file_mode::binary};
    return load(stream);
}

auto load(streams::stream &stream) -> dynamic_image
{
    detail::bitmap_file_header header{};

    if (stream.read(reinterpret_cast<std::uint8_t *>(&header), sizeof(detail::bitmap_file_header)) !=
        sizeof(detail::bitmap_file_header))
        throw load_exception();

    if (header.type != detail::expected_bitmap_type)
        throw load_exception();

    detail::bitmap_info_header info_header{};

    if (stream.read(reinterpret_cast<std::uint8_t *>(&info_header), sizeof(detail::bitmap_info_header)) !=
        sizeof(detail::bitmap_info_header))
        throw load_exception();

    if (!stream.seek(header.offbits, streams::stream::seek_direction::begin))
        throw load_exception();

    std::vector<std::byte> pixel_data(info_header.size_image);

    if (stream.read(reinterpret_cast<uint8_t *>(pixel_data.data()), info_header.size_image) != info_header.size_image)
        throw load_exception();

    const auto d =
        image_descriptor<bgr24>{{static_cast<dimension>(info_header.width), static_cast<dimension>(info_header.height)},
                                static_cast<dimension>(detail::calculate_stride(info_header))};

    auto img = image<bgr24>{d, std::move(pixel_data)};
    return dynamic_image(filters::invert_vertically(img));
}

} // namespace aeon::imaging::file::bmp
