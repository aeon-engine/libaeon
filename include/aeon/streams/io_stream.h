#ifndef aeon_streams_io_stream_h__
#define aeon_streams_io_stream_h__

namespace aeon
{
namespace streams
{

class io_stream : public stream, public io_stream_colors_mixin
{
public:
    io_stream(int mode = aeon::streams::access_mode::write);

    virtual std::size_t read(std::uint8_t *data, std::size_t size);

    virtual std::size_t write(const std::uint8_t *data,
        std::size_t size);

    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0);

    virtual bool seek(std::ptrdiff_t pos, seek_direction direction);

    virtual bool seekw(std::ptrdiff_t pos, seek_direction direction);

    virtual std::size_t tell();

    virtual std::size_t tellw();

    virtual bool eof() const;

    virtual std::size_t size() const;

    virtual void flush();

    virtual bool good() const;
};

typedef std::shared_ptr<io_stream> io_stream_ptr;

} // namespace streams
} // namespace aeon

#endif //aeon_streams_io_stream_h__
