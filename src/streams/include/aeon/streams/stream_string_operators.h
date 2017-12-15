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

#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <limits>
#include <cassert>

namespace aeon
{
namespace streams
{

template <typename T>
inline auto &operator>>(stream_reader<T> &reader, std::string &val)
{
    val = reader.read_as_string();
    return reader;
}

inline auto &operator<<(stream_writer &writer, const std::string &value)
{
    const auto string_length = value.size();

    if (writer.internal_stream().write(reinterpret_cast<const std::uint8_t *>(value.c_str()), string_length) !=
        string_length)
        throw std::runtime_error("Operator write failed on stream.");

    return writer;
}

template <typename T>
struct length_prefix_string
{
    explicit length_prefix_string(std::string &str)
        : string(str)
    {
    }

    explicit length_prefix_string(const std::string &str)
        : string(const_cast<std::string &>(str))
    {
    }

    std::string &string;
};

template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
inline auto &operator<<(streams::stream_writer &writer, const length_prefix_string<T> &value)
{
    const auto string_length = value.string.size();
    assert(string_length < std::numeric_limits<T>::max());

    writer << static_cast<T>(string_length);

    if (writer.internal_stream().write(reinterpret_cast<const std::uint8_t *>(value.string.c_str()), string_length) !=
        string_length)
        throw std::runtime_error("Operator write failed on stream.");

    return writer;
}

template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
inline auto &operator>>(streams::stream_reader<streams::stream> &reader, length_prefix_string<T> &value)
{
    T length = 0;
    reader >> length;
    value.string.resize(length);

    if (reader.internal_stream().read(reinterpret_cast<std::uint8_t *>(value.string.data()), length) != length)
        throw std::runtime_error("Operator read failed on stream.");

    return reader;
}

} // namespace streams
} // namespace aeon
