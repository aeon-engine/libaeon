// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/seek_direction.h>
#include <aeon/streams/tags.h>
#include <ios>

namespace aeon::streams
{

class idynamic_stream
{
public:
    // The categories of a dynamic stream can not be known at compile time. Instead the check is done at runtime.
    struct category : input, input_seekable, output, output_seekable, flushable, has_size, has_status, has_eof
    {
    };

    virtual ~idynamic_stream() = default;

    idynamic_stream(idynamic_stream &&) noexcept = default;
    auto operator=(idynamic_stream &&) noexcept -> idynamic_stream & = default;

    idynamic_stream(const idynamic_stream &) noexcept = delete;
    auto operator=(const idynamic_stream &) noexcept -> idynamic_stream & = delete;

    virtual auto read(char *data, const std::streamsize size) -> std::streamsize = 0;

    virtual auto seekg(const std::streamoff offset, const seek_direction direction) -> bool = 0;

    [[nodiscard]] virtual auto tellg() -> std::streamoff = 0;

    virtual auto write(const char *data, const std::streamsize size) -> std::streamsize = 0;

    virtual auto seekp(const std::streamoff offset, const seek_direction direction) -> bool = 0;

    [[nodiscard]] virtual auto tellp() -> std::streamoff = 0;

    [[nodiscard]] virtual auto eof() -> bool = 0;

    [[nodiscard]] virtual auto good() -> bool = 0;

    [[nodiscard]] virtual auto fail() -> bool = 0;

    virtual void flush() = 0;

    [[nodiscard]] virtual auto size() -> std::streamoff = 0;

    [[nodiscard]] virtual auto is_input() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto is_input_seekable() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto is_output() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto is_output_seekable() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto has_eof() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto has_status() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto has_size() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto is_flushable() const noexcept -> bool = 0;

protected:
    idynamic_stream() = default;
};

} // namespace aeon::streams