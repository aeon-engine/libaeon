// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/exception.h>

namespace aeon::streams
{

template <memory_viewable T = std::u8string>
class string_stream
{
public:
    using value_type = T;
    using element_type = typename value_type::value_type;

    string_stream() noexcept
        : device_{}
    {
    }

    explicit string_stream(const std::size_t reserve)
        : device_{}
    {
        device_.reserve(reserve);
    }

    ~string_stream() = default;

    string_stream(string_stream &&) = delete;
    auto operator=(string_stream &&) -> string_stream & = delete;

    string_stream(const string_stream &) = delete;
    auto operator=(const string_stream &) -> string_stream & = delete;

    void reserve(const std::size_t size)
    {
        device_.reserve(size);
    }

    void append(const std::string_view &val)
    {
        const auto size = static_cast<std::streamsize>(std::size(val));

        if (device_.write(reinterpret_cast<const std::byte *>(std::data(val)), size) != size)
            throw stream_exception{};
    }

    auto &operator<<(const std::string_view &val)
    {
        append(val);
        return *this;
    }

    void append(const std::u8string_view &val)
    {
        const auto size = static_cast<std::streamsize>(std::size(val));

        if (device_.write(reinterpret_cast<const std::byte *>(std::data(val)), size) != size)
            throw stream_exception{};
    }

    auto &operator<<(const std::u8string_view &val)
    {
        append(val);
        return *this;
    }

    void append(const char &val)
    {
        if (device_.write(reinterpret_cast<const std::byte *>(&val), sizeof(char)) != sizeof(char))
            throw stream_exception{};
    }

    auto &operator<<(const char &val)
    {
        append(val);
        return *this;
    }

    void append(const char8_t &val)
    {
        if (device_.write(reinterpret_cast<const std::byte *>(&val), sizeof(char8_t)) != sizeof(char8_t))
            throw stream_exception{};
    }

    auto &operator<<(const char8_t &val)
    {
        append(val);
        return *this;
    }

    [[nodiscard]] auto release() noexcept -> value_type
    {
        return device_.release();
    }

private:
    memory_device<value_type> device_;
};

} // namespace aeon::streams
