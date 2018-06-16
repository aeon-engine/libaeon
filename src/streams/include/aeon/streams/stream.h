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

#pragma once

#include <aeon/streams/access_mode_mixin.h>
#include <aeon/streams/stream_name_mixin.h>
#include <aeon/common/noncopyable.h>

#include <vector>
#include <cstddef>
#include <cstdint>

namespace aeon::streams
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
    stream(const common::flags<access_mode> mode = access_mode::read)
        : access_mode_mixin{mode}
    {
    }

    /*!
     * Destructor.
     */
    virtual ~stream() = default;

    stream(stream &&) = default;
    auto operator=(stream &&) -> stream & = default;

    stream(const stream &) = default;
    auto operator=(const stream &) -> stream & = default;

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
    virtual auto read(std::uint8_t *data, std::size_t size) -> std::size_t = 0;

    /*!
     * Read from the stream. This may move the internal read index, based on
     * the stream implementation.
     *
     * \param data Vector to where data should be read to.
     *             The vector will be resized to fit size bytes.
     * \param size Size of the data to be read.
     * \return The amount of bytes that were actually read into data. May be less
     *         than the given size.
     */
    virtual auto vector_read(std::vector<std::uint8_t> &data, std::size_t size) -> std::size_t
    {
        data.resize(size);
        const auto result = read(data.data(), size);
        data.resize(result);
        return result;
    }

    /*!
     * Write to the stream. This may move the internal write index, based on
     * the stream implementation.
     *
     * \param data Pointer to a buffer that contains the data to be written. Must
     *             be large enough to contain size bytes.
     * \param size of the data to be written.
     * \return The amount of bytes that were actually written into the stream.
     *         This may be less than the given size.
     */
    virtual auto write(const std::uint8_t *data, std::size_t size) -> std::size_t = 0;

    /*!
     * Write to the stream. This may move the internal write index, based on
     * the stream implementation.
     *
     * \param data Vector containing the data to be written.
     * \return The amount of bytes that were actually written into the stream.
     *         This may be less than the given size.
     */
    auto vector_write(const std::vector<uint8_t> &data) -> std::size_t
    {
        return write(data.data(), data.size());
    }

    /*!
     * Peek bytes from the stream. This is like reading bytes from the stream,
     * without moving the internal read index. Actual implementation may vary between
     * different stream types.
     *
     * \param data Pointer to a buffer where data should be peeked to.
     *             Must be large enough to contain size bytes.
     * \param size Size of the data to be peek.
     * \return The amount of bytes that were actually peeked into data. May be less
     *         than the given size.
     */
    virtual auto peek(std::uint8_t *data, std::size_t size) -> std::size_t = 0;

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
    virtual auto seek(std::ptrdiff_t pos, seek_direction direction) -> bool = 0;

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
    virtual auto seekw(std::ptrdiff_t pos, seek_direction direction) -> bool = 0;

    /*!
     * Get the current value of the internal read index.
     * \return The internal read index.
     */
    virtual auto tell() -> std::size_t = 0;

    /*!
     * Get the current value of the internal write index.
     * \return The internal write index.
     */
    virtual auto tellw() -> std::size_t = 0;

    /*!
     * Check if the internal read index is at the end ("End Of File"). When this
     * returns true, all read functions will not be able to read any more data.
     * \return Returns true when the read index is at the end, false otherwise.
     */
    virtual auto eof() const -> bool = 0;

    /*!
     * Get the total size of the stream. Depending on the stream implementation,
     * a size may not be available or known. When 0 is returned, this does not mean
     * that there is no more data to read. To determine if there is more data to
     * read, use eof().
     *
     * \return The size of the stream if known, otherwise 0.
     * \sa eof()
     */
    virtual auto size() const -> std::size_t = 0;

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
    virtual auto good() const -> bool = 0;

    /*!
     * Read the entire contents of this stream into another stream. Individual stream
     * implementations may have additional overloads for specialized optimization.
     *
     * \param data Another stream
     */
    virtual void read_from_stream(stream &data)
    {
        auto buffer = data.read_to_vector();
        write(&buffer[0], buffer.size());
    }

    /*!
     * Read the entire contents of this stream into an std::vector. Individual
     * stream implementations may have additional overloads for specialized optimization.
     *
     * \return A vector containing all data read from this buffer.
     */
    virtual auto read_to_vector() -> std::vector<std::uint8_t>
    {
        const auto buff_size = size();

        if (buff_size == 0)
            return {};

        std::vector<std::uint8_t> buffer;
        buffer.resize(buff_size);
        const auto read_size = read(&buffer[0], buff_size);
        buffer.resize(read_size);
        return buffer;
    }

    /*!
     * Check if the stream actually contains data (size == 0). In some stream
     * implementations, this can be more efficient than simply checking the size.
     *
     * \return False if there is no data in the stream that can be read.
     */
    virtual auto empty() const -> bool
    {
        return size() == 0;
    }

    /*!
     * Check if this stream is of a certain type.
     */
    template <typename T>
    auto is() const -> bool
    {
        return dynamic_cast<const T *const>(this) != nullptr;
    }

    /*!
     * Use this stream as a certain type. Only use when this stream is of this type;
     * there are no checks done if this is actually the case. Use is() to check this.
     */
    template <typename T>
    auto as() -> T &
    {
        return *(dynamic_cast<T *>(this));
    }
};

} // namespace aeon::streams
