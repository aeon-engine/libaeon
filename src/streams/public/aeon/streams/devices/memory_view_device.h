// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/devices/span_device.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/string.h>
#include <string>

namespace aeon::streams
{

template <typename T>
concept memory_viewable = common::type_traits::is_std_vector_v<T> || std::is_same_v<T, common::string> ||
                          std::is_same_v<T, std::string> || std::is_same_v<T, std::u8string>;

template <memory_viewable T>
class memory_view_device : public device
{
public:
    using value_type = typename T::value_type;

    struct category : input_tag, input_seekable_tag, output_tag, output_seekable_tag, has_eof_tag, has_size_tag
    {
    };

    explicit memory_view_device(T &buffer) noexcept;
    explicit memory_view_device(const T &buffer) noexcept;

    memory_view_device(memory_view_device &&) noexcept = default;
    auto operator=(memory_view_device &&) noexcept -> memory_view_device & = default;

    memory_view_device(const memory_view_device &) = delete;
    auto operator=(const memory_view_device &) -> memory_view_device & = delete;

    ~memory_view_device() = default;

    auto write(const std::byte *data, const std::streamsize size) noexcept -> std::streamsize;

    auto read(std::byte *data, const std::streamsize size) noexcept -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    [[nodiscard]] auto tellg() const noexcept -> std::streamoff;

    auto seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool;

    [[nodiscard]] auto tellp() const noexcept -> std::streamoff;

    [[nodiscard]] auto eof() const noexcept -> bool;

    [[nodiscard]] auto size() const noexcept -> std::streamoff;

    void reserve(const std::streamoff size);

    void resize(const std::streamoff size);

    [[nodiscard]] const auto &data() const noexcept;

protected:
    memory_view_device() noexcept;
    void update_span();

    T *buffer_view_;
    span_device<typename T::value_type> span_device_;
};

template <memory_viewable T>
inline memory_view_device<T>::memory_view_device(T &buffer) noexcept
    : buffer_view_{&buffer}
    , span_device_{std::span<typename T::value_type>{}}
{
    if (!std::empty(*buffer_view_))
        update_span();
}

template <memory_viewable T>
inline memory_view_device<T>::memory_view_device(const T &buffer) noexcept
    : buffer_view_{const_cast<T *>(&buffer)}
    , span_device_{std::span<typename T::value_type>{}}
{
    if (!std::empty(*buffer_view_))
        update_span();
}

template <memory_viewable T>
inline memory_view_device<T>::memory_view_device() noexcept
    : buffer_view_{}
    , span_device_{std::span<typename T::value_type>{}}
{
}

template <memory_viewable T>
inline auto memory_view_device<T>::write(const std::byte *data, const std::streamsize size) noexcept -> std::streamsize
{
    const auto current_size = tellp();
    if (current_size + size > span_device_.size())
        resize(current_size + size);

    return span_device_.write(data, size);
}

template <memory_viewable T>
inline auto memory_view_device<T>::read(std::byte *data, const std::streamsize size) noexcept -> std::streamsize
{
    return span_device_.read(data, size);
}

template <memory_viewable T>
inline auto memory_view_device<T>::seekg(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    return span_device_.seekg(offset, direction);
}

template <memory_viewable T>
[[nodiscard]] inline auto memory_view_device<T>::tellg() const noexcept -> std::streamoff
{
    return span_device_.tellg();
}

template <memory_viewable T>
inline auto memory_view_device<T>::seekp(const std::streamoff offset, const seek_direction direction) noexcept -> bool
{
    std::streamoff idx = 0;
    switch (direction)
    {
        case seek_direction::begin:
        {
            idx = offset;
        }
        break;
        case seek_direction::current:
        {
            idx = tellp() + offset;
        }
        break;
        case seek_direction::end:
        {
            idx = (std::size(span_device_) - 1) - offset;
        }
        break;
    }

    if (idx >= span_device_.size())
        resize(idx + 1);

    return span_device_.seekp(offset, direction);
}

template <memory_viewable T>
[[nodiscard]] inline auto memory_view_device<T>::tellp() const noexcept -> std::streamoff
{
    return span_device_.tellp();
}

template <memory_viewable T>
[[nodiscard]] inline auto memory_view_device<T>::eof() const noexcept -> bool
{
    return span_device_.eof();
}

template <memory_viewable T>
[[nodiscard]] inline auto memory_view_device<T>::size() const noexcept -> std::streamoff
{
    return span_device_.size();
}

template <memory_viewable T>
inline void memory_view_device<T>::reserve(const std::streamoff size)
{
    buffer_view_->reserve(size);
}

template <memory_viewable T>
inline void memory_view_device<T>::resize(const std::streamoff size)
{
    buffer_view_->resize(size);
    update_span();
}

template <memory_viewable T>
[[nodiscard]] const auto &memory_view_device<T>::data() const noexcept
{
    return *buffer_view_;
}

template <memory_viewable T>
void memory_view_device<T>::update_span()
{
    span_device_.set_span(std::span{*buffer_view_});
}

} // namespace aeon::streams
