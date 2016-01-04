/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace streams
{

class stream;
class stream_writer
{
public:
    stream_writer(stream &streamref)
        : stream_(streamref)
    {
    }

    ~stream_writer()
    {
    }

    stream_writer &operator=(const stream_writer &) = delete;

#define STREAM_WRITER_WRITE_OPERATOR(Type)                                                                             \
    stream_writer &operator<<(Type &value)                                                                             \
    {                                                                                                                  \
        if (stream_.write((std::uint8_t *)&value, sizeof(Type)) != sizeof(Type))                                       \
        {                                                                                                              \
            throw std::runtime_error("Operator write failed on stream.");                                              \
        }                                                                                                              \
        return *this;                                                                                                  \
    }

    STREAM_WRITER_WRITE_OPERATOR(std::int8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int64_t)

    STREAM_WRITER_WRITE_OPERATOR(std::uint8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint64_t)

    STREAM_WRITER_WRITE_OPERATOR(float)
    STREAM_WRITER_WRITE_OPERATOR(double)

    stream_writer &operator<<(const std::string &value)
    {
        std::size_t string_length = value.size();
        if (stream_.write((std::uint8_t *)value.c_str(), string_length) != string_length)
        {
            throw std::runtime_error("Operator write failed on stream.");
        }
        return *this;
    }

    void write_line(const std::string &line)
    {
        stream_.write((std::uint8_t *)line.c_str(), line.size());
        stream_.write((std::uint8_t *)"\n", 1);
    }

protected:
    stream &stream_;
};

} // namespace streams
} // namespace aeon
