// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/tags.h>
#include <aeon/streams/exception.h>
#include <aeon/common/assert.h>

#define ZLIB_CONST
#include <zlib.h>
#undef ZLIB_CONST

#include <iostream>
#include <array>

namespace aeon::streams
{

class zlib_compress_filter_exception : public stream_exception
{
};

class zlib_decompress_filter_exception : public stream_exception
{
};

namespace internal
{

class zlib_compress
{
public:
    explicit zlib_compress(const int level)
        : zstream_{}
    {
        if (deflateInit(&zstream_, level) != Z_OK)
            throw zlib_compress_filter_exception{};
    }

    zlib_compress(zlib_compress &&) noexcept = delete;
    auto operator=(zlib_compress &&) noexcept -> zlib_compress & = delete;

    zlib_compress(const zlib_compress &) noexcept = delete;
    auto operator=(const zlib_compress &) noexcept -> zlib_compress & = delete;

    ~zlib_compress()
    {
        deflateEnd(&zstream_);
    }

    auto stream() noexcept -> z_stream &
    {
        return zstream_;
    }

private:
    z_stream zstream_;
};

class zlib_decompress
{
public:
    explicit zlib_decompress()
        : zstream_{}
    {
        if (inflateInit(&zstream_) != Z_OK)
            throw zlib_compress_filter_exception{};
    }

    zlib_decompress(zlib_decompress &&) noexcept = delete;
    auto operator=(zlib_decompress &&) noexcept -> zlib_decompress & = delete;

    zlib_decompress(const zlib_decompress &) noexcept = delete;
    auto operator=(const zlib_decompress &) noexcept -> zlib_decompress & = delete;

    ~zlib_decompress()
    {
        inflateEnd(&zstream_);
    }

    auto stream() noexcept -> z_stream &
    {
        return zstream_;
    }

private:
    z_stream zstream_;
};

} // namespace internal

enum class zlib_compression_mode : int
{
    best = 9,
    balanced = 5,
    fastest = 1
};

template <int compress_buffer_size = 256>
class zlib_compress_filter : public filter
{
public:
    struct category : output
    {
    };

    explicit zlib_compress_filter(const zlib_compression_mode mode = zlib_compression_mode::best)
        : zlib_compress_{std::make_unique<internal::zlib_compress>(static_cast<int>(mode))}
        , output_buffer_{}
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
        zlib_compress_->stream().avail_in = static_cast<uInt>(size);
        zlib_compress_->stream().next_in = reinterpret_cast<const unsigned char *>(data);

        do
        {
            zlib_compress_->stream().avail_out = compress_buffer_size;
            zlib_compress_->stream().next_out = reinterpret_cast<unsigned char *>(std::data(output_buffer_));
            if (deflate(&zlib_compress_->stream(), Z_SYNC_FLUSH) != Z_OK)
                throw zlib_compress_filter_exception{};

            const auto write_size =
                static_cast<std::streamsize>(compress_buffer_size - zlib_compress_->stream().avail_out);
            aeon_assert(write_size >= 0, "Zlib compress write size can't be < 0.");

            if (write_size != 0)
            {
                if (sink.write(std::data(output_buffer_), write_size) != write_size)
                    throw zlib_compress_filter_exception{};
            }

        } while (zlib_compress_->stream().avail_out == 0);

        aeon_assert(zlib_compress_->stream().avail_in == 0, "Did not write all expected compressed bytes.");

        return size;
    }

private:
    std::unique_ptr<internal::zlib_compress> zlib_compress_;
    std::array<char, compress_buffer_size> output_buffer_;
};

template <int decompress_buffer_size = 256>
class zlib_decompress_filter : public filter
{
public:
    struct category : input
    {
    };

    explicit zlib_decompress_filter()
        : zlib_decompress_{std::make_unique<internal::zlib_decompress>()}
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
        auto &zstream = zlib_decompress_->stream();

        unsigned long bytes_inflated = 0;
        auto read_size_remaining = size;

        auto data_buffer = data;

        do
        {
            const auto prev_total_out = zstream.total_out;

            if (zstream.avail_in == 0)
            {
                auto read_size = source.read(std::data(input_buffer_), std::size(input_buffer_));

                if (read_size == 0)
                    break;

                zstream.next_in = reinterpret_cast<const Bytef *>(std::data(input_buffer_));
                zstream.avail_in = static_cast<uInt>(read_size);
            }

            zstream.next_out = reinterpret_cast<Bytef *>(data_buffer);
            zstream.avail_out = static_cast<uInt>(read_size_remaining);

            if (inflate(&zstream, Z_SYNC_FLUSH) != Z_OK)
                throw zlib_decompress_filter_exception{};

            bytes_inflated = zstream.total_out - prev_total_out;
            read_size_remaining -= bytes_inflated;

            data_buffer += bytes_inflated;
        } while (read_size_remaining != 0);

        return size - read_size_remaining;
    }

private:
    std::unique_ptr<internal::zlib_decompress> zlib_decompress_;
    std::array<char, decompress_buffer_size> input_buffer_;
};

} // namespace aeon::streams
