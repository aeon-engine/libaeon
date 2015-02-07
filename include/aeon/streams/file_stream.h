#ifndef aeon_streams_file_stream_h__
#define aeon_streams_file_stream_h__

namespace aeon
{

class file_stream : public stream
{
public:
    file_stream(const std::string &filename, int mode);

    file_stream(const std::string &filename);

    file_stream(boost::filesystem::path path, int mode);
    file_stream(boost::filesystem::path path);

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

protected:
    std::ios::openmode access_mode_to_ios_open_mode_(int mode);
    std::ios::seekdir seek_direction_to_ios_seekdir_(seek_direction direction);

    std::fstream fstream_;
    std::size_t size_;
};

typedef std::shared_ptr<file_stream> file_stream_ptr;

} // namespace aeon

#endif // aeon_streams_file_stream_h__

