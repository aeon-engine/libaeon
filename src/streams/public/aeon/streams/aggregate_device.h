// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/devices/device.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/devices/device_view.h>
#include <aeon/common/type_traits.h>
#include <iostream>
#include <type_traits>

namespace aeon::streams
{

template <typename filter_t, typename device_t>
class aggregate_device;

template <typename>
struct is_aggregate_device
{
    static constexpr auto value = false;
};

template <typename filter_t, typename device_t>
struct is_aggregate_device<aggregate_device<filter_t, device_t>>
{
    static constexpr auto value = true;
};

template <int i>
struct aggregate_device_filter
{
    template <typename filter_t, typename device_t>
    static constexpr auto &get(aggregate_device<filter_t, device_t> &device) noexcept
    {
        return aggregate_device_filter<i - 1>::get(device.device_);
    }

    template <typename filter_t, typename device_t>
    static constexpr auto &get(const aggregate_device<filter_t, device_t> &device) noexcept
    {
        return aggregate_device_filter<i - 1>::get(device.device_);
    }
};

template <>
struct aggregate_device_filter<0>
{
    template <typename filter_t, typename device_t>
    static constexpr auto &get(aggregate_device<filter_t, device_t> &device) noexcept
    {
        return device;
    }

    template <typename filter_t, typename device_t>
    static constexpr auto &get(const aggregate_device<filter_t, device_t> &device) noexcept
    {
        return device;
    }
};

template <typename filter_t, typename device_t>
class aggregate_device : public device
{
    template <int>
    friend struct aggregate_device_filter;

public:
    struct category
        : common::type_traits::optional_base<has_any_eof_v<filter_t, device_t>, has_eof_tag>,
          common::type_traits::optional_base<has_any_status_v<filter_t, device_t>, has_status_tag>,
          common::type_traits::optional_base<has_any_size_v<filter_t, device_t>, has_size_tag>,
          common::type_traits::optional_base<is_any_flushable_v<filter_t, device_t>, flushable_tag>,
          common::type_traits::optional_base<is_any_input_v<filter_t, device_t>, input_tag>,
          common::type_traits::optional_base<is_any_input_seekable_v<filter_t, device_t>, input_seekable_tag>,
          common::type_traits::optional_base<is_any_output_v<filter_t, device_t>, output_tag>,
          common::type_traits::optional_base<is_any_output_seekable_v<filter_t, device_t>, output_seekable_tag>
    {
    };

    explicit aggregate_device(filter_t &&filter, device_t &&device);

    ~aggregate_device() = default;

    aggregate_device(aggregate_device &&) noexcept(
        std::is_nothrow_move_constructible_v<filter_t> &&std::is_nothrow_move_constructible_v<device_t>) = default;
    auto operator=(aggregate_device &&) noexcept(
        std::is_nothrow_move_assignable_v<filter_t> &&std::is_nothrow_move_assignable_v<device_t>)
        -> aggregate_device & = default;

    aggregate_device(const aggregate_device &) noexcept(
        std::is_nothrow_copy_constructible_v<filter_t> &&std::is_nothrow_copy_constructible_v<device_t>) = default;
    auto operator=(const aggregate_device &) noexcept(
        std::is_nothrow_copy_assignable_v<filter_t> &&std::is_nothrow_copy_assignable_v<device_t>)
        -> aggregate_device & = default;

    auto read(std::byte *data, const std::streamsize size) -> std::streamsize;

    auto seekg(const std::streamoff offset, const seek_direction direction) -> bool;

    [[nodiscard]] auto tellg() -> std::streamoff;

    auto write(const std::byte *data, const std::streamsize size) -> std::streamsize;

    auto seekp(const std::streamoff offset, const seek_direction direction) -> bool;

    [[nodiscard]] auto tellp() -> std::streamoff;

    [[nodiscard]] auto eof() -> bool;

    [[nodiscard]] auto good() -> bool;

    [[nodiscard]] auto fail() -> bool;

    void flush();

    [[nodiscard]] auto size() -> std::streamoff;

    [[nodiscard]] constexpr auto &device() noexcept
    {
        if constexpr (is_aggregate_device<device_t>::value)
        {
            return device_.device();
        }
        else
        {
            return device_;
        }
    }

    [[nodiscard]] constexpr auto &device() const noexcept
    {
        if constexpr (is_aggregate_device<device_t>::value)
        {
            return device_.device();
        }
        else
        {
            return device_;
        }
    }

    [[nodiscard]] static constexpr auto filter_count() noexcept -> int
    {
        if constexpr (is_aggregate_device<device_t>::value)
            return device_t::filter_count() + 1;
        else
            return 1;
    }

    [[nodiscard]] constexpr auto &filter() noexcept
    {
        return filter_;
    }

    [[nodiscard]] constexpr auto &filter() const noexcept
    {
        return filter_;
    }

    template <int i>
    [[nodiscard]] constexpr auto &filter() noexcept
    {
        constexpr auto count = filter_count() - i - 1;
        return aggregate_device_filter<count>::get(*this).filter();
    }

    template <int i>
    [[nodiscard]] constexpr auto &filter() const noexcept
    {
        constexpr auto count = filter_count() - i - 1;
        return aggregate_device_filter<count>::get(*this).filter();
    }

private:
    filter_t filter_;
    device_t device_;
};

template <typename filter_t, typename device_t>
inline aggregate_device<filter_t, device_t>::aggregate_device(filter_t &&filter, device_t &&device)
    : filter_{std::move(filter)}
    , device_{std::move(device)}
{
    static_assert(is_filter_v<filter_t>, "First template argument must be a filter.");
    static_assert(is_device_v<device_t>, "Second template argument must be a device or aggregate device.");
}

template <typename filter_t, typename device_t>
inline auto aggregate_device<filter_t, device_t>::read(std::byte *data, const std::streamsize size) -> std::streamsize
{
    static_assert(is_any_input_v<filter_t, device_t>, "Device does not support 'read'");

    if constexpr (is_input_v<filter_t>)
        return filter_.read(device_, data, size);
    else
        return device_.read(data, size);
}

template <typename filter_t, typename device_t>
inline auto aggregate_device<filter_t, device_t>::seekg(const std::streamoff offset, const seek_direction direction)
    -> bool
{
    static_assert(is_any_input_seekable_v<filter_t, device_t>, "Device does not support 'seekg'");

    if constexpr (is_input_seekable_v<filter_t>)
        return filter_.seekg(device_, offset, direction);
    else
        return device_.seekg(offset, direction);
}

template <typename filter_t, typename device_t>
[[nodiscard]] inline auto aggregate_device<filter_t, device_t>::tellg() -> std::streamoff
{
    static_assert(is_any_input_seekable_v<filter_t, device_t>, "Device does not support 'tellg'");

    if constexpr (is_input_seekable_v<filter_t>)
        return filter_.tellg(device_);
    else
        return device_.tellg();
}

template <typename filter_t, typename device_t>
inline auto aggregate_device<filter_t, device_t>::write(const std::byte *data, const std::streamsize size)
    -> std::streamsize
{
    static_assert(is_any_output_v<filter_t, device_t>, "Device does not support 'write'");

    if constexpr (is_output_v<filter_t>)
        return filter_.write(device_, data, size);
    else
        return device_.write(data, size);
}

template <typename filter_t, typename device_t>
inline auto aggregate_device<filter_t, device_t>::seekp(const std::streamoff offset, const seek_direction direction)
    -> bool
{
    static_assert(is_any_output_seekable_v<filter_t, device_t>, "Device does not support 'seekp'");

    if constexpr (is_output_seekable_v<filter_t>)
        return filter_.seekp(device_, offset, direction);
    else
        return device_.seekp(offset, direction);
}

template <typename filter_t, typename device_t>
[[nodiscard]] inline auto aggregate_device<filter_t, device_t>::tellp() -> std::streamoff
{
    static_assert(is_any_output_seekable_v<filter_t, device_t>, "Device does not support 'tellp'");

    if constexpr (is_output_seekable_v<filter_t>)
        return filter_.tellp(device_);
    else
        return device_.tellp();
}

template <typename filter_t, typename device_t>
inline auto aggregate_device<filter_t, device_t>::eof() -> bool
{
    static_assert(has_any_eof_v<filter_t, device_t>, "Device does not support 'eof'");

    if constexpr (has_eof_v<filter_t>)
        return filter_.eof(device_);
    else
        return device_.eof();
}

template <typename filter_t, typename device_t>
[[nodiscard]] inline auto aggregate_device<filter_t, device_t>::good() -> bool
{
    static_assert(has_any_status_v<filter_t, device_t>, "Device does not support 'good'");

    if constexpr (has_status_v<filter_t>)
        return filter_.good(device_);
    else
        return device_.good();
}

template <typename filter_t, typename device_t>
[[nodiscard]] inline auto aggregate_device<filter_t, device_t>::fail() -> bool
{
    static_assert(has_any_status_v<filter_t, device_t>, "Device does not support 'fail'");

    if constexpr (has_status_v<filter_t>)
        return filter_.fail(device_);
    else
        return device_.fail();
}

template <typename filter_t, typename device_t>
inline void aggregate_device<filter_t, device_t>::flush()
{
    static_assert(is_any_flushable_v<filter_t, device_t>, "Device does not support 'flush'");

    if constexpr (is_flushable_v<filter_t>)
        filter_.flush(device_);
    else
        device_.flush();
}

template <typename filter_t, typename device_t>
[[nodiscard]] inline auto aggregate_device<filter_t, device_t>::size() -> std::streamoff
{
    static_assert(has_any_size_v<filter_t, device_t>, "Device does not support 'size'");

    if constexpr (has_size_v<filter_t>)
        return filter_.size(device_);
    else
        return device_.size();
}

template <typename operator_device_t, typename operator_filter_t,
          std::enable_if_t<is_device_v<operator_device_t> && is_filter_v<operator_filter_t>, int> = 0>
[[nodiscard]] inline auto make_split(const aggregate_device<operator_filter_t, operator_device_t> &device)
{
    return device_view{device.device()};
}

template <int i, typename operator_device_t, typename operator_filter_t,
          std::enable_if_t<is_device_v<operator_device_t> && is_filter_v<operator_filter_t>, int> = 0>
[[nodiscard]] inline auto make_split(const aggregate_device<operator_filter_t, operator_device_t> &device)
{
    constexpr auto idx = aggregate_device<operator_filter_t, operator_device_t>::filter_count() - i - 1;
    return device_view{aggregate_device_filter<idx>::get(device)};
}

template <typename operator_device_t, typename operator_filter_t,
          std::enable_if_t<is_device_v<operator_device_t> && is_filter_v<operator_filter_t>, int> = 0>
inline auto operator|(operator_device_t &&device, operator_filter_t &&filter)
{
    return aggregate_device{std::forward<operator_filter_t>(filter), std::forward<operator_device_t>(device)};
}

} // namespace aeon::streams
