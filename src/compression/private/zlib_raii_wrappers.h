// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/compression/exception.h>
#include <aeon/compression/zlib.h>

#define ZLIB_CONST
#include <zlib.h>
#undef ZLIB_CONST

namespace aeon::compression::internal
{

class zlib_compress final
{
public:
    explicit zlib_compress(const int level)
        : zstream_{}
    {
        if (deflateInit(&zstream_, level) != Z_OK)
            throw zlib_compress_exception{};
    }

    zlib_compress(zlib_compress &&) noexcept = delete;
    auto operator=(zlib_compress &&) noexcept -> zlib_compress & = delete;

    zlib_compress(const zlib_compress &) noexcept = delete;
    auto operator=(const zlib_compress &) noexcept -> zlib_compress & = delete;

    ~zlib_compress()
    {
        deflateEnd(&zstream_);
    }

    [[nodiscard]] auto stream() noexcept -> z_stream &
    {
        return zstream_;
    }

private:
    z_stream zstream_;
};

class zlib_decompress final
{
public:
    explicit zlib_decompress()
        : zstream_{}
    {
        if (inflateInit(&zstream_) != Z_OK)
            throw zlib_compress_exception{};
    }

    zlib_decompress(zlib_decompress &&) noexcept = delete;
    auto operator=(zlib_decompress &&) noexcept -> zlib_decompress & = delete;

    zlib_decompress(const zlib_decompress &) noexcept = delete;
    auto operator=(const zlib_decompress &) noexcept -> zlib_decompress & = delete;

    ~zlib_decompress()
    {
        inflateEnd(&zstream_);
    }

    [[nodiscard]] auto stream() noexcept -> z_stream &
    {
        return zstream_;
    }

private:
    z_stream zstream_;
};

} // namespace aeon::compression::internal
