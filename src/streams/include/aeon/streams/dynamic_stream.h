// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/streams/dynamic_stream_view.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/common/compilers.h>
#include <type_traits>
#include <memory>

namespace aeon::streams
{

template <typename device_t>
class dynamic_stream final : public dynamic_stream_view<device_t>
{
public:
    explicit dynamic_stream(device_t &&device);

    virtual ~dynamic_stream() = default;

    dynamic_stream(dynamic_stream &&other) noexcept(std::is_nothrow_move_constructible_v<device_t>);
    auto operator=(dynamic_stream &&other) noexcept(std::is_nothrow_move_assignable_v<device_t>) -> dynamic_stream &;

    dynamic_stream(const dynamic_stream &) noexcept(std::is_nothrow_copy_constructible_v<device_t>) = delete;
    auto operator=(const dynamic_stream &) noexcept(std::is_nothrow_copy_assignable_v<device_t>)
        -> dynamic_stream & = delete;

private:
    device_t device_;
};

template <typename device_t>
inline dynamic_stream<device_t>::dynamic_stream(device_t &&device)
    : dynamic_stream_view<device_t>{}
    , device_{std::move(device)}
{
    static_assert(is_device_v<device_t>, "Template argument must be a device or aggregate device.");
    dynamic_stream_view<device_t>::device_ref_ = &device_;
}

template <typename device_t>
inline dynamic_stream<device_t>::dynamic_stream(dynamic_stream &&other) noexcept(
    std::is_nothrow_move_constructible_v<device_t>)
    : dynamic_stream_view<device_t>{}
    , device_{std::move(other.device_)}
{
    dynamic_stream_view<device_t>::device_ref_ = &device_;
}

template <typename device_t>
inline auto
    dynamic_stream<device_t>::operator=(dynamic_stream &&other) noexcept(std::is_nothrow_move_assignable_v<device_t>)
        -> dynamic_stream &
{
    if (AEON_LIKELY(this != &other))
    {
        device_ = std::move(other.device_);
        dynamic_stream_view<device_t>::device_ref_ = &device_;
    }

    return *this;
}

template <typename device_t>
inline auto make_dynamic_stream(device_t &&device) -> dynamic_stream<device_t>
{
    return dynamic_stream<device_t>(std::forward<device_t>(device));
}

template <typename device_t>
inline auto make_dynamic_stream_ptr(device_t &&device) -> std::unique_ptr<idynamic_stream>
{
    return std::make_unique<dynamic_stream<device_t>>(std::forward<device_t>(device));
}

} // namespace aeon::streams
