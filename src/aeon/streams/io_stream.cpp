/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/streams.h>

namespace aeon
{
namespace streams
{

io_stream::io_stream(int mode /*= aeon::streams::access_mode::write*/)
    : aeon::streams::stream(mode)
{
}

std::size_t io_stream::read(std::uint8_t *data, std::size_t size)
{
    if (!is_readable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fread(data, 1, size, stdin);
}

std::size_t io_stream::write(const std::uint8_t *data, std::size_t size)
{
    if (!is_writable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fwrite(data, 1, size, stdout);
}

bool io_stream::peek(std::uint8_t &data, std::ptrdiff_t /*= 0*/)
{
    if (!is_readable())
        throw io_stream_exception();

    int c = fgetc(stdin);

    if (c == EOF)
        return false;

    // TODO: research if there is a good alternative for this.
    if (ungetc(c, stdin) == EOF)
        return false;

    data = static_cast<std::uint8_t>(c);
    return true;
}

bool io_stream::seek(std::ptrdiff_t, seek_direction)
{
    return false;
}

bool io_stream::seekw(std::ptrdiff_t, seek_direction)
{
    return false;
}

std::size_t io_stream::tell()
{
    return 0;
}

std::size_t io_stream::tellw()
{
    return 0;
}

bool io_stream::eof() const
{
    return (feof(stdin) != 0);
}

void io_stream::flush()
{
    fflush(stdout);
}

std::size_t io_stream::size() const
{
    return 0;
}

bool io_stream::good() const
{
    return true;
}

} // namespace streams
} // namespace aeon
