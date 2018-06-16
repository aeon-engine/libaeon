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

#include <aeon/streams/memory_stream.h>

namespace aeon::streams
{

memory_stream::memory_stream()
    : stream{access_mode::read_write}
    , buffer_{}
    , offset_{0}
    , size_{0}
{
}

memory_stream::memory_stream(std::vector<std::uint8_t> &&buffer, const common::flags<access_mode> mode)
    : stream{mode}
    , buffer_{std::move(buffer)}
    , offset_{0}
    , size_{0}
{
    size_ = buffer_.size();
}

auto memory_stream::read(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw memory_stream_exception();

    if (!data || size == 0)
        throw memory_stream_exception();

    // Only read what we have
    if (offset_ + size > size_)
        size = size_ - offset_;

    // Are we really out of bounds?
    if (size == 0)
        return 0;

    std::memcpy(data, &buffer_[offset_], size);
    offset_ += size;

    return size;
}

auto memory_stream::write(const std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_writable())
        throw memory_stream_exception();

    if (!data || size == 0)
        throw memory_stream_exception();

    // Make sure we have enough space in the buffer
    reserve(offset_ + size);

    std::memcpy(&buffer_[offset_], data, size);
    offset_ += size;

    return size;
}

auto memory_stream::peek(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw memory_stream_exception();

    if (!data || size == 0)
        throw memory_stream_exception();

    // Only peek read what we have
    if (offset_ + size > size_)
        size = size_ - offset_;

    // Are we really out of bounds?
    if (size == 0)
        return 0;

    std::memcpy(data, &buffer_[offset_], size);

    return size;
}

auto memory_stream::seek(std::ptrdiff_t pos, stream::seek_direction direction) -> bool
{
    std::ptrdiff_t new_pos = 0;
    switch (direction)
    {
        case seek_direction::begin:
        {
            new_pos = pos;
        }
        break;
        case seek_direction::current:
        {
            new_pos = offset_ + pos;
        }
        break;
        case seek_direction::end:
        {
            new_pos = (size_ - 1) - pos;
        }
        break;
    }

    // Can't go higher then the size of our buffer...
    if (new_pos < 0)
        return false;

    if (new_pos >= static_cast<std::ptrdiff_t>(size_))
        return false;

    // Set the new offset if all is good
    offset_ = new_pos;
    return true;
}

auto memory_stream::seekw(std::ptrdiff_t, stream::seek_direction) -> bool
{
    return false;
}

auto memory_stream::tell() -> std::size_t
{
    return offset_;
}

auto memory_stream::tellw() -> std::size_t
{
    return 0;
}

auto memory_stream::eof() const -> bool
{
    return offset_ >= size_;
}

auto memory_stream::size() const -> std::size_t
{
    return size_;
}

void memory_stream::flush()
{
}

auto memory_stream::good() const -> bool
{
    // If the buffer is empty, and we haven't written anything, we're ok.
    if (offset_ == 0 && buffer_.empty())
        return true;

    // Are we still within bounds?
    if (offset_ >= buffer_.size())
        return false;

    // All ok!
    return true;
}

void memory_stream::reserve(std::size_t size)
{
    if (size > buffer_.size())
        buffer_.resize(buffer_.size() + size);

    if (size > size_)
        size_ = size;
}

void memory_stream::expand(std::size_t size)
{
    reserve(buffer_.size() + size);
}

auto memory_stream::read_to_vector() -> std::vector<std::uint8_t>
{
    return buffer_;
}

} // namespace aeon::streams
