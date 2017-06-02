/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/streams/stream.h>
#include <cstring>

namespace aeon
{
namespace streams
{

class memory_stream_exception : public stream_exception
{
};

class memory_stream : public stream
{
public:
    memory_stream();

    explicit memory_stream(std::vector<std::uint8_t> &&buffer, int mode = access_mode::read_write);

    virtual ~memory_stream() = default;

    memory_stream(memory_stream &&o) = default;
    memory_stream &operator=(memory_stream &&other) = default;

    auto read(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto write(const std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto peek(std::uint8_t *data, std::size_t size) -> std::size_t override;

    auto seek(std::ptrdiff_t pos, stream::seek_direction direction) -> bool override;

    auto seekw(std::ptrdiff_t /* pos */, stream::seek_direction /* direction */) -> bool override;

    auto tell() -> std::size_t override;

    auto tellw() -> std::size_t override;

    auto eof() const -> bool override;

    auto size() const -> std::size_t override;

    void flush() override;

    auto good() const -> bool override;

    void reserve(std::size_t size);

    void expand(std::size_t size);

    auto read_to_vector() -> std::vector<std::uint8_t> override;

    auto data() const;

protected:
    std::vector<std::uint8_t> buffer_;
    std::size_t offset_;
    std::size_t size_;
};

inline auto memory_stream::data() const
{
    return &buffer_[0];
}

} // namespace streams
} // namespace aeon
