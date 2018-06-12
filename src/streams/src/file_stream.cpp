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

#include <aeon/streams/file_stream.h>

namespace aeon::streams
{

file_stream::file_stream(const std::string &filename, int mode, file_mode fm /*= file_mode::binary*/)
    : file_stream(std::filesystem::path(filename), mode, fm)
{
}

file_stream::file_stream(const std::string &filename, file_mode fm /*= file_mode::binary*/)
    : file_stream(std::filesystem::path(filename), access_mode::read, fm)
{
}

file_stream::file_stream(const std::filesystem::path &path, int mode, file_mode fm)
    : stream(mode)
    , size_(0)
    , filename_(path.string())
{
    fstream_.open(path, to_ios_open_mode_(mode, fm));

    if (!fstream_.good())
        throw file_stream_exception();

    // Note: We can not call is_readable here since it's a virtual method.
    if (fstream_.good() && ((access_mode_ & access_mode::read) != 0))
    {
        fstream_.seekg(0, std::ios::end);
        size_ = static_cast<std::size_t>(fstream_.tellg());
        fstream_.seekg(0, std::ios::beg);
    }
}

file_stream::file_stream(const std::filesystem::path &path, file_mode fm)
    : file_stream(path, access_mode::read, fm)
{
}

auto file_stream::read(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.read(reinterpret_cast<char *>(data), size);

    if (fstream_)
        return size;

    return static_cast<std::size_t>(fstream_.gcount());
}

auto file_stream::write(const std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_writable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.write(reinterpret_cast<const char *>(data), size);

    if (fstream_.fail())
        return 0;

    return size;
}

auto file_stream::peek(std::uint8_t *data, std::size_t size) -> std::size_t
{
    if (!is_readable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    std::size_t original_offset = static_cast<std::size_t>(fstream_.tellg());

    fstream_.read(reinterpret_cast<char *>(data), size);

    if (fstream_.eof())
    {
        std::size_t peek_count = static_cast<std::size_t>(fstream_.gcount());

        fstream_.seekg(original_offset, std::ios::beg);

        return peek_count;
    }

    if (fstream_.fail())
    {
        fstream_.clear();
        fstream_.seekg(original_offset, std::ios::beg);
        return 0;
    }

    fstream_.seekg(original_offset, std::ios::beg);

    return size;
}

auto file_stream::seek(std::ptrdiff_t pos, seek_direction direction) -> bool
{
    if (!is_readable())
        throw file_stream_exception();

    // Make sure all failure bits are cleared before seeking.
    // This can happen if read didn't manage to read all requested characters.
    fstream_.clear();

    fstream_.seekg(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

auto file_stream::seekw(std::ptrdiff_t pos, seek_direction direction) -> bool
{
    if (!is_writable())
        throw file_stream_exception();

    fstream_.seekp(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

auto file_stream::tell() -> std::size_t
{
    if (!is_readable())
        throw file_stream_exception();

    return static_cast<std::size_t>(fstream_.tellg());
}

auto file_stream::tellw() -> std::size_t
{
    if (!is_writable())
        throw file_stream_exception();

    return static_cast<std::size_t>(fstream_.tellp());
}

auto file_stream::eof() const -> bool
{
    return fstream_.eof();
}

auto file_stream::size() const -> std::size_t
{
    return size_;
}

void file_stream::flush()
{
    fstream_.flush();
}

auto file_stream::good() const -> bool
{
    return fstream_.good();
}

auto file_stream::to_ios_open_mode_(int mode, file_mode fm) const -> std::ios::openmode
{
    auto openmode_zero = static_cast<std::ios::openmode>(0);

    auto m = (fm == file_mode::binary) ? std::fstream::binary : openmode_zero;
    m |= (mode & access_mode::read) ? std::fstream::in : openmode_zero;
    m |= (mode & access_mode::write) ? std::fstream::out : openmode_zero;
    m |= (mode & access_mode::truncate) ? std::fstream::trunc : openmode_zero;
    return m;
}

auto file_stream::seek_direction_to_ios_seekdir_(seek_direction direction) const -> std::ios::seekdir
{
    switch (direction)
    {
        case (seek_direction::begin):
            return std::ios::beg;
        case (seek_direction::current):
            return std::ios::cur;
        case (seek_direction::end):
            return std::ios::end;
    }

    return std::ios::cur;
}

auto file_stream::read_line() -> std::string
{
    if (!is_readable())
        throw file_stream_exception();

    if (eof())
        throw file_stream_exception();

    std::string line;
    std::getline(fstream_, line);
    line.erase(line.find_last_not_of("\n\r") + 1);
    return line;
}

void file_stream::write_line(const std::string &line)
{
    if (!is_writable())
        throw file_stream_exception();

    fstream_ << line << std::endl;
}

auto file_stream::get_filename() const -> const std::string &
{
    return filename_;
}

} // namespace aeon::streams
