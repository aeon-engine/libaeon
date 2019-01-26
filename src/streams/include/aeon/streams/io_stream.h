// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/io_stream_colors_mixin.h>
#include <aeon/streams/stream.h>

namespace aeon::streams
{

class io_stream_exception : public stream_exception
{
};

class io_stream : public stream, public io_stream_colors_mixin
{
public:
    explicit io_stream(const common::flags<access_mode> mode = aeon::streams::access_mode::write);
    virtual ~io_stream() = default;

    io_stream(io_stream &&) noexcept = default;
    auto operator=(io_stream &&) noexcept -> io_stream & = default;

    io_stream(const io_stream &) = default;
    auto operator=(const io_stream &) -> io_stream & = default;

    auto read(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto write(const std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto peek(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto seek(std::ptrdiff_t pos, seek_direction direction) -> bool override;

    auto seekw(std::ptrdiff_t pos, seek_direction direction) -> bool override;

    auto tell() -> std::size_t override;

    auto tellw() -> std::size_t override;

    auto eof() const -> bool override;

    auto size() const -> std::size_t override;

    void flush() override;

    auto good() const -> bool override;
};

} // namespace aeon::streams
