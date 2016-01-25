/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#pragma once

namespace aeon
{
namespace streams
{

class stream_exception : public std::exception
{
};

/*!
 * \brief Base class for streams
 *
 * This class serves as the base class for all streams.
 * When implementing a new steam, derive from this class.
 *
 * Beware that the exact behavior of various functions may vary between stream
 * implementations.
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
     * When no parameter is given, Read-only mode is assumed.
     *
     * \param mode The access mode for the stream.
     * \sa AccessMode
     */
    stream(int mode = access_mode::read)
        : access_mode_mixin(mode)
    {
    }

    /*!
     * Destructor.
     */
    virtual ~stream()
    {
    }

    /*!
     * Read from the stream. This may move the internal read index, based on
     * the stream implementation.
     *
     * \param data Pointer to a buffer where data should be read to.
     *             Must be large enough to contain size bytes.
     * \param size Size of the data to be read.
     * \return The amount of bytes that were actually read into data. May be less
     *         than the given size.
     */
    virtual std::size_t read(std::uint8_t *data, std::size_t size) = 0;

    /*!
     * Write to the stream. This may move the internal write index, based on
     * the stream implementation.
     *
     * \param data Pointer to a buffer that contains the data to be written. Must
     *             be large enough to contain size bytes.
     * \param Size of the data to be written.
     * \return The amount of bytes that were actually written into the stream.
     *         This may be less than the given size.
     */
    virtual std::size_t write(const std::uint8_t *data, std::size_t size) = 0;

    /*!
     * Peek one byte from the stream. This is like reading 1 byte from the stream,
     * without moving the internal read index. Actual implementation may vary between
     * different stream types.
     *
     * \param data Reference to a single byte to write to
     * \param offset The offset to read from. Depending on the implementation, this
     *               offset may be relative to the current read index, and not from
     *               the beginning of the stream.
     * \return Returns true of the peek succeeded. When false is returned, the value
     *         of data is undefined.
     */
    virtual bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0) = 0;

    /*!
     * Seek within the stream. Based on the implementation, this will move the internal
     * read index.
     *
     * \param pos The position index to seek to.
     * \param direction The seek direction within the stream.
     * \return Returns true if the seek succeeded. When false is returned, the seek
     *         failed. If a seek failed, the internal read index will be restored to
     *         it's previous state.
     * \sa seek_direction
     */
    virtual bool seek(std::ptrdiff_t pos, seek_direction direction) = 0;

    /*!
     * Seek within the stream. Based on the implementation, this will move the internal
     * write index.
     *
     * \param pos The position index to seek to.
     * \param direction The seek direction within the stream.
     * \return Returns true if the seek succeeded. When false is returned, the seek
     *         failed. If a seek failed, the internal write index will be restored to
     *         it's previous state.
     * \sa seek_direction
     */
    virtual bool seekw(std::ptrdiff_t pos, seek_direction direction) = 0;

    /*!
     * Get the current value of the internal read index.
     * \return The internal read index.
     */
    virtual std::size_t tell() = 0;

    /*!
     * Get the current value of the internal write index.
     * \return The internal write index.
     */
    virtual std::size_t tellw() = 0;

    /*!
     * Check if the internal read index is at the end ("End Of File"). When this
     * returns true, all read functions will not be able to read any more data.
     * \return Returns true when the read index is at the end, false otherwise.
     */
    virtual bool eof() const = 0;

    /*!
     * Get the total size of the stream. Depending on the stream implementation,
     * a size may not be available or known. When 0 is returned, this does not mean
     * that there is no more data to read. To determine if there is more data to
     * read, use eof().
     *
     * \return The size of the stream if known, otherwise 0.
     * \sa eof()
     */
    virtual std::size_t size() const = 0;

    /*!
     * Flush the internal write buffers. Depending on the stream implementation,
     * this may have different effects. For a file stream, the file is flushed to
     * disk, but for a memory stream this function has no effect.
     */
    virtual void flush() = 0;

    /*!
     * Check if any errors were reported within this stream. For example, in a file
     * stream this may return false when the file could not be opened. When this
     * returns false, all read and write function calls are very likely to fail.
     *
     * \return Returns true if no errors were detected, false if something is wrong.
     */
    virtual bool good() const = 0;

    /*!
     * Read the entire contents of this stream into another stream. Individual stream
     * implementations may have additional overloads for specialized optimization.
     *
     * \param data Another stream
     */
    virtual void read_from_stream(stream &data)
    {
        std::vector<std::uint8_t> buffer = data.read_to_vector();
        write(&buffer[0], buffer.size());
    }

    /*!
     * Read the entire contents of this stream into an std::vector. Individual
     * stream implementations may have additional overloads for specialized optimization.
     *
     * \return A vector containing all data read from this buffer.
     */
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
