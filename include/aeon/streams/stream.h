#ifndef aeon_streams_stream_h__
#define aeon_streams_stream_h__

namespace aeon
{
namespace streams
{

/*!
 * \brief Base class for streams
 *
 * This class serves as the base class for all streams.
 * When implementing a new steam, derive from this class.
 */
class stream : public access_mode_mixin, public stream_name_mixin
{
public:
    /*!
     * The seek direction used in the Stream::Seek function. This determines
     * the behavior of the pos parameter.
     */
    enum class seek_direction
    {
        begin,   /**< Seek forwards from the beginning */
        current, /**< Seek forwards from wherever the read pointer currently
                      is */
        end      /**< Seek backwards from the end */
    };

    /*!
     * \brief Basic constructor for Stream
     *
     * This constructor will give the stream the default name as configured
     * in the AEON_STREAMS_DEFAULT_STREAM_NAME macro.
     *
     * When no parameter is given, Read-only mode is assumed.
     *
     * \param access_mode The access mode for the stream.
     * \sa AccessMode
     */
    stream(int mode = access_mode::read) :
        access_mode_mixin(mode)
    {}

    /*!
     * Destructor.
     *
     * This will call close() to let the implementation close the stream
     * properly if needed.
     */
    virtual ~stream()
    {
    }

    virtual std::size_t read(std::uint8_t *data, std::size_t size) = 0;

    virtual std::size_t write(const std::uint8_t *data,
                              std::size_t size) = 0;

    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0) = 0;

    virtual bool seek(std::ptrdiff_t pos, seek_direction direction) = 0;

    virtual bool seekw(std::ptrdiff_t pos, seek_direction direction) = 0;

    virtual std::size_t tell() = 0;

    virtual std::size_t tellw() = 0;

    virtual bool eof() const = 0;

    virtual std::size_t size() const = 0;

    virtual void flush() = 0;

    virtual bool good() const = 0;

    void read_from_stream(stream &data)
    {
        std::vector<std::uint8_t> buffer = read_to_vector();
        write(&buffer[0], buffer.size());
    }

    virtual std::vector<std::uint8_t> read_to_vector()
    {
        std::vector<std::uint8_t> buffer;
        std::size_t buff_size = size();
        buffer.resize(buff_size);
        std::size_t read_size = read(&buffer[0], buff_size);
        buffer.resize(read_size);
        return buffer;
    }
};

typedef std::shared_ptr<stream> stream_ptr;

} // namespace streams
} // namespace aeon

#endif // aeon_streams_stream_h__

