// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/streams/exception.h>
#include <aeon/common/assert.h>
#include <aeon/common/signed_sizeof.h>
#include <string>
#include <vector>

namespace aeon::streams
{

class dynamic_stream_writer
{
public:
    explicit dynamic_stream_writer(idynamic_stream &device) noexcept;

    dynamic_stream_writer(dynamic_stream_writer &&) noexcept = default;
    auto operator=(dynamic_stream_writer &&) noexcept -> dynamic_stream_writer & = default;

    dynamic_stream_writer(const dynamic_stream_writer &) noexcept = default;
    auto operator=(const dynamic_stream_writer &) noexcept -> dynamic_stream_writer & = default;

    ~dynamic_stream_writer() = default;

    auto device() const noexcept -> idynamic_stream &;

    template <typename T>
    void vector_write(const std::vector<T> &vec) const;

private:
    idynamic_stream *device_;
};

template <typename T>
inline void dynamic_stream_writer::vector_write(const std::vector<T> &vec) const
{
    static_assert(sizeof(T) == 1, "Given template argument size must be 1 byte.");

    const auto size = static_cast<std::streamsize>(std::size(vec));

    if (device_->write(reinterpret_cast<const char *>(std::data(vec)), size) != size)
        throw stream_exception{};
}

inline dynamic_stream_writer::dynamic_stream_writer(idynamic_stream &device) noexcept
    : device_{&device}
{
    aeon_assert(device_->is_output(), "Stream writer requires an output device.");
}

inline auto dynamic_stream_writer::device() const noexcept -> idynamic_stream &
{
    return *device_;
}

template <typename T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto &operator<<(dynamic_stream_writer &writer, const T &val)
{
    if (writer.device().write(reinterpret_cast<const char *>(&val), aeon_signed_sizeof(T)) != aeon_signed_sizeof(T))
        throw stream_exception{};

    return writer;
}

inline auto &operator<<(dynamic_stream_writer &writer, const std::string &val)
{
    const auto size = static_cast<std::streamsize>(std::size(val));
    if (writer.device().write(std::data(val), size) != size)
        throw stream_exception{};

    return writer;
}

template <typename T>
inline auto &operator<<(dynamic_stream_writer &writer, const length_prefix_string<T> &value)
{
    const auto string_length = value.string.size();
    aeon_assert(string_length < std::numeric_limits<T>::max(), "String length exceeds length type max (overflow).");

    writer << static_cast<T>(string_length);

    if (writer.device().write(value.string.c_str(), string_length) != static_cast<std::streamsize>(string_length))
        throw stream_exception{};

    return writer;
}

template <typename T>
inline auto &operator<<(dynamic_stream_writer &writer, const std::vector<T> &val)
{
    for (const auto &v : val)
        writer << v;

    return writer;
}

} // namespace aeon::streams
