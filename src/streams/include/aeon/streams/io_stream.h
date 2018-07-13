/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
