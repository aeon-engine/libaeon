// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/varint.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/exception.h>
#include <aeon/common/assert.h>
#include <aeon/common/string_concepts.h>
#include <type_traits>
#include <cstdint>

namespace aeon::streams
{

template <typename T>
concept length_prefix = std::is_integral_v<T> || std::is_same_v<T, varint>;

template <common::concepts::basic_string T, length_prefix LengthT = std::uint32_t>
struct length_prefix_string
{
    using string_type = T;
    using length_type = LengthT;

    explicit length_prefix_string(T &str)
        : string(str)
    {
    }

    explicit length_prefix_string(const T &str)
        : string(const_cast<T &>(str))
    {
    }

    T &string;
};

template <typename device_t, common::concepts::basic_string T, length_prefix LengthT>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<T, LengthT> &value)
{
    const auto string_length_bytes = value.string.size() * sizeof(typename T::value_type);
    aeon_assert(string_length_bytes < std::numeric_limits<LengthT>::max(),
                "String size in bytes exceeds length type max (overflow).");

    writer << static_cast<LengthT>(string_length_bytes);

    if (writer.device().write(reinterpret_cast<const std::byte *>(value.string.c_str()), string_length_bytes) !=
        static_cast<std::streamsize>(string_length_bytes))
        throw stream_exception{};

    return writer;
}

template <typename device_t, common::concepts::basic_string T>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<T, varint> &value)
{
    const auto string_length_bytes = value.string.size() * sizeof(typename T::value_type);

    writer << varint{string_length_bytes};

    if (writer.device().write(reinterpret_cast<const std::byte *>(value.string.c_str()), string_length_bytes) !=
        static_cast<std::streamsize>(string_length_bytes))
        throw stream_exception{};

    return writer;
}

template <typename device_t, common::concepts::basic_string T, length_prefix LengthT>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<T, LengthT> &&value)
{
    LengthT length_bytes = 0;
    reader >> length_bytes;
    value.string.resize(length_bytes / sizeof(typename T::value_type));

    if (reader.device().read(reinterpret_cast<std::byte *>(std::data(value.string)), length_bytes) !=
        static_cast<std::streamoff>(length_bytes))
        throw stream_exception{};

    return reader;
}

template <typename device_t, common::concepts::basic_string T>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<T, varint> &&value)
{
    std::uint64_t length_bytes = 0;
    reader >> varint{length_bytes};
    value.string.resize(length_bytes / sizeof(typename T::value_type));

    if (reader.device().read(reinterpret_cast<std::byte *>(std::data(value.string)), length_bytes) !=
        static_cast<std::streamoff>(length_bytes))
        throw stream_exception{};

    return reader;
}

} // namespace aeon::streams
