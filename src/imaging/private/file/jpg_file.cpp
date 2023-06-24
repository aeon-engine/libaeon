// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/imaging/file/jpg_file.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/common/assert.h>
#include "tjhandle_wrapper.h"
#include <turbojpeg.h>

namespace aeon::imaging::file::jpg
{

namespace detail
{

[[nodiscard]] static auto subsample_mode_to_tjsamp(const subsample_mode mode) -> TJSAMP
{
    switch (mode)
    {
        case subsample_mode::subsample_444:
            return TJSAMP_444;
        case subsample_mode::subsample_440:
            return TJSAMP_440;
        case subsample_mode::subsample_422:
            return TJSAMP_422;
        case subsample_mode::subsample_420:
            return TJSAMP_420;
        case subsample_mode::subsample_411:
            return TJSAMP_411;
        case subsample_mode::subsample_grayscale:
            return TJSAMP_GRAY;
    }

    throw save_exception{};
}

} // namespace detail

[[nodiscard]] auto load(const std::filesystem::path &path) -> image
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    return load(stream);
}

[[nodiscard]] auto load(streams::idynamic_stream &stream) -> image
{
    detail::tjhandle_decompress_wrapper wrapper;

    streams::stream_reader reader{stream};
    auto data = reader.read_to_vector<unsigned char>();
    const auto data_size = static_cast<unsigned long>(std::size(data));

    int width = 0;
    int height = 0;

    if (tjDecompressHeader(wrapper.handle(), std::data(data), data_size, &width, &height) != 0)
        throw load_exception{};

    image loaded_image{format::r8g8b8_uint, width, height};

    if (tjDecompress2(wrapper.handle(), std::data(data), data_size,
                      reinterpret_cast<unsigned char *>(std::data(loaded_image)), width, 0, height, TJPF_RGB,
                      TJFLAG_FASTDCT) != 0)
        throw load_exception{};

    return loaded_image;
}

void save(const image_view &image, const subsample_mode subsample, int quality, streams::idynamic_stream &stream)
{
    aeon_assert_value_in_range(quality, 1, 100);

    const detail::tjhandle_compress_wrapper wrapper;

    const auto tjsubsample = detail::subsample_mode_to_tjsamp(subsample);
    std::vector<std::uint8_t> dest_buffer(tjBufSize(width(image), height(image), tjsubsample));
    auto dest_buffer_data = dest_buffer.data();

    auto actual_size = static_cast<unsigned long>(std::size(dest_buffer));
    if (tjCompress2(wrapper.handle(), reinterpret_cast<const unsigned char *>(std::data(image)), width(image),
                    static_cast<int>(stride(image)), height(image), TJPF_RGB, &dest_buffer_data, &actual_size,
                    tjsubsample, quality, TJFLAG_NOREALLOC) != 0)
        throw save_exception();

    dest_buffer.resize(actual_size);

    streams::stream_writer writer{stream};
    writer.vector_write(dest_buffer);

    if (stream.is_flushable())
        stream.flush();
}

void save(const image_view &image, const subsample_mode subsample, int quality, const std::filesystem::path &path)
{
    auto stream = streams::make_dynamic_stream(streams::file_sink_device{path});
    save(image, subsample, quality, stream);
}

} // namespace aeon::imaging::file::jpg
