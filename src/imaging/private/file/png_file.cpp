// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/compilers.h>
#include "png_read_structs.h"
#include "png_write_structs.h"
#include "png_structs.h"
#include <png.h>
#include <array>

#define PNG_HEADER_SIGNATURE_SIZE 8

namespace aeon::imaging::file::png
{

namespace detail
{

void png_read_callback(png_structp png_ptr, png_bytep output_ptr, png_size_t output_size)
{
    auto *stream = static_cast<streams::idynamic_stream *>(png_get_io_ptr(png_ptr));

    // Do we have a stream?
    if (!stream)
        throw load_exception();

    // Read the data
    if (stream->read(reinterpret_cast<std::byte *>(output_ptr), static_cast<size_t>(output_size)) !=
        static_cast<std::streamoff>(output_size))
        throw load_exception();
}

void png_write_callback(png_structp png_ptr, png_bytep data, png_size_t length)
{
    auto *stream = static_cast<streams::idynamic_stream *>(png_get_io_ptr(png_ptr));
    stream->write(reinterpret_cast<std::byte *>(data), length);
}

[[nodiscard]] inline auto convert_encoding_to_color_type(const format format)
{
    switch (format)
    {
        case format::r8_uint:
            return PNG_COLOR_TYPE_GRAY;
        case format::r8g8b8_uint:
            return PNG_COLOR_TYPE_RGB;
        case format::r8g8b8a8_uint:
            return PNG_COLOR_TYPE_RGB_ALPHA;
        case format::r8g8_uint:
            return PNG_COLOR_TYPE_GRAY_ALPHA;
        case format::undefined:
        case format::b8g8r8_uint:
        case format::b8g8r8a8_uint:
        case format::bc1_rgb_srgb_block:
        case format::bc1_rgba_srgb_block:
        case format::bc2_srgb_block:
        case format::bc3_srgb_block:
        case format::r32_float:
        case format::r32_uint:
        case format::r32g32_float:
        case format::r32g32_uint:
        case format::r32g32b32_float:
        case format::r32g32b32_uint:
        case format::r32g32b32a32_float:
        case format::r32g32b32a32_uint:
        default:
            throw save_exception{};
    }
}

} // namespace detail

[[nodiscard]] auto load(const std::filesystem::path &path) -> image
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    return load(stream);
}

[[nodiscard]] auto load(streams::idynamic_stream &stream) -> image
{
    // Check our stream
    if (!stream.good())
        throw load_exception{};

    const auto size = stream.size();

    if (size == 0)
        throw load_exception{};

    // Read the header
    auto png_header = std::array<png_byte, PNG_HEADER_SIGNATURE_SIZE>();

    if (stream.read(reinterpret_cast<std::byte *>(png_header.data()), PNG_HEADER_SIGNATURE_SIZE) !=
        PNG_HEADER_SIGNATURE_SIZE)
        throw load_exception{};

    // Check the header
    if (png_sig_cmp(png_header.data(), 0, PNG_HEADER_SIGNATURE_SIZE))
        throw load_exception{};

    const auto png_structs = detail::png_read_structs{};

    // Bind errors from libpng
    AEON_IGNORE_VS_WARNING_PUSH(4611)
    if (setjmp(png_jmpbuf(png_structs.png_ptr())))
        throw load_exception{};
    AEON_IGNORE_VS_WARNING_POP()

    // Init png reading. We will be using a read function, as we can't read
    // from a file.
    png_set_read_fn(png_structs.png_ptr(), &stream, detail::png_read_callback);

    // Let libpng know we already read the signature
    png_set_sig_bytes(png_structs.png_ptr(), PNG_HEADER_SIGNATURE_SIZE);

    // Read all the info up to the image data
    png_read_info(png_structs.png_ptr(), png_structs.info_ptr());

    // Variables to pass to get info
    auto bit_depth = 0;
    auto color_type = 0;
    auto temp_width = png_uint_32();
    auto temp_height = png_uint_32();

    // Get info about png
    png_get_IHDR(png_structs.png_ptr(), png_structs.info_ptr(), &temp_width, &temp_height, &bit_depth, &color_type,
                 nullptr, nullptr, nullptr);

    // Update the png info struct.
    png_read_update_info(png_structs.png_ptr(), png_structs.info_ptr());

    const auto rowbytes = png_get_rowbytes(png_structs.png_ptr(), png_structs.info_ptr());

    // Allocate the image_data as a big block
    const auto bitmap_buff_size = rowbytes * temp_height * sizeof(png_byte);

    auto bitmap_buffer = std::vector<std::byte>(bitmap_buff_size);

    // Cast to png_byte since this is what libpng likes as buffer.
    // Just passing the pointer should be fine. But this ensures 100%
    // compatibility.
    auto *const image_data = reinterpret_cast<png_byte *>(&(bitmap_buffer)[0]);

    // Row_pointers is for pointing to image_data for reading the
    // png with libpng
    // TODO: shouldn't this just be height? not times sizeof? Remaining of old code?
    const auto rowpointer_buff_size = temp_height * sizeof(png_bytep);
    auto rowpointer_buffer = std::vector<std::uint8_t *>(rowpointer_buff_size);

    // Cast to png_bytep
    auto *const row_pointers = static_cast<png_bytep *>(&(rowpointer_buffer)[0]);

    // Set the individual row_pointers to point at the correct offsets
    // of image_data
    for (auto i = 0ul; i < temp_height; ++i)
    {
        row_pointers[i] = image_data + i * rowbytes;
    }

    // Read the png into image_data through row_pointers
    png_read_image(png_structs.png_ptr(), row_pointers);

    const auto width = static_cast<image::dimensions_type>(temp_width);
    const auto height = static_cast<image::dimensions_type>(temp_height);

    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB:
            return image{format::r8g8b8_uint, width, height, std::move(bitmap_buffer)};
        case PNG_COLOR_TYPE_RGB_ALPHA:
            return image{format::r8g8b8a8_uint, width, height, std::move(bitmap_buffer)};
        case PNG_COLOR_TYPE_GRAY:
            return image{format::r8_uint, width, height, std::move(bitmap_buffer)};
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            return image{format::r8g8_uint, width, height, std::move(bitmap_buffer)};
        default:
            throw load_exception{};
    }
}

void save(const image_view &image, streams::idynamic_stream &stream)
{
    // Check our stream
    if (!stream.good())
        throw save_exception{};

    const auto png_structs = detail::png_write_structs{};

    // Bind errors from libpng
    AEON_IGNORE_VS_WARNING_PUSH(4611)
    if (setjmp(png_jmpbuf(png_structs.png_ptr())))
        throw save_exception{};
    AEON_IGNORE_VS_WARNING_POP()

    const auto color_type = detail::convert_encoding_to_color_type(pixel_format(image));
    const auto width = static_cast<png_uint_32>(math::width(image));
    const auto height = static_cast<png_uint_32>(math::height(image));
    const auto bit_depth = static_cast<int>(math::element_type(image).component_size * 8);

    // Only 8 or 16 bit are supported bith depths
    if (bit_depth != 8 && bit_depth != 16)
        throw save_exception{};

    png_set_IHDR(png_structs.png_ptr(), png_structs.info_ptr(), width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    auto rowpointer_buffer = std::vector<const std::uint8_t *>(height);
    auto *const rowpointer_buffer_ptr = rowpointer_buffer.data();
    const auto *const pixel_data_ptr = reinterpret_cast<const std::uint8_t *>(image.data());

    for (auto y = 0u; y < height; ++y)
        rowpointer_buffer_ptr[y] = pixel_data_ptr + y * stride(image);

    // TODO: Figure out an alternative for const cast here.
    png_set_rows(png_structs.png_ptr(), png_structs.info_ptr(), const_cast<png_bytepp>(rowpointer_buffer_ptr));
    png_set_write_fn(png_structs.png_ptr(), &stream, detail::png_write_callback, nullptr);
    png_write_png(png_structs.png_ptr(), png_structs.info_ptr(), PNG_TRANSFORM_IDENTITY, nullptr);

    // Flush the output after writing.
    if (stream.is_flushable())
        stream.flush();
}

void save(const image_view &image, const std::filesystem::path &path)
{
    auto stream = streams::make_dynamic_stream(streams::file_sink_device{path});
    save(image, stream);
}

} // namespace aeon::imaging::file::png
