// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/stream.h>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace aeon::streams
{

class stream;

class stream_writer
{
public:
    explicit stream_writer(stream &streamref);
    ~stream_writer() = default;

    stream_writer(stream_writer &&) = delete;
    auto operator=(stream_writer &&) -> stream_writer & = delete;

    stream_writer(const stream_writer &) = delete;
    auto operator=(const stream_writer &) -> stream_writer & = delete;

    void write_line(const std::string &line) const;

    auto &internal_stream() const noexcept;

protected:
    stream &stream_;
};

inline stream_writer::stream_writer(stream &streamref)
    : stream_{streamref}
{
}

inline void stream_writer::write_line(const std::string &line) const
{
    stream_.write(reinterpret_cast<const std::uint8_t *>(line.c_str()), line.size());
    stream_.write(reinterpret_cast<const std::uint8_t *>("\n"), 1);
}

inline auto &stream_writer::internal_stream() const noexcept
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
