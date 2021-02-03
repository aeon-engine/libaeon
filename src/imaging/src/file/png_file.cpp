// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/file/png_read_structs.h>
#include <aeon/imaging/file/png_write_structs.h>
#include <aeon/imaging/file/png_structs.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/common/compilers.h>
#include <png.h>
#include <array>

#define PNG_HEADER_SIGNATURE_SIZE 8

namespace aeon::imaging::file::png
{

namespace detail
{

void png_read_callback(png_structp png_ptr, png_bytep output_ptr, png_size_t output_size)
{
    auto stream = static_cast<streams::idynamic_stream *>(png_get_io_ptr(png_ptr));

    // Do we have a stream?
    if (!stream)
        throw load_exception();

    // Read the data
    if (stream->read(reinterpret_cast<char *>(output_ptr), static_cast<size_t>(output_size)) !=
        static_cast<std::streamoff>(output_size))
        throw load_exception();
}

void png_write_callback(png_structp png_ptr, png_bytep data, png_size_t length)
{
    auto stream = static_cast<streams::idynamic_stream *>(png_get_io_ptr(png_ptr));
    stream->write(reinterpret_cast<char *>(data), length);
}

template <typename T>
struct png_color_type_traits
{
    static constexpr auto color_type() noexcept
    {
        return -1;
    }
};

template <>
struct png_color_type_traits<rgb24>
{
    static constexpr auto color_type() noexcept
    {
        return PNG_COLOR_TYPE_RGB;
    }
};

template <>
struct png_color_type_traits<rgba32>
{
    static constexpr auto color_type() noexcept
    {
        return PNG_COLOR_TYPE_RGB_ALPHA;
    }
};

template <typename T>
struct save_impl
{
    static void process(const image_view<T> &image, streams::idynamic_stream &stream)
    {
        // Check our stream
        if (!stream.good())
            throw save_exception();

        auto png_structs = detail::png_write_structs{};

        // Bind errors from libpng
        AEON_IGNORE_VS_WARNING_PUSH(4611)
        if (setjmp(png_jmpbuf(png_structs.png_ptr())))
            throw save_exception();
        AEON_IGNORE_VS_WARNING_POP()

        constexpr auto color_type = detail::png_color_type_traits<T>::color_type();
        const auto w = static_cast<png_uint_32>(width(image));
        const auto h = static_cast<png_uint_32>(height(image));
        const auto bit_depth = 8; // TODO: store bit depth in the image data.

        png_set_IHDR(png_structs.png_ptr(), png_structs.info_ptr(), w, h, bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

        auto rowpointer_buffer = std::vector<const std::uint8_t *>(h);
        const auto rowpointer_buffer_ptr = rowpointer_buffer.data();
        const auto pixel_data_ptr = reinterpret_cast<const std::uint8_t *>(image.data());

        for (auto y = 0u; y < h; ++y)
            rowpointer_buffer_ptr[y] = pixel_data_ptr + y * stride_y(image);

        // TODO: Figure out an alternative for const cast here.
        png_set_rows(png_structs.png_ptr(), png_structs.info_ptr(), const_cast<png_bytepp>(rowpointer_buffer_ptr));
        png_set_write_fn(png_structs.png_ptr(), &stream, detail::png_write_callback, nullptr);
        png_write_png(png_structs.png_ptr(), png_structs.info_ptr(), PNG_TRANSFORM_IDENTITY, nullptr);

        // Flush the output after writing.
        if (stream.is_flushable())
            stream.flush();
    }
};

} // namespace detail

[[nodiscard]] auto load(const std::filesystem::path &path) -> dynamic_image
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    return load(stream);
}

[[nodiscard]] auto load(streams::idynamic_stream &stream) -> dynamic_image
{
    // Check our stream
    if (!stream.good())
        throw load_exception();

    const auto size = stream.size();

    if (size == 0)
        throw load_exception();

    // Read the header
    auto png_header = std::array<png_byte, PNG_HEADER_SIGNATURE_SIZE>();

    if (stream.read(reinterpret_cast<char *>(png_header.data()), PNG_HEADER_SIGNATURE_SIZE) !=
        PNG_HEADER_SIGNATURE_SIZE)
        throw load_exception();

    // Check the header
    if (png_sig_cmp(png_header.data(), 0, PNG_HEADER_SIGNATURE_SIZE))
        throw load_exception();

    auto png_structs = detail::png_read_structs{};

    // Bind errors from libpng
    AEON_IGNORE_VS_WARNING_PUSH(4611)
    if (setjmp(png_jmpbuf(png_structs.png_ptr())))
        throw load_exception();
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
    const auto image_data = reinterpret_cast<png_byte *>(&(bitmap_buffer)[0]);

    // Row_pointers is for pointing to image_data for reading the
    // png with libpng
    // TODO: shouldn't this just be height? not times sizeof? Remaining of old code?
    const auto rowpointer_buff_size = temp_height * sizeof(png_bytep);
    auto rowpointer_buffer = std::vector<std::uint8_t *>(rowpointer_buff_size);

    // Cast to png_bytep
    const auto row_pointers = static_cast<png_bytep *>(&(rowpointer_buffer)[0]);

    // Set the individual row_pointers to point at the correct offsets
    // of image_data
    for (auto i = 0ul; i < temp_height; ++i)
    {
        row_pointers[i] = image_data + i * rowbytes;
    }

    // Read the png into image_data through row_pointers
    png_read_image(png_structs.png_ptr(), row_pointers);

    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB:
        {
            const auto d =
                image_descriptor<rgb24>{{static_cast<dimension>(temp_width), static_cast<dimension>(temp_height)}};
            auto img = image<rgb24>{d, std::move(bitmap_buffer)};
            return dynamic_image{std::move(img)};
        }
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            const auto d =
                image_descriptor<rgba32>{{static_cast<dimension>(temp_width), static_cast<dimension>(temp_height)}};
            auto img = image<rgba32>{d, std::move(bitmap_buffer)};
            return dynamic_image{std::move(img)};
        }
        default:
            throw load_exception();
    }
}

void save(const dynamic_image &image, const std::filesystem::path &path)
{
    auto stream = streams::make_dynamic_stream(streams::file_sink_device{path});
    save(image, stream);
}

void save(const dynamic_image &image, streams::idynamic_stream &stream)
{
    aeon_assert((encoding(image) == pixel_encoding::rgb24) || (encoding(image) == pixel_encoding::rgba32),
                "Encoding mismatch.");
    process_image<detail::save_impl>(image, stream);
}

template <typename T>
void save(const image_view<T> &image, const std::filesystem::path &path)
{
    auto stream = streams::make_dynamic_stream(streams::file_sink_device{path});
    save<T>(image, stream);
}

template void save<rgb24>(const image_view<rgb24> &image, const std::filesystem::path &path);
template void save<rgba32>(const image_view<rgba32> &image, const std::filesystem::path &path);

template <typename T>
void save(const image_view<T> &image, streams::idynamic_stream &stream)
{
    detail::save_impl<T>::process(image, stream);
}

template void save<rgb24>(const image_view<rgb24> &image, streams::idynamic_stream &stream);
template void save<rgba32>(const image_view<rgba32> &image, streams::idynamic_stream &stream);

} // namespace aeon::imaging::file::png
