// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/devices/span_device.h>
#include <vector>

namespace aeon::streams
{

template <typename T>
class memory_view_device : public device
{
public:
    struct category : input, input_seekable, output, output_seekable, has_eof, has_size
    {
    };

    explicit memory_view_device(std::vector<T> &buffer) noexcept;
    explicit memory_view_device(const std::vector<T> &buffer) noexcept;

    memory_view_device(memory_view_device &&) noexcept = default;
    auto operator=(memory_view_device &&) noexcept -> memory_view_device & = default;

    memory_view_device(const memory_view_device &) = delete;
    auto operator=(const memory_view_device &) -> memory_view_device & = delete;

    ~memory_view_device() = default;

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
    memory_view_device() noexcept;
    void update_span();

    std::vector<T> *buffer_view_;
    span_device<T> span_device_;
};

memory_view_device(const std::string &)->memory_view_device<char>;

template <typename T>
inline memory_view_device<T>::memory_view_device(std::vector<T> &buffer) noexcept
    : buffer_view_{&buffer}
    , span_device_{common::span<T>{}}
{
    if (!std::empty(*buffer_view_))
        update_span();
}

template <typename T>
inline memory_view_device<T>::memory_view_device(const std::vector<T> &buffer) noexcept
    : buffer_view_{const_cast<std::vector<T>*>(&buffer)}
    , span_device_{common::span<T>{}}
{
    if (!std::empty(*buffer_view_))
        update_span();
}
template <typename T>
inline memory_view_device<T>::memory_view_device() noexcept
    : buffer_view_{}
    , span_device_{common::span<T>{}}
{
}

template <typename T>
inline auto memory_view_device<T>::write(const char *data, const std::streamsize size) noexcept -> std::streamsize
{
    resize(tellp() + size);
    return span_device_.write(data, size);
}

template <typename T>
inline auto memory_view_device<T>::read(char *data, const std::streamsize size) noexcept -> std::streamsize
{
    return span_device_.read(data, size);
}

template <typename T>
inline auto memory_view_device<T>::seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    return span_device_.seekg(offset, direction);
}

template <typename T>
inline auto memory_view_device<T>::tellg() const noexcept -> std::streamoff
{
    return span_device_.tellg();
}

template <typename T>
inline auto memory_view_device<T>::seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    return span_device_.seekp(offset, direction);
}

template <typename T>
inline auto memory_view_device<T>::tellp() const noexcept -> std::streamoff
{
    return span_device_.tellp();
}

template <typename T>
inline auto memory_view_device<T>::eof() const noexcept -> bool
{
    return span_device_.eof();
}

template <typename T>
inline auto memory_view_device<T>::size() const noexcept -> std::streamoff
{
    return span_device_.size();
}

template <typename T>
inline auto memory_view_device<T>::buffer() const noexcept -> const std::vector<T> &
{
    return *buffer_view_;
}

template <typename T>
inline void memory_view_device<T>::reserve(const std::streamoff size)
{
    buffer_view_->reserve(size);
}

template <typename T>
inline void memory_view_device<T>::resize(const std::streamoff size)
{
    if (size > static_cast<std::streamoff>(std::size(*buffer_view_)))
        buffer_view_->resize(size);

    update_span();
}

template <typename T>
auto memory_view_device<T>::data() const noexcept -> const std::vector<T> &
{
    return *buffer_view_;
}

template <typename T>
void memory_view_device<T>::update_span()
{
    span_device_.set_span(common::span{*buffer_view_});
}

} // namespace aeon::streams
