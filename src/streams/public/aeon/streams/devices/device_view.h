// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/devices/span_device.h>
#include <aeon/streams/stream_traits.h>

namespace aeon::streams
{

template <typename T>
class device_view : public device
{
public:
    struct category : T::category
    {
    };

    explicit device_view(T &device) noexcept;
    explicit device_view(const T &device) noexcept;

    device_view(device_view &&) noexcept = default;
    auto operator=(device_view &&) noexcept -> device_view & = default;

    device_view(const device_view &) noexcept = default;
    auto operator=(const device_view &) noexcept -> device_view & = default;

    ~device_view() = default;

    auto read(std::byte *data, const std::streamsize size) -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) -> bool;

    [[nodiscard]] auto tellg() -> std::streamoff;

    auto write(const std::byte *data, const std::streamsize size) -> std::streamsize;

    auto seekp(const std::streamoff offset, const seek_direction direction) -> bool;

    [[nodiscard]] auto tellp() -> std::streamoff;

    [[nodiscard]] auto eof() -> bool;

    [[nodiscard]] auto good() -> bool;

    [[nodiscard]] auto fail() -> bool;

    void flush();

    [[nodiscard]] auto size() -> std::streamoff;

protected:
    T *device_;
};

template <typename T>
inline device_view<T>::device_view(T &device) noexcept
    : device_{&device}
{
}

template <typename T>
inline device_view<T>::device_view(const T &device) noexcept
    : device_{const_cast<T *>(&device)}
{
}

template <typename T>
inline auto device_view<T>::write(const std::byte *data, const std::streamsize size) -> std::streamsize
{
    static_assert(is_output_v<T>, "Device does not support 'write'");
    return device_->write(data, size);
}

template <typename T>
inline auto device_view<T>::read(std::byte *data, const std::streamsize size) -> std::streamsize
{
    static_assert(is_input_v<T>, "Device does not support 'read'");
    return device_->read(data, size);
}

template <typename T>
inline auto device_view<T>::seekg(const std::streamoff offset, const seek_direction direction) -> bool
{
    static_assert(is_input_seekable_v<T>, "Device does not support 'seekg'");
    return device_->seekg(offset, direction);
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::tellg() -> std::streamoff
{
    static_assert(is_input_seekable_v<T>, "Device does not support 'tellg'");
    return device_->tellg();
}

template <typename T>
inline auto device_view<T>::seekp(const std::streamoff offset, const seek_direction direction) -> bool
{
    static_assert(is_output_seekable_v<T>, "Device does not support 'seekp'");
    return device_->seekp(offset, direction);
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::tellp() -> std::streamoff
{
    static_assert(is_output_seekable_v<T>, "Device does not support 'tellp'");
    return device_->tellp();
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::eof() -> bool
{
    static_assert(has_eof_v<T>, "Device does not support 'eof'");
    return device_->eof();
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::good() -> bool
{
    static_assert(has_status_v<T>, "Device does not support 'good'");
    return device_->good();
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::fail() -> bool
{
    static_assert(has_status_v<T>, "Device does not support 'fail'");
    return device_->fail();
}

template <typename T>
inline void device_view<T>::flush()
{
    static_assert(is_flushable_v<T>, "Device does not support 'flush'");
    device_->flush();
}

template <typename T>
[[nodiscard]] inline auto device_view<T>::size() -> std::streamoff
{
    static_assert(has_size_v<T>, "Device does not support 'size'");
    return device_->size();
}

} // namespace aeon::streams
