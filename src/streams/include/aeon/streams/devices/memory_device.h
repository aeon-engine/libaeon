// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/devices/memory_view_device.h>
#include <vector>

namespace aeon::streams
{

template <typename T>
class memory_device : public memory_view_device<T>
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

    memory_device(memory_device &&other) noexcept;
    auto operator=(memory_device &&other) noexcept -> memory_device &;

    memory_device(const memory_device &other);
    auto operator=(const memory_device &other) -> memory_device &;

    ~memory_device() = default;

protected:
    std::vector<T> buffer_;
};

memory_device(const std::string &)->memory_device<char>;

template <typename T>
inline memory_device<T>::memory_device() noexcept
    : memory_view_device<T>{}
    , buffer_{}
{
    memory_view_device<T>::buffer_view_ = &buffer_;
}

template <typename T>
inline memory_device<T>::memory_device(const std::streamoff size)
    : memory_view_device<T>{}
    , buffer_(size)
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline memory_device<T>::memory_device(const std::vector<T> &buffer)
    : memory_view_device<T>{}
    , buffer_{buffer}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline memory_device<T>::memory_device(std::vector<T> &&buffer) noexcept
    : memory_view_device<T>{}
    , buffer_{std::move(buffer)}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
template <typename U>
inline memory_device<T>::memory_device(const std::vector<U> &buffer)
    : memory_view_device<T>{}
    , buffer_{std::begin(buffer), std::end(buffer)}
{
    static_assert(sizeof(T) == sizeof(U), "Given template argument size must be the same as the buffer type size.");

    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline memory_device<T>::memory_device(const std::string &str) noexcept
    : memory_view_device<T>{}
    , buffer_{std::begin(str), std::end(str)}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline memory_device<T>::memory_device(memory_device &&other) noexcept
    : memory_view_device<T>{}
    , buffer_{std::move(other.buffer_)}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline auto memory_device<T>::operator=(memory_device &&other) noexcept -> memory_device &
{
    buffer_ = std::move(other.buffer_);

    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();

    return *this;
}

template <typename T>
inline memory_device<T>::memory_device(const memory_device &other)
    : memory_view_device<T>{}
    , buffer_{other.buffer_}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline auto memory_device<T>::operator=(const memory_device &other) -> memory_device &
{
    buffer_ = other.buffer_;

    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();

    return *this;
}

} // namespace aeon::streams
