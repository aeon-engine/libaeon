#ifndef aeon_streams_stream_reader_h__
#define aeon_streams_stream_reader_h__

namespace aeon
{
namespace streams
{

class stream;
class stream_reader
{
public:
    stream_reader(stream &streamref) :
        stream_(streamref)
    {
    }

    ~stream_reader()
    {
    }

    stream_reader& operator=(const stream_reader &) = delete;

#define STREAM_READER_READ_OPERATOR(Type) \
    stream_reader &operator>>(Type &value) \
    { \
        if (stream_.read((std::uint8_t *) &value, \
            sizeof(Type)) != sizeof(Type)) \
        { \
            throw std::runtime_error("Operator read failed on stream."); \
        } \
        return *this; \
    }

    STREAM_READER_READ_OPERATOR(std::int8_t)
    STREAM_READER_READ_OPERATOR(std::int16_t)
    STREAM_READER_READ_OPERATOR(std::int32_t)
    STREAM_READER_READ_OPERATOR(std::int64_t)

    STREAM_READER_READ_OPERATOR(std::uint8_t)
    STREAM_READER_READ_OPERATOR(std::uint16_t)
    STREAM_READER_READ_OPERATOR(std::uint32_t)
    STREAM_READER_READ_OPERATOR(std::uint64_t)

    STREAM_READER_READ_OPERATOR(float)
    STREAM_READER_READ_OPERATOR(double)

    std::string read_line()
    {
        std::uint8_t peek_data = 0;
        std::ptrdiff_t offset = 0;
        std::size_t stringlength = 0;

        while (stream_.peek(peek_data, offset++))
        {
            ++stringlength;

            if (peek_data == '\n')
                break;
        }

        if (stringlength == 0)
            return std::string();

        std::string line;
        line.resize(stringlength);
        stringlength = stream_.read((std::uint8_t *) &line[0], stringlength);

        if (stringlength == 0)
            return std::string();

        int strip_characters = 1;

        if (stringlength >= 2)
        {
            if (line[stringlength - 2] == '\r')
                ++strip_characters;
        }

        line.resize(stringlength - strip_characters);

        return line;
    }

protected:
    stream &stream_;
};

} // namespace streams
} // namespace aeon

#endif // aeon_streams_stream_reader_h__

