// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <limits>
#include <cassert>
#include <string_view>
#include <string>

namespace aeon::streams
{

template <typename T>
inline auto &operator>>(stream_reader<T> &reader, std::string &val)
{
    val = reader.read_as_string();
    return reader;
}

inline auto &operator<<(stream_writer &writer, const std::string_view &value)
{
    const auto string_length = value.size();

    if (writer.internal_stream().write(reinterpret_cast<const std::uint8_t *>(value.data()), string_length) !=
        string_length)
        throw std::runtime_error("Operator write failed on stream.");

    return writer;
}

inline auto &operator<<(stream_writer &writer, const std::string &value)
{
    writer << std::string_view{value};
    return writer;
}

inline auto &operator<<(stream_writer &writer, const char *value)
{
    writer << std::string_view{value};
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

} // namespace aeon::streams
