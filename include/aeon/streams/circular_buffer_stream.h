#ifndef aeon_streams_circular_buffer_stream_h__
#define aeon_streams_circular_buffer_stream_h__

namespace aeon
{
namespace streams
{

/*!
 * \brief Circular Buffer Stream
 *
 * This class is mainly used as a circular buffer for TCP packet handling. The
 * template int value given will be the size of the buffer. If there is more
 * data written than read, write will fail and no more data will be written
 * until the buffer is emptied again with read. Be sure to make the buffer
 * large enough for your use-case.
 */
template<int circular_buffer_size>
class circular_buffer_stream : public stream
{
public:
    /*!
     * \brief Default constructor
     *
     * This is the main constructor for this circular buffer.
     */
    circular_buffer_stream() :
        tail_(0),
        head_(0),
        size_(0)
    {
    }

    /*!
     * Move constructor
     */
    circular_buffer_stream(circular_buffer_stream &&other) :
        buffer_(std::move(other.buffer_)),
        tail_(std::move(other.tail_)),
        head_(std::move(other.head_)),
        size_(std::move(other.size_))
    {
    }

    /*!
     * Destructor
     */
    ~circular_buffer_stream()
    {
    }

    /*!
     * Read raw data from the circular buffer. The data will be read from the
     * beginning of the buffer. If there is more data read than is being
     * written, this function will return false.
     *
     * \param data The destination of the data to be read from the circular
                   buffer.
     * \param size The size of the data to be read. The data parameter must be
                   large enough to hold this size.
     * \return The size read from the circular buffer or 0.
     */
    virtual std::size_t read(std::uint8_t *data, std::size_t size)
    {
        // Can we read this size at all?
        if (is_out_of_bounds_(size))
            return 0;

        // Do we have this many bytes in the buffer?
        if (size > size_)
            return 0;

        std::size_t bytes_to_read = size;
        std::size_t write_offset = 0;

        // If we can't read everything at once, read the first part
        if (is_out_of_bounds_(size + tail_))
        {
            std::size_t bytes_until_end = circular_buffer_size - tail_;
            std::memcpy(data, &buffer_.data()[tail_], bytes_until_end);
            bytes_to_read -= bytes_until_end;
            write_offset = bytes_until_end;
            tail_ = 0;
        }

        // Do we have anything left to read?
        if (bytes_to_read > 0)
        {
            std::memcpy(&data[write_offset],
                &buffer_.data()[tail_], bytes_to_read);

            tail_ += bytes_to_read;
        }

        // Update the size of the buffer
        size_ -= size;

        return size;
    }

    /*!
     * Write raw data into the circular buffer. The data will be written at the
     * end of the buffer. If there is more data written than being read, this
     * function will return false and will not write anything into the buffer.
     * Trying to write more bytes than the size of the circular buffer itself
     * will fail and the function will return false.
     *
     * \param data The data to be written into the circular buffer.
     * \param size The size of the data that *data is pointing to.
     * \return The size of the buffer written into the circular buffer,
               or 0 on error.
     */
    virtual std::size_t write(const std::uint8_t *data, std::size_t size)
    {
        // Can we fit this in at all?
        if (is_out_of_bounds_(size))
            return 0;

        // We are about to overwrite data that was not yet read. Abort.
        if (!fits_in_buffer(size))
            return 0;

        std::size_t bytes_to_write = size;
        std::size_t read_offset = 0;

        // If this doesn't fit, we loop around
        if (is_out_of_bounds_(size + head_))
        {
            std::size_t bytes_until_end = circular_buffer_size - head_;
            bytes_to_write -= bytes_until_end;
            read_offset = bytes_until_end;

            std::memcpy(&buffer_.data()[head_], data, bytes_until_end);

            head_ = 0;
        }

        // Do we still have anything to write?
        if (bytes_to_write > 0)
        {
            std::memcpy(&buffer_.data()[head_],
                &data[read_offset], bytes_to_write);

            head_ += bytes_to_write;
        }

        // Finally check if we're at the end of the buffer
        if (head_ >= circular_buffer_size)
            head_ = 0;

        // Update the size of the buffer
        size_ += size;

        return size;
    }

    /*!
     * Read 1 byte from the circular buffer without moving the internal read
     * pointer.
     *
     * \return The byte at the current read offset.
     */
    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0)
    {
        if (offset < 0)
            return false;

        if (size_ == 0 || (std::size_t) offset > size_)
            return false;

        std::ptrdiff_t normalized_offset = offset % circular_buffer_size;

        data = buffer_[tail_ + normalized_offset];
        return true;
    }

    virtual bool seek(std::ptrdiff_t,
                      stream::seek_direction)
    {
        return false;
    }

    virtual bool seekw(std::ptrdiff_t, stream::seek_direction)
    {
        return false;
    }

    virtual std::size_t tell()
    {
        return tail_;
    }

    virtual std::size_t tellw()
    {
        return head_;
    }

    virtual bool eof() const
    {
        return size_ == circular_buffer_size;
    }

    /*!
     * Get the amount of bytes written into this circular buffer. This size is
     * updated after each read and write accordingly.
     *
     * \return The amount of bytes written into this circular buffer.
     */
    virtual std::size_t size() const
    {
        return size_;
    }

    virtual void flush()
    {
    }

    virtual bool good() const
    {
        return true;
    }

    /*!
     * Get the maximum amount of bytes that can be written into this circular
     * buffer. This size is always equal to the size given to the template
     * parameter.
     *
     * \return The maximum amount of bytes that can be written
     */
    std::size_t max_size() const
    {
        return circular_buffer_size;
    }

    /*!
     * Move operator
     */
    circular_buffer_stream& operator=(circular_buffer_stream &&other)
    {
        buffer_ = std::move(other.buffer_);
        tail_ = std::move(other.tail_);
        head_ = std::move(other.head_);
        size_ = std::move(other.size_);
        return *this;
    }

protected:
    bool is_out_of_bounds_(std::size_t offset)
    {
        return (offset > circular_buffer_size);
    }

    bool fits_in_buffer(std::size_t size)
    {
        return ((size_ + size) <= circular_buffer_size);
    }

    std::array<std::uint8_t, circular_buffer_size> buffer_;
    std::size_t tail_;
    std::size_t head_;
    std::size_t size_;
};

} // namespace streams
} // namespace aeon

#endif // aeon_streams_circular_buffer_stream_h__

