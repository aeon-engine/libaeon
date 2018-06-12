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

#include <aeon/streams/io_stream.h>

#include <limits>

namespace aeon::streams
{

io_stream::io_stream(int mode /*= aeon::streams::access_mode::write*/)
    : aeon::streams::stream(mode)
{
}

auto io_stream::read(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fread(data, 1, size, stdin);
}

auto io_stream::write(const std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_writable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fwrite(data, 1, size, stdout);
}

auto io_stream::peek(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw io_stream_exception();

    if (size > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
        throw io_stream_exception();

    auto max_count = static_cast<std::ptrdiff_t>(size);

    int c;
    std::ptrdiff_t count = 0;
    while ((c = fgetc(stdin)) != EOF && count < max_count)
    {
        data[count] = static_cast<std::uint8_t>(c);
        count++;
    }

    for (std::ptrdiff_t i = count; i >= 0; --i)
    {
        c = data[i];

        // TODO: research if there is a good alternative for this.
        if (ungetc(c, stdin) == EOF)
            // \note This is actually a really weird that this error could occur.
            //       The point is, is that when we where able to get the chars
            //       theoretically we should be able to put them back.
            throw io_stream_exception();
    }

    return static_cast<std::size_t>(count);
}

auto io_stream::seek(std::ptrdiff_t, seek_direction) -> bool
{
    return false;
}

auto io_stream::seekw(std::ptrdiff_t, seek_direction) -> bool
{
    return false;
}

auto io_stream::tell() -> std::size_t
{
    return 0;
}

auto io_stream::tellw() -> std::size_t
{
    return 0;
}

auto io_stream::eof() const -> bool
{
    return (feof(stdin) != 0);
}

void io_stream::flush()
{
    fflush(stdout);
}

auto io_stream::size() const -> std::size_t
{
    return 0;
}

auto io_stream::good() const -> bool
{
    return true;
}

} // namespace aeon::streams
