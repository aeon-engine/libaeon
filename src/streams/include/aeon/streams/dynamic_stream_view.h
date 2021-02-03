// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/common/assert.h>
#include <type_traits>
#include <memory>

namespace aeon::streams
{

template <typename device_t>
class dynamic_stream_view : public idynamic_stream
{
public:
    explicit dynamic_stream_view(device_t &device);

    ~dynamic_stream_view() override = default;

    dynamic_stream_view(dynamic_stream_view &&) noexcept(std::is_nothrow_move_constructible_v<device_t>) = default;
    auto operator=(dynamic_stream_view &&) noexcept(std::is_nothrow_move_assignable_v<device_t>)
        -> dynamic_stream_view & = default;

    dynamic_stream_view(const dynamic_stream_view &) noexcept(std::is_nothrow_copy_constructible_v<device_t>) = delete;
    auto operator=(const dynamic_stream_view &) noexcept(std::is_nothrow_copy_assignable_v<device_t>)
        -> dynamic_stream_view & = delete;

    auto read(char *data, const std::streamsize size) -> std::streamsize final;

    auto seekg(const std::streamoff offset, const seek_direction direction) -> bool final;

    [[nodiscard]] auto tellg() -> std::streamoff final;

    auto write(const char *data, const std::streamsize size) -> std::streamsize final;

    auto seekp(const std::streamoff offset, const seek_direction direction) -> bool final;

    [[nodiscard]] auto tellp() -> std::streamoff final;

    [[nodiscard]] auto eof() -> bool final;

    [[nodiscard]] auto good() -> bool final;

    [[nodiscard]] auto fail() -> bool final;

    void flush() final;

    [[nodiscard]] auto size() -> std::streamoff final;

    [[nodiscard]] auto is_input() const noexcept -> bool final;

    [[nodiscard]] auto is_input_seekable() const noexcept -> bool final;

    [[nodiscard]] auto is_output() const noexcept -> bool final;

    [[nodiscard]] auto is_output_seekable() const noexcept -> bool final;

    [[nodiscard]] auto has_eof() const noexcept -> bool final;

    [[nodiscard]] auto has_status() const noexcept -> bool final;

    [[nodiscard]] auto has_size() const noexcept -> bool final;

    [[nodiscard]] auto is_flushable() const noexcept -> bool final;

protected:
    dynamic_stream_view()
        : device_ref_{}
    {
    }

    device_t *device_ref_;
};

template <typename device_t>
inline dynamic_stream_view<device_t>::dynamic_stream_view(device_t &device)
    : device_ref_{&device}
{
    static_assert(is_device_v<device_t>, "Template argument must be a device or aggregate device.");
}

template <typename device_t>
inline auto dynamic_stream_view<device_t>::read([[maybe_unused]] char *data,
                                                [[maybe_unused]] const std::streamsize size) -> std::streamsize
{
    if constexpr (is_input_v<device_t>)
        return device_ref_->read(data, size);
    else
    {
        aeon_assert_fail("Device does not support read.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream_view<device_t>::seekg([[maybe_unused]] const std::streamoff offset,
                                                 [[maybe_unused]] const seek_direction direction) -> bool
{
    if constexpr (is_input_seekable_v<device_t>)
        return device_ref_->seekg(offset, direction);
    else
    {
        aeon_assert_fail("Device does not support seekg.");
        return false;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::tellg() -> std::streamoff
{
    if constexpr (is_input_seekable_v<device_t>)
        return device_ref_->tellg();
    else
    {
        aeon_assert_fail("Device does not support tellg.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream_view<device_t>::write([[maybe_unused]] const char *data,
                                                 [[maybe_unused]] const std::streamsize size) -> std::streamsize
{
    if constexpr (is_output_v<device_t>)
        return device_ref_->write(data, size);
    else
    {
        aeon_assert_fail("Device does not support write.");
        return 0;
    }
}

template <typename device_t>
inline auto dynamic_stream_view<device_t>::seekp([[maybe_unused]] const std::streamoff offset,
                                                 [[maybe_unused]] const seek_direction direction) -> bool
{
    if constexpr (is_output_seekable_v<device_t>)
        return device_ref_->seekp(offset, direction);
    else
    {
        aeon_assert_fail("Device does not support seekp.");
        return false;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::tellp() -> std::streamoff
{
    if constexpr (is_output_seekable_v<device_t>)
        return device_ref_->tellp();
    else
    {
        aeon_assert_fail("Device does not support tellp.");
        return 0;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::eof() -> bool
{
    if constexpr (has_eof_v<device_t>)
        return device_ref_->eof();
    else
    {
        aeon_assert_fail("Device does not support eof.");
        return false;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::good() -> bool
{
    if constexpr (has_status_v<device_t>)
        return device_ref_->good();
    else
    {
        aeon_assert_fail("Device does not support good.");
        return false;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::fail() -> bool
{
    if constexpr (has_status_v<device_t>)
        return device_ref_->fail();
    else
    {
        aeon_assert_fail("Device does not support fail.");
        return true;
    }
}

template <typename device_t>
inline void dynamic_stream_view<device_t>::flush()
{
    if constexpr (is_flushable_v<device_t>)
        device_ref_->flush();
    else
        aeon_assert_fail("Device does not support flush.");
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::size() -> std::streamoff
{
    if constexpr (has_size_v<device_t>)
        return device_ref_->size();
    else
    {
        aeon_assert_fail("Device does not support size.");
        return 0;
    }
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::is_input() const noexcept -> bool
{
    return is_input_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::is_input_seekable() const noexcept -> bool
{
    return is_input_seekable_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::is_output() const noexcept -> bool
{
    return is_output_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::is_output_seekable() const noexcept -> bool
{
    return is_output_seekable_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::has_eof() const noexcept -> bool
{
    return has_eof_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::has_status() const noexcept -> bool
{
    return has_status_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::has_size() const noexcept -> bool
{
    return has_size_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto dynamic_stream_view<device_t>::is_flushable() const noexcept -> bool
{
    return is_flushable_v<device_t>;
}

template <typename device_t>
[[nodiscard]] inline auto make_dynamic_stream_view(device_t &device) -> dynamic_stream_view<device_t>
{
    return dynamic_stream_view<device_t>(device);
}

template <typename device_t>
[[nodiscard]] inline auto make_dynamic_stream_view_ptr(device_t &device) -> std::unique_ptr<idynamic_stream>
{
    return std::make_unique<dynamic_stream_view<device_t>>(device);
}

} // namespace aeon::streams
