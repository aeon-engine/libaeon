#ifndef aeon_streams_stream_writer_h__
#define aeon_streams_stream_writer_h__

namespace aeon
{

class stream;
class stream_writer
{
public:
    stream_writer(stream &streamref) :
        stream_(streamref)
    {
    }

    ~stream_writer()
    {
    }

#define STREAM_WRITER_WRITE_OPERATOR(Type) \
    stream_writer &operator<<(Type &value) \
    { \
        if (stream_.write((std::uint8_t *) &value, \
            sizeof(Type)) != sizeof(Type)) \
        { \
            throw std::runtime_error("Operator write failed on stream."); \
        } \
        return *this; \
    }

    STREAM_WRITER_WRITE_OPERATOR(std::int8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int64_t)

    STREAM_WRITER_WRITE_OPERATOR(std::uint8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint64_t)

    STREAM_WRITER_WRITE_OPERATOR(float)
    STREAM_WRITER_WRITE_OPERATOR(double)

protected:
    stream &stream_;
};

} // namespace aeon

#endif // aeon_streams_stream_writer_h__

