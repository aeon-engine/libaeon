// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <cstdint>

namespace aeon::streams
{

/*!
 * Encode/Decode a 64-bit integer with LEB128 variable length integer compression.
 * With this encoding, a high MSB indicates there are more bytes to read,
 * leaving 7 bits per byte to actually store the integer value.
 */
struct varint
{
    explicit varint(std::uint64_t &val)
        : value(val)
    {
    }

    explicit varint(const std::uint64_t &str)
        : value(const_cast<std::uint64_t &>(str))
    {
    }

    std::uint64_t &value;
};

template <typename device_t>
inline auto &operator<<(stream_writer<device_t> &writer, const varint &value)
{
    auto v = value.value;

    while (v >= 0x80)
    {
        writer << static_cast<std::uint8_t>(v | 0x80);
        v >>= 7;
    }

    writer << static_cast<std::uint8_t>(v);

    return writer;
}

template <typename device_t>
inline auto &operator>>(stream_reader<device_t> &reader, varint &&value)
{
    std::uint8_t byte = 0;
    reader >> byte;

    if (byte < 0x80)
    {
        value.value = byte;
        return reader;
    }

    value.value = byte & 0x7f;
    auto shift = 7u;

    do
    {
        reader >> byte;
        value.value |= (static_cast<std::uint64_t>(byte & 0x7f) << shift);
        shift += 7;
    } while (byte >= 0x80);

    return reader;
}

} // namespace aeon::streams
