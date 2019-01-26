// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/io_stream.h>

#include <limits>

namespace aeon::streams
{

io_stream::io_stream(const common::flags<access_mode> mode /*= aeon::streams::access_mode::write*/)
    : stream{mode}
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

    const auto max_count = static_cast<std::ptrdiff_t>(size);

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
