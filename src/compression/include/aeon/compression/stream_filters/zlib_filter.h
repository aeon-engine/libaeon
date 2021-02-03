// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/compression/zlib.h>
#include <aeon/streams/filters/filter.h>
#include <aeon/streams/tags.h>

#include <memory>
#include <array>

namespace aeon::compression::stream_filters
{

template <int compress_buffer_size = 256>
class zlib_compress_filter : public streams::filter
{
public:
    struct category : streams::output
    {
    };

    explicit zlib_compress_filter(const zlib_compression_mode mode = zlib_compression_mode::best)
        : compress_{mode, compress_buffer_size}
    {
    }

    zlib_compress_filter(zlib_compress_filter &&) noexcept = default;
    auto operator=(zlib_compress_filter &&) noexcept -> zlib_compress_filter & = default;

    zlib_compress_filter(const zlib_compress_filter &) noexcept = delete;
    auto operator=(const zlib_compress_filter &) noexcept -> zlib_compress_filter & = delete;

    ~zlib_compress_filter() = default;

    template <typename sink_t>
    auto write(sink_t &sink, const char *data, const std::streamsize size) -> std::streamsize
    {
        compress_.write(data, size,
                        [&sink](const char *data, const std::streamsize size) { return sink.write(data, size); });
        return size;
    }

private:
    zlib_compress compress_;
};

template <int decompress_buffer_size = 256>
class zlib_decompress_filter : public streams::filter
{
public:
    struct category : streams::input
    {
    };

    explicit zlib_decompress_filter()
        : decompress_{decompress_buffer_size}
    {
    }

    zlib_decompress_filter(zlib_decompress_filter &&) noexcept = default;
    auto operator=(zlib_decompress_filter &&) noexcept -> zlib_decompress_filter & = default;

    zlib_decompress_filter(const zlib_decompress_filter &) noexcept = delete;
    auto operator=(const zlib_decompress_filter &) noexcept -> zlib_decompress_filter & = delete;

    ~zlib_decompress_filter() = default;

    template <typename source_t>
    auto read(source_t &source, char *data, const std::streamsize size) -> std::streamsize
    {
        return decompress_.read(data, size,
                                [&source](char *data, const std::streamsize size) { return source.read(data, size); });
    }

private:
    zlib_decompress decompress_;
};

} // namespace aeon::compression::stream_filters
