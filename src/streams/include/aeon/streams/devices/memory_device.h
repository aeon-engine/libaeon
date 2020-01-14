// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/common/compilers.h>

namespace aeon::streams
{

template <typename T = std::vector<char>>
class memory_device : public memory_view_device<T>
{
public:
    struct category : input, input_seekable, output, output_seekable, has_eof, has_size
    {
    };

    explicit memory_device() noexcept;

    explicit memory_device(const std::streamoff size);

    explicit memory_device(const T &buffer);

    explicit memory_device(T &&buffer) noexcept;

    memory_device(memory_device &&other) noexcept;
    auto operator=(memory_device &&other) noexcept -> memory_device &;

    memory_device(const memory_device &other);
    auto operator=(const memory_device &other) -> memory_device &;

    ~memory_device() = default;

protected:
    T buffer_;
};

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
inline memory_device<T>::memory_device(const T &buffer)
    : memory_view_device<T>{}
    , buffer_{buffer}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <typename T>
inline memory_device<T>::memory_device(T &&buffer) noexcept
    : memory_view_device<T>{}
    , buffer_{std::move(buffer)}
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
    if (AEON_LIKELY(this != &other))
    {
        buffer_ = std::move(other.buffer_);

        memory_view_device<T>::buffer_view_ = &buffer_;

        if (!std::empty(buffer_))
            memory_view_device<T>::update_span();
    }

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
    if (AEON_LIKELY(this != &other))
    {
        buffer_ = other.buffer_;

        memory_view_device<T>::buffer_view_ = &buffer_;

        if (!std::empty(buffer_))
            memory_view_device<T>::update_span();
    }

    return *this;
}

} // namespace aeon::streams
