// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/compression/zlib.h>
#include <aeon/common/assert.h>
#include "zlib_raii_wrappers.h"

namespace aeon::compression
{

zlib_compress::zlib_compress(const zlib_compression_mode mode, const int buffer_size)
    : compress_{std::make_unique<internal::zlib_compress>(static_cast<int>(mode))}
    , buffer_{}
{
    buffer_.resize(buffer_size);
}

zlib_compress::~zlib_compress() = default;

zlib_compress::zlib_compress(zlib_compress &&) noexcept = default;

auto zlib_compress::operator=(zlib_compress &&) noexcept -> zlib_compress & = default;

void zlib_compress::write(const char *data, const std::streamsize size, const write_callback &cb)
{
    compress_->stream().avail_in = static_cast<uInt>(size);
    compress_->stream().next_in = reinterpret_cast<const unsigned char *>(data);

    do
    {
        compress_->stream().avail_out = static_cast<uInt>(std::size(buffer_));
        compress_->stream().next_out = reinterpret_cast<unsigned char *>(std::data(buffer_));
        if (deflate(&compress_->stream(), Z_SYNC_FLUSH) != Z_OK)
            throw zlib_compress_exception{};

        const auto write_size = static_cast<std::streamsize>(std::size(buffer_) - compress_->stream().avail_out);
        aeon_assert(write_size >= 0, "Zlib compress write size can't be < 0.");

        if (write_size != 0)
        {
            if (cb(std::data(buffer_), write_size) != write_size)
                throw zlib_compress_exception{};
        }
    } while (compress_->stream().avail_out == 0);

    aeon_assert(compress_->stream().avail_in == 0, "Did not write all expected compressed bytes.");
}

zlib_decompress::zlib_decompress(const int buffer_size)
    : decompress_{std::make_unique<internal::zlib_decompress>()}
    , buffer_{}
{
    buffer_.resize(buffer_size);
}

zlib_decompress::~zlib_decompress() = default;

zlib_decompress::zlib_decompress(zlib_decompress &&) noexcept = default;

auto zlib_decompress::operator=(zlib_decompress &&) noexcept -> zlib_decompress & = default;

auto zlib_decompress::read(char *data, const std::streamsize size, const read_callback &cb) -> std::streamsize
{
    auto &zstream = decompress_->stream();

    auto read_size_remaining = size;
    auto data_buffer = data;

    do
    {
        const auto prev_total_out = zstream.total_out;

        if (zstream.avail_in == 0)
        {
            const auto read_size = cb(std::data(buffer_), std::size(buffer_));

            if (read_size == 0)
                break;

            zstream.next_in = reinterpret_cast<const Bytef *>(std::data(buffer_));
            zstream.avail_in = static_cast<uInt>(read_size);
        }

        zstream.next_out = reinterpret_cast<Bytef *>(data_buffer);
        zstream.avail_out = static_cast<uInt>(read_size_remaining);

        if (inflate(&zstream, Z_SYNC_FLUSH) != Z_OK)
            throw zlib_decompress_exception{};

        const auto bytes_inflated = zstream.total_out - prev_total_out;
        read_size_remaining -= bytes_inflated;

        data_buffer += bytes_inflated;
    } while (read_size_remaining != 0);

    return size - read_size_remaining;
}

} // namespace aeon::compression
