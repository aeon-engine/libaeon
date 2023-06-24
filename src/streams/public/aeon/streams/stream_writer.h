// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/exception.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/common/signed_sizeof.h>
#include <aeon/common/assert.h>
#include <aeon/common/string_view.h>
#include <vector>
#include <array>

namespace aeon::streams
{

template <typename device_t>
concept stream_writable =
    (is_device_v<device_t> && is_output_v<device_t>) || std::is_same_v<std::decay_t<device_t>, idynamic_stream>;

template <stream_writable device_t>
class stream_writer
{
public:
    explicit stream_writer(device_t &device) noexcept;

    stream_writer(stream_writer &&) noexcept = default;
    auto operator=(stream_writer &&) noexcept -> stream_writer & = default;

    stream_writer(const stream_writer &) noexcept = default;
    auto operator=(const stream_writer &) noexcept -> stream_writer & = default;

    ~stream_writer() = default;

    void device(device_t &device) noexcept;
    [[nodiscard]] auto device() const noexcept -> device_t &;

    template <typename T>
    void vector_write(const std::vector<T> &vec) const;

    template <typename T, std::size_t size>
    void array_write(const std::array<T, size> &arr) const;

private:
    device_t *device_;
};

template <typename device_t>
class dynamic_stream;

template <stream_writable device_t>
stream_writer(dynamic_stream<device_t> &) -> stream_writer<idynamic_stream>;

template <stream_writable device_t>
inline stream_writer<device_t>::stream_writer(device_t &device) noexcept
    : device_{&device}
{
    if constexpr (std::is_same_v<std::decay_t<device_t>, idynamic_stream>)
        aeon_assert(device_->is_output(), "Stream writer requires an output device.");
}

template <stream_writable device_t>
inline void stream_writer<device_t>::device(device_t &device) noexcept
{
    device_ = &device;
}

template <stream_writable device_t>
[[nodiscard]] inline auto stream_writer<device_t>::device() const noexcept -> device_t &
{
    return *device_;
}

template <stream_writable device_t>
template <typename T>
inline void stream_writer<device_t>::vector_write(const std::vector<T> &vec) const
{
    static_assert(sizeof(T) == 1, "Given template argument size must be 1 byte.");

    const auto size = static_cast<std::streamsize>(std::size(vec));

    if (device_->write(reinterpret_cast<const std::byte *>(std::data(vec)), size) != size)
        throw stream_exception{};
}

template <stream_writable device_t>
template <typename T, std::size_t size>
inline void stream_writer<device_t>::array_write(const std::array<T, size> &arr) const
{
    static_assert(sizeof(T) == 1, "Given template argument size must be 1 byte.");

    if (device_->write(reinterpret_cast<const std::byte *>(std::data(arr)), size) != size)
        throw stream_exception{};
}

template <stream_writable device_t, typename T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto &operator<<(stream_writer<device_t> &writer, const T &val)
{
    if (writer.device().write(reinterpret_cast<const std::byte *>(&val), aeon_signed_sizeof(T)) !=
        aeon_signed_sizeof(T))
        throw stream_exception{};

    return writer;
}

template <stream_writable device_t>
inline auto &operator<<(stream_writer<device_t> &writer, const common::string_view &val)
{
    const auto size = static_cast<std::streamsize>(std::size(val));

    if (writer.device().write(reinterpret_cast<const std::byte *>(std::data(val)), size) != size)
        throw stream_exception{};

    return writer;
}

template <stream_writable device_t, typename T>
inline auto &operator<<(stream_writer<device_t> &writer, const std::vector<T> &val)
{
    for (const auto &v : val)
        writer << v;

    return writer;
}

} // namespace aeon::streams
