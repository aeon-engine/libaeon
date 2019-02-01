// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/devices/span_device.h>
#include <vector>

namespace aeon::streams
{

template <typename T>
class memory_device : public device
{
public:
    struct category : input, input_seekable, output, output_seekable, has_eof, has_size
    {
    };

    explicit memory_device() noexcept;

    explicit memory_device(const std::streamoff size);

    explicit memory_device(const std::vector<T> &buffer);

    explicit memory_device(std::vector<T> &&buffer) noexcept;

    template <typename U>
    explicit memory_device(const std::vector<U> &buffer);

    explicit memory_device(const std::string &str) noexcept;

    memory_device(memory_device &&) noexcept = default;
    auto operator=(memory_device &&) noexcept -> memory_device & = default;

    memory_device(const memory_device &) = default;
    auto operator=(const memory_device &) -> memory_device & = default;

    ~memory_device() = default;

    auto write(const char *data, const std::streamsize size) noexcept -> std::streamsize;

    auto read(char *data, const std::streamsize size) noexcept -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    auto tellg() const noexcept -> std::streamoff;

    auto seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    auto tellp() const noexcept -> std::streamoff;

    auto eof() const noexcept -> bool;

    auto size() const noexcept -> std::streamoff;

    auto buffer() const noexcept -> const std::vector<T> &;

    void reserve(const std::streamoff size);

    void resize(const std::streamoff size);

    auto data() const noexcept -> const std::vector<T> &;

protected:
    void update_span();

    std::vector<T> buffer_;
    span_device<T> span_device_;
};

memory_device(const std::string &)->memory_device<char>;

template <typename T>
inline memory_device<T>::memory_device() noexcept
    : buffer_{}
    , span_device_{common::span<T>{}}
{
}

template <typename T>
inline memory_device<T>::memory_device(const std::streamoff size)
    : buffer_(size)
    , span_device_{common::span<T>{}}
{
    if (!std::empty(buffer_))
        update_span();
}

template <typename T>
inline memory_device<T>::memory_device(const std::vector<T> &buffer)
    : buffer_{buffer}
    , span_device_{common::span<T>{}}
{
    if (!std::empty(buffer_))
        update_span();
}

template <typename T>
inline memory_device<T>::memory_device(std::vector<T> &&buffer) noexcept
    : buffer_{std::move(buffer)}
    , span_device_{common::span<T>{}}
{
    if (!std::empty(buffer_))
        update_span();
}

template <typename T>
template <typename U>
inline memory_device<T>::memory_device(const std::vector<U> &buffer)
    : buffer_{std::begin(buffer), std::end(buffer)}
    , span_device_{common::span<T>{}}
{
    static_assert(sizeof(T) == sizeof(U), "Given template argument size must be the same as the buffer type size.");

    if (!std::empty(buffer_))
        update_span();
}

template <typename T>
inline memory_device<T>::memory_device(const std::string &str) noexcept
    : buffer_{std::begin(str), std::end(str)}
    , span_device_{common::span<T>{}}
{
    if (!std::empty(buffer_))
        update_span();
}

template <typename T>
inline auto memory_device<T>::write(const char *data, const std::streamsize size) noexcept -> std::streamsize
{
    resize(tellp() + size);
    return span_device_.write(data, size);
}

template <typename T>
inline auto memory_device<T>::read(char *data, const std::streamsize size) noexcept -> std::streamsize
{
    return span_device_.read(data, size);
}

template <typename T>
inline auto memory_device<T>::seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    return span_device_.seekg(offset, direction);
}

template <typename T>
inline auto memory_device<T>::tellg() const noexcept -> std::streamoff
{
    return span_device_.tellg();
}

template <typename T>
inline auto memory_device<T>::seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    return span_device_.seekp(offset, direction);
}

template <typename T>
inline auto memory_device<T>::tellp() const noexcept -> std::streamoff
{
    return span_device_.tellp();
}

template <typename T>
inline auto memory_device<T>::eof() const noexcept -> bool
{
    return span_device_.eof();
}

template <typename T>
inline auto memory_device<T>::size() const noexcept -> std::streamoff
{
    return span_device_.size();
}

template <typename T>
inline auto memory_device<T>::buffer() const noexcept -> const std::vector<T> &
{
    return buffer_;
}

template <typename T>
inline void memory_device<T>::reserve(const std::streamoff size)
{
    buffer_.reserve(size);
}

template <typename T>
inline void memory_device<T>::resize(const std::streamoff size)
{
    if (size > static_cast<std::streamoff>(std::size(buffer_)))
        buffer_.resize(size);

    update_span();
}

template <typename T>
auto memory_device<T>::data() const noexcept -> const std::vector<T> &
{
    return buffer_;
}

template <typename T>
void memory_device<T>::update_span()
{
    span_device_.set_span(common::span{buffer_});
}

} // namespace aeon::streams
