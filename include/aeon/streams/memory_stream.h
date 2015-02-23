#ifndef aeon_streams_memory_stream_h__
#define aeon_streams_memory_stream_h__

namespace aeon
{
namespace streams
{

class memory_stream : public stream
{
public:
    memory_stream() :
        stream(access_mode::read_write),
        offset_(0),
        size_(0)
    {
    }

    memory_stream(std::vector<std::uint8_t> &&buffer,
                  int mode = access_mode::read_write) :
        stream(mode),
        buffer_(std::move(buffer)),
        offset_(0),
        size_(0)
    {
        size_ = buffer_.size();
    }

    virtual ~memory_stream()
    {
    }

    virtual std::size_t read(std::uint8_t *data, std::size_t size)
    {
        if (!is_readable())
            return 0;

        // Only read what we have
        if(offset_ < size)
            size = offset_;

        // Are we really out of bounds?
        if (size <= 0)
            return 0;

        // Copy our data
        offset_ -= size;
        std::memcpy(data, &buffer_[offset_], size);

        return size;
    }

    virtual std::size_t write(const std::uint8_t *data, std::size_t size)
    {
        if (!is_writable())
            return 0;

        // Make sure we have enough space in the buffer
        reserve(offset_ + size);

        // Copy our data
        std::memcpy(&buffer_[offset_], data, size);
        offset_ += size;

        return size;
    }

    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0)
    {
        if (!is_readable() || !good())
            return false;

        if (offset_ + offset >= size_)
            return false;

        data = buffer_[offset_ + offset];
        return true;
    }

    virtual bool seek(std::ptrdiff_t pos, stream::seek_direction direction)
    {
        std::ptrdiff_t new_pos = 0;
        switch(direction)
        {
            case seek_direction::begin:
            {
                new_pos = pos;
            } break;
            case seek_direction::current:
            {
                new_pos = offset_ + pos;
            } break;
            case seek_direction::end:
            {
                new_pos = (size_ - 1) - pos;
            } break;
        };

        // Can't go higher then the size of our buffer...
        if (new_pos < 0)
            return false;

        if (new_pos >= (std::ptrdiff_t) size_)
            return false;

        // Set the new offset if all is good
        offset_ = new_pos;
        return true;
    }

    virtual bool seekw(std::ptrdiff_t pos, stream::seek_direction direction)
    {
        return false;
    }

    virtual std::size_t tell()
    {
        return offset_;
    }

    virtual std::size_t tellw()
    {
        return 0;
    }

    virtual bool eof() const
    {
        return offset_ >= size_;
    }

    virtual std::size_t size() const
    {
        return size_;
    }

    virtual void flush()
    {
    }

    virtual bool good() const
    {
        // Are we still within bounds?
        if (offset_ >= buffer_.size())
            return false;

        // All ok!
        return true;
    }

    virtual void reserve(std::size_t size)
    {
        if (size > buffer_.size())
            buffer_.resize(buffer_.size() + size);

        if (size > size_)
            size_ = size;
    }

    virtual void expand(std::size_t size)
    {
        reserve(buffer_.size() + size);
    }

    const std::uint8_t *data() const
    {
        return &buffer_[0];
    }

    virtual std::vector<std::uint8_t> read_to_vector()
    {
        return buffer_;
    }

protected:
    std::vector<std::uint8_t> buffer_;
    std::size_t offset_;
    std::size_t size_;
};

typedef std::shared_ptr<memory_stream> memory_stream_ptr;

} // namespace streams
} // namespace aeon

#endif // aeon_streams_memory_stream_h__

