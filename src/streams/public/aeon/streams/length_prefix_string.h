// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/varint.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/exception.h>
#include <aeon/common/assert.h>
#include <aeon/common/string.h>
#include <aeon/common/string_concepts.h>
#include <type_traits>
#include <cstdint>

namespace aeon::streams
{

template <typename T>
concept length_prefix = std::is_integral_v<T> || std::is_same_v<T, varint>;

template <length_prefix LengthT = std::uint32_t>
struct length_prefix_string
{
    using length_type = LengthT;

    explicit length_prefix_string(common::string &str)
        : string(str)
    {
    }

    explicit length_prefix_string(const common::string &str)
        : string(const_cast<common::string &>(str))
    {
    }

    common::string &string;
};

template <typename device_t, length_prefix LengthT>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<LengthT> &value)
{
    const auto string_length_bytes = value.string.size() * sizeof(common::string::value_type);
    aeon_assert(string_length_bytes < std::numeric_limits<LengthT>::max(),
                "String size in bytes exceeds length type max (overflow).");

    writer << static_cast<LengthT>(string_length_bytes);

    if (writer.device().write(reinterpret_cast<const std::byte *>(value.string.c_str()), string_length_bytes) !=
        static_cast<std::streamsize>(string_length_bytes))
        throw stream_exception{};

    return writer;
}

template <typename device_t>
inline auto &operator<<(stream_writer<device_t> &writer, const length_prefix_string<varint> &value)
{
    const auto string_length_bytes = value.string.size() * sizeof(common::string::value_type);

    writer << varint{string_length_bytes};

    if (writer.device().write(reinterpret_cast<const std::byte *>(value.string.c_str()), string_length_bytes) !=
        static_cast<std::streamsize>(string_length_bytes))
        throw stream_exception{};

    return writer;
}

template <typename device_t, length_prefix LengthT>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<LengthT> &&value)
{
    LengthT length_bytes = 0;
    reader >> length_bytes;
    value.string.resize(length_bytes / sizeof(common::string::value_type));

    if (reader.device().read(reinterpret_cast<std::byte *>(std::data(value.string)), length_bytes) !=
        static_cast<std::streamoff>(length_bytes))
        throw stream_exception{};

    return reader;
}

template <typename device_t>
inline auto &operator>>(stream_reader<device_t> &reader, length_prefix_string<varint> &&value)
{
    std::uint64_t length_bytes = 0;
    reader >> varint{length_bytes};
    value.string.resize(length_bytes / sizeof(common::string::value_type));

    if (reader.device().read(reinterpret_cast<std::byte *>(std::data(value.string)), length_bytes) !=
        static_cast<std::streamoff>(length_bytes))
        throw stream_exception{};

    return reader;
}

} // namespace aeon::streams
