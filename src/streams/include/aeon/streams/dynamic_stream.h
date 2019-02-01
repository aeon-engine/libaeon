// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/common/assert.h>
#include <type_traits>
#include <memory>

namespace aeon::streams
{

template <typename device_t>
class dynamic_stream final : public idynamic_stream
{
public:
    explicit dynamic_stream(device_t &&device);

    ~dynamic_stream() override = default;

    dynamic_stream(dynamic_stream &&) noexcept(std::is_nothrow_move_constructible_v<device_t>) = default;
    auto operator=(dynamic_stream &&) noexcept(std::is_nothrow_move_assignable_v<device_t>)
        -> dynamic_stream & = default;

    dynamic_stream(const dynamic_stream &) noexcept(std::is_nothrow_copy_constructible_v<device_t>) = delete;
    auto operator=(const dynamic_stream &) noexcept(std::is_nothrow_copy_assignable_v<device_t>)
        -> dynamic_stream & = delete;

    auto read(char *data, const std::streamsize size) -> std::streamsize override;

    auto seekg(const std::streamoff offset, const seek_direction direction) -> bool override;

    auto tellg() -> std::streamoff override;

    auto write(const char *data, const std::streamsize size) -> std::streamsize override;

    auto seekp(const std::streamoff offset, const seek_direction direction) -> bool override;

    auto tellp() -> std::streamoff override;

    auto eof() -> bool override;

    auto good() -> bool override;

    auto fail() -> bool override;

    void flush() override;

    auto size() -> std::streamoff override;

    auto is_input() const noexcept -> bool override;

    auto is_input_seekable() const noexcept -> bool override;

    auto is_output() const noexcept -> bool override;

    auto is_output_seekable() const noexcept -> bool override;

    auto has_eof() const noexcept -> bool override;

    auto has_status() const noexcept -> bool override;

    auto has_size() const noexcept -> bool override;

    auto is_flushable() const noexcept -> bool override;

private:
    device_t device_;
};

template <typename device_t>
inline dynamic_stream<device_t>::dynamic_stream(device_t &&device)
    : device_{std::move(device)}
{
    static_assert(is_device_v<device_t>, "Template argument must be a device or aggregate device.");
}

template <typename device_t>
inline auto dynamic_stream<device_t>::read(char *data, const std::streamsize size) -> std::streamsize
{
    if constexpr (is_input_v<device_t>)
        return device_.read(data, size);
    else
    {
        aeon_assert_fail("Device does not support read.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::seekg(const std::streamoff offset, const seek_direction direction) -> bool
{
    if constexpr (is_input_seekable_v<device_t>)
        return device_.seekg(offset, direction);
    else
    {
        aeon_assert_fail("Device does not support seekg.");
        return false;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::tellg() -> std::streamoff
{
    if constexpr (is_input_seekable_v<device_t>)
        return device_.tellg();
    else
    {
        aeon_assert_fail("Device does not support tellg.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::write(const char *data, const std::streamsize size) -> std::streamsize
{
    if constexpr (is_output_v<device_t>)
        return device_.write(data, size);
    else
    {
        aeon_assert_fail("Device does not support write.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::seekp(const std::streamoff offset, const seek_direction direction) -> bool
{
    if constexpr (is_output_seekable_v<device_t>)
        return device_.seekp(offset, direction);
    else
    {
        aeon_assert_fail("Device does not support seekp.");
        return false;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::tellp() -> std::streamoff
{
    if constexpr (is_output_seekable_v<device_t>)
        return device_.tellp();
    else
    {
        aeon_assert_fail("Device does not support tellp.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::eof() -> bool
{
    if constexpr (has_eof_v<device_t>)
        return device_.eof();
    else
    {
        aeon_assert_fail("Device does not support eof.");
        return false;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::good() -> bool
{
    if constexpr (has_status_v<device_t>)
        return device_.good();
    else
    {
        aeon_assert_fail("Device does not support good.");
        return false;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::fail() -> bool
{
    if constexpr (has_status_v<device_t>)
        return device_.fail();
    else
    {
        aeon_assert_fail("Device does not support fail.");
        return true;
    }
}

template <typename device_t>
inline void dynamic_stream<device_t>::flush()
{
    if constexpr (is_flushable_v<device_t>)
        device_.flush();
    else
        aeon_assert_fail("Device does not support flush.");
}

template <typename device_t>
inline auto dynamic_stream<device_t>::size() -> std::streamoff
{
    if constexpr (has_size_v<device_t>)
        return device_.size();
    else
    {
        aeon_assert_fail("Device does not support size.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream<device_t>::is_input() const noexcept -> bool
{
    return is_input_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::is_input_seekable() const noexcept -> bool
{
    return is_input_seekable_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::is_output() const noexcept -> bool
{
    return is_output_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::is_output_seekable() const noexcept -> bool
{
    return is_output_seekable_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::has_eof() const noexcept -> bool
{
    return has_eof_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::has_status() const noexcept -> bool
{
    return has_status_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::has_size() const noexcept -> bool
{
    return has_size_v<device_t>;
}

template <typename device_t>
inline auto dynamic_stream<device_t>::is_flushable() const noexcept -> bool
{
    return is_flushable_v<device_t>;
}

template <typename device_t>
inline auto make_dynamic_stream(device_t &&device) -> dynamic_stream<device_t>
{
    return dynamic_stream<device_t>(std::forward<device_t>(device));
}

template <typename device_t>
inline auto make_dynamic_stream_ptr(device_t &&device) -> std::unique_ptr<idynamic_stream>
{
    return std::unique_ptr<idynamic_stream>(new dynamic_stream<device_t>(std::forward<device_t>(device)));
}

} // namespace aeon::streams
