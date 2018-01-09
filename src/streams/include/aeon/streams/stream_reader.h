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

#include <aeon/common/literals.h>
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

template <typename T>
class stream_reader : common::noncopyable
{
    static constexpr int read_line_block_size = 64;

public:
    explicit stream_reader(T &streamref);

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
    auto peek_size = 0_size_t;
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
            const auto temp_size = line_end - peek_data;
            line.append(peek_data, temp_size);

            const auto jump_back = (static_cast<std::ptrdiff_t>(peek_size) - temp_size) - 1;

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

template <typename T, typename U, class = typename std::enable_if<std::is_pod<U>::value>::type>
inline auto &operator>>(stream_reader<T> &writer, U &val)
{
    if (writer.internal_stream().read(reinterpret_cast<std::uint8_t *>(&val), sizeof(U)) != sizeof(U))
        throw std::runtime_error("Operator read failed on stream.");

    return writer;
}

} // namespace streams
} // namespace aeon
