// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/common/assert.h>
#include <iostream>

namespace aeon::streams::internal
{

[[nodiscard]] inline auto to_ios_seekdir(const seek_direction direction) noexcept -> std::ios::seekdir
{
    switch (direction)
    {
        case seek_direction::begin:
            return std::ios::beg;
        case seek_direction::current:
            return std::ios::cur;
        case seek_direction::end:
            return std::ios::end;
    }

    aeon_assert_fail("Unknown seek direction.");
    return std::ios::cur;
}

template <typename T>
class iostream_device_base : public device
{
public:
    explicit iostream_device_base() noexcept;
    explicit iostream_device_base(T &stream) noexcept;

    iostream_device_base(iostream_device_base &&) noexcept = default;
    auto operator=(iostream_device_base &&) noexcept -> iostream_device_base & = default;

    iostream_device_base(const iostream_device_base &) noexcept = default;
    auto operator=(const iostream_device_base &) noexcept -> iostream_device_base & = default;

    auto write(const char *data, const std::streamsize size) const -> std::streamsize;

    auto read(char *data, const std::streamsize size) const -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) const -> bool;

    [[nodiscard]] auto tellg() const -> std::streamoff;

    auto seekp(const std::streamoff offset, const seek_direction direction) const -> bool;

    [[nodiscard]] auto tellp() const -> std::streamoff;

    [[nodiscard]] auto eof() const -> bool;

    [[nodiscard]] auto good() const -> bool;

    [[nodiscard]] auto fail() const -> bool;

    void flush() const;

protected:
    ~iostream_device_base() = default;
    T *stream_;
};

template <typename T>
inline iostream_device_base<T>::iostream_device_base() noexcept
    : stream_{nullptr}
{
}

template <typename T>
inline iostream_device_base<T>::iostream_device_base(T &stream) noexcept
    : stream_{&stream}
{
}

template <typename T>
inline auto iostream_device_base<T>::write(const char *data, const std::streamsize size) const -> std::streamsize
{
    stream_->write(data, size);

    if (stream_->fail())
        return 0;

    return size;
}

template <typename T>
inline auto iostream_device_base<T>::read(char *data, const std::streamsize size) const -> std::streamsize
{
    if (stream_->read(data, size))
        return size;

    return static_cast<std::size_t>(stream_->gcount());
}

template <typename T>
inline auto iostream_device_base<T>::seekg(const std::streamoff offset, const seek_direction direction) const -> bool
{
    // Make sure all failure bits are cleared before seeking.
    // This can happen if read didn't manage to read all requested characters.
    stream_->clear();

    stream_->seekg(offset, to_ios_seekdir(direction));
    return !stream_->fail();
}

template <typename T>
[[nodiscard]] inline auto iostream_device_base<T>::tellg() const -> std::streamoff
{
    return stream_->tellg();
}

template <typename T>
inline auto iostream_device_base<T>::seekp(const std::streamoff offset, const seek_direction direction) const -> bool
{
    stream_->seekp(offset, to_ios_seekdir(direction));
    return !stream_->fail();
}

template <typename T>
[[nodiscard]] inline auto iostream_device_base<T>::tellp() const -> std::streamoff
{
    return stream_->tellp();
}

template <typename T>
[[nodiscard]] inline auto iostream_device_base<T>::eof() const -> bool
{
    return stream_->eof();
}

template <typename T>
[[nodiscard]] inline auto iostream_device_base<T>::good() const -> bool
{
    return stream_->good();
}

template <typename T>
[[nodiscard]] inline auto iostream_device_base<T>::fail() const -> bool
{
    return stream_->fail();
}

template <typename T>
inline void iostream_device_base<T>::flush() const
{
    stream_->flush();
}

} // namespace aeon::streams::internal
