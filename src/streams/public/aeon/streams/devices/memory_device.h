// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/devices/memory_view_device.h>

namespace aeon::streams
{

template <memory_viewable T = std::vector<char>>
class memory_device : public memory_view_device<T>
{
public:
    using value_type = typename T::value_type;

    struct category : input_tag, input_seekable_tag, output_tag, output_seekable_tag, has_eof_tag, has_size_tag
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

    void reserve(const std::size_t size);

    [[nodiscard]] auto release() noexcept -> T
    {
        return std::move(buffer_);
    }

protected:
    T buffer_;
};

template <memory_viewable T>
inline memory_device<T>::memory_device() noexcept
    : memory_view_device<T>{}
    , buffer_{}
{
    memory_view_device<T>::buffer_view_ = &buffer_;
}

template <memory_viewable T>
inline memory_device<T>::memory_device(const std::streamoff size)
    : memory_view_device<T>{}
    , buffer_(size)
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <memory_viewable T>
inline memory_device<T>::memory_device(const T &buffer)
    : memory_view_device<T>{}
    , buffer_{buffer}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <memory_viewable T>
inline memory_device<T>::memory_device(T &&buffer) noexcept
    : memory_view_device<T>{}
    , buffer_{std::move(buffer)}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <memory_viewable T>
inline memory_device<T>::memory_device(memory_device &&other) noexcept
    : memory_view_device<T>{}
    , buffer_{std::move(other.buffer_)}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <memory_viewable T>
inline auto memory_device<T>::operator=(memory_device &&other) noexcept -> memory_device &
{
    if (this != &other) [[likely]]
    {
        buffer_ = std::move(other.buffer_);

        memory_view_device<T>::buffer_view_ = &buffer_;

        if (!std::empty(buffer_))
            memory_view_device<T>::update_span();
    }

    return *this;
}

template <memory_viewable T>
inline memory_device<T>::memory_device(const memory_device &other)
    : memory_view_device<T>{}
    , buffer_{other.buffer_}
{
    memory_view_device<T>::buffer_view_ = &buffer_;

    if (!std::empty(buffer_))
        memory_view_device<T>::update_span();
}

template <memory_viewable T>
inline auto memory_device<T>::operator=(const memory_device &other) -> memory_device &
{
    if (this != &other) [[likely]]
    {
        buffer_ = other.buffer_;

        memory_view_device<T>::buffer_view_ = &buffer_;

        if (!std::empty(buffer_))
            memory_view_device<T>::update_span();
    }

    return *this;
}

template <memory_viewable T>
inline void memory_device<T>::reserve(const std::size_t size)
{
    buffer_.reserve(static_cast<std::size_t>(size));
    memory_view_device<T>::update_span();
}

} // namespace aeon::streams
