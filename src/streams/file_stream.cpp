#include <aeon/streams.h>

namespace aeon
{
namespace streams
{

file_stream::file_stream(const std::string &filename, int mode) :
    stream(mode),
    size_(0)
{
    fstream_.open(filename, access_mode_to_ios_open_mode_(mode));

    if (fstream_.good() && is_readable())
    {
        fstream_.seekg(0, std::ios::end);
        size_ = fstream_.tellg();
        fstream_.seekg(0, std::ios::beg);
    }
}

file_stream::file_stream(const std::string &filename) :
    file_stream(filename, access_mode::read)
{
}

file_stream::file_stream(boost::filesystem::path path, int mode) :
    file_stream(path.string(), mode)
{
}

file_stream::file_stream(boost::filesystem::path path) :
    file_stream(path.string())
{
}

std::size_t file_stream::read(std::uint8_t *data, std::size_t size)
{
    if (!is_readable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.read((char *)data, size);

    if (fstream_.eof())
        return fstream_.gcount();

    if (fstream_.fail())
        return 0;

    return size;
}

std::size_t file_stream::write(const std::uint8_t *data,
    std::size_t size)
{
    if (!is_writable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.write((const char *)data, size);

    if (fstream_.fail())
        return 0;

    return size;
}

bool file_stream::peek(std::uint8_t &data, std::ptrdiff_t offset /* = 0 */)
{
    if (!is_readable())
        throw file_stream_exception();

    std::size_t original_offset = 0;

    if (offset != 0)
    {
        original_offset = fstream_.tellg();
        fstream_.seekg(original_offset + offset, std::ios::beg);

        if (fstream_.fail())
            return false;
    }

    int peek_val = fstream_.peek();

    if (peek_val == EOF)
        return false;

    data = (std::uint8_t) peek_val;

    if (offset != 0)
        fstream_.seekg(original_offset, std::ios::beg);

    return true;
}

bool file_stream::seek(std::ptrdiff_t pos, seek_direction direction)
{
    if (!is_readable())
        throw file_stream_exception();

    fstream_.seekg(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

bool file_stream::seekw(std::ptrdiff_t pos, seek_direction direction)
{
    if (!is_writable())
        throw file_stream_exception();

    fstream_.seekp(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

std::size_t file_stream::tell()
{
    if (!is_readable())
        throw file_stream_exception();

    return fstream_.tellg();
}

std::size_t file_stream::tellw()
{
    if (!is_writable())
        throw file_stream_exception();

    return fstream_.tellp();
}

bool file_stream::eof() const
{
    return fstream_.eof();
}

std::size_t file_stream::size() const
{
    return size_;
}

void file_stream::flush()
{
    fstream_.flush();
}

bool file_stream::good() const
{
    return fstream_.good();
}

std::ios::openmode file_stream::access_mode_to_ios_open_mode_(int mode)
{
    std::ios_base::openmode m = 0;
    m |= (mode & access_mode::read) ? std::fstream::in : 0;
    m |= (mode & access_mode::write) ? std::fstream::out : 0;
    m |= (mode & access_mode::text) ? 0 : std::fstream::binary;
    m |= (mode & access_mode::truncate) ? std::fstream::trunc : 0;
    return m;
}

std::ios::seekdir file_stream::seek_direction_to_ios_seekdir_(
    seek_direction direction)
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

bool file_stream::read_line(std::string &line)
{
    if (!is_text() || !is_readable())
        throw file_stream_exception();

    if (eof())
        return false;

    std::getline(fstream_, line);
    line.erase(line.find_last_not_of("\n\r") + 1);
    return true;
}

void file_stream::write_line(const std::string &line)
{
    if (!is_text() || !is_writable())
        throw file_stream_exception();

    fstream_ << line << std::endl;
}

} // namespace streams
} // namespace aeon
