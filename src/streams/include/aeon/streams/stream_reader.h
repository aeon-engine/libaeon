/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/streams/stream.h>
#include <aeon/streams/file_stream_fwd.h>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <cstdint>
#include <cstring>

namespace aeon
{
namespace streams
{

#define STREAM_READER_READ_OPERATOR(Type)                                                                              \
    auto operator>>(Type &value)->stream_reader &                                                                      \
    {                                                                                                                  \
        if (stream_.read(reinterpret_cast<std::uint8_t *>(&value), sizeof(Type)) != sizeof(Type))                      \
        {                                                                                                              \
            throw std::runtime_error("Operator read failed on stream.");                                               \
        }                                                                                                              \
        return *this;                                                                                                  \
    }

template <typename T>
class stream_reader : common::noncopyable
{
    static constexpr int read_line_block_size = 64;

public:
    explicit stream_reader(T &streamref);

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

    auto read_as_string() const;

    template <class U = T>
    auto read_line() -> typename std::enable_if<std::is_same<U, file_stream>::value, std::string>::type;

    template <class U = T>
    auto read_line() -> typename std::enable_if<!std::is_same<U, file_stream>::value, std::string>::type;

    auto &internal_stream();

protected:
    T &stream_;
};

template <typename T>
stream_reader<T>::stream_reader(T &streamref)
    : stream_(streamref)
{
}

template <typename T>
auto stream_reader<T>::read_as_string() const
{
    auto vector = stream_.read_to_vector();
    return std::string(vector.begin(), vector.end());
}

template <typename T>
template <typename U>
auto stream_reader<T>::read_line() -> typename std::enable_if<std::is_same<U, file_stream>::value, std::string>::type
{
    return stream_.read_line();
}

template <typename T>
template <typename U>
auto stream_reader<T>::read_line() -> typename std::enable_if<!std::is_same<U, file_stream>::value, std::string>::type
{
    std::string line;
    std::size_t peek_size;
    char peek_data[read_line_block_size] = {};
    while ((peek_size = stream_.read(reinterpret_cast<std::uint8_t *>(peek_data), read_line_block_size)) > 0)
    {
        const char *line_end = std::strchr(peek_data, '\n');
        if (!line_end)
        {
            line.append(peek_data, peek_size);
        }
        else
        {
            std::ptrdiff_t temp_size = line_end - peek_data;
            line.append(peek_data, temp_size);

            std::ptrdiff_t jump_back = (static_cast<std::ptrdiff_t>(peek_size) - temp_size) - 1;

            if (jump_back == 0)
                break;

            if (!stream_.seek(-jump_back, T::seek_direction::current))
                throw stream_exception();

            break;
        }
    }

    if (!line.empty())
    {
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
    }

    return line;
}

template <typename T>
inline auto &stream_reader<T>::internal_stream()
{
    return stream_;
}

} // namespace streams
} // namespace aeon
