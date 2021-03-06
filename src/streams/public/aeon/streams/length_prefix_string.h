// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/varint.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/exception.h>
#include <aeon/common/assert.h>
#include <type_traits>
#include <string>
#include <cstdint>

namespace aeon::streams
{

template <typename T>
concept length_prefix = std::is_integral_v<T> || std::is_same_v<T, varint>;

template <length_prefix T = std::uint32_t>
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

template <typename device_t, typename T>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<T> &value)
{
    const auto string_length = value.string.size();
    aeon_assert(string_length < std::numeric_limits<T>::max(), "String length exceeds length type max (overflow).");

    writer << static_cast<T>(string_length);

    if (writer.device().write(value.string.c_str(), string_length) != static_cast<std::streamsize>(string_length))
        throw stream_exception{};

    return writer;
}

template <typename device_t>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<varint> &value)
{
    const auto string_length = value.string.size();

    writer << varint{string_length};

    if (writer.device().write(value.string.c_str(), string_length) != static_cast<std::streamsize>(string_length))
        throw stream_exception{};

    return writer;
}

template <typename device_t, typename T>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<T> &&value)
{
    T length = 0;
    reader >> length;
    value.string.resize(length);

    if (reader.device().read(std::data(value.string), length) != static_cast<std::streamoff>(length))
        throw stream_exception{};

    return reader;
}

template <typename device_t>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<varint> &&value)
{
    std::uint64_t length = 0;
    reader >> varint{length};
    value.string.resize(length);

    if (reader.device().read(std::data(value.string), length) != static_cast<std::streamoff>(length))
        throw stream_exception{};

    return reader;
}

} // namespace aeon::streams
