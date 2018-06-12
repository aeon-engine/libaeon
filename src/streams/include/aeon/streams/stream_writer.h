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

#include <aeon/streams/stream.h>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace aeon::streams
{

class stream;

class stream_writer : common::noncopyable
{
public:
    explicit stream_writer(stream &streamref);

    void write_line(const std::string &line) const;

    auto &internal_stream();

protected:
    stream &stream_;
};

inline stream_writer::stream_writer(stream &streamref)
    : stream_(streamref)
{
}

inline void stream_writer::write_line(const std::string &line) const
{
    stream_.write(reinterpret_cast<const std::uint8_t *>(line.c_str()), line.size());
    stream_.write(reinterpret_cast<const std::uint8_t *>("\n"), 1);
}

inline auto &stream_writer::internal_stream()
{
    return stream_;
}

template <typename T, class = typename std::enable_if<std::is_pod<T>::value>::type>
inline auto &operator<<(stream_writer &writer, const T &val)
{
    if (writer.internal_stream().write(reinterpret_cast<const std::uint8_t *>(&val), sizeof(T)) != sizeof(T))
        throw std::runtime_error("Operator write failed on stream.");

    return writer;
}

} // namespace aeon::streams
