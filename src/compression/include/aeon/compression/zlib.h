// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <vector>
#include <ios>
#include <functional>
#include <memory>

namespace aeon::compression
{

namespace internal
{
class zlib_compress;
class zlib_decompress;
} // namespace internal

enum class zlib_compression_mode : int
{
    best = 9,
    balanced = 5,
    fastest = 1
};

class zlib_compress final
{
public:
    using write_callback = std::function<std::streamsize(const char *, const std::streamsize)>;

    explicit zlib_compress(const zlib_compression_mode mode, const int buffer_size = 256);
    ~zlib_compress();

    zlib_compress(zlib_compress &&) noexcept;
    auto operator=(zlib_compress &&) noexcept -> zlib_compress &;

    zlib_compress(const zlib_compress &) noexcept = delete;
    auto operator=(const zlib_compress &) noexcept -> zlib_compress & = delete;

    void write(const char *data, const std::streamsize size, const write_callback &cb);

private:
    std::unique_ptr<internal::zlib_compress> compress_;
    std::vector<char> buffer_;
};

class zlib_decompress final
{
public:
    using read_callback = std::function<std::streamsize(char *, const std::streamsize)>;

    explicit zlib_decompress(const int buffer_size = 256);
    ~zlib_decompress();

    zlib_decompress(zlib_decompress &&) noexcept;
    auto operator=(zlib_decompress &&) noexcept -> zlib_decompress &;

    zlib_decompress(const zlib_decompress &) noexcept = delete;
    auto operator=(const zlib_decompress &) noexcept -> zlib_decompress & = delete;

    auto read(char *data, const std::streamsize size, const read_callback &cb) -> std::streamsize;

private:
    std::unique_ptr<internal::zlib_decompress> decompress_;
    std::vector<char> buffer_;
};

} // namespace aeon::compression
