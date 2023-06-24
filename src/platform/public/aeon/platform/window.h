// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/platform/window_iconification_state.h>
#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <aeon/math/rectangle.h>
#include <aeon/common/string.h>
#include <cstdint>

namespace aeon::platform
{

class context;
class window_events;
struct native_handles;

struct window_state_flags
{
    std::uint32_t position_changed : 1 = false;
    std::uint32_t dimensions_changed : 1 = false;
    std::uint32_t framebuffer_dimensions_changed : 1 = false;
    std::uint32_t focus_changed : 1 = false;
    std::uint32_t visibility_changed : 1 = false;
    std::uint32_t iconification_state_changed : 1 = false;
};

static_assert(sizeof(window_state_flags) == sizeof(std::uint32_t));

class window
{
public:
    window() noexcept = default;
    virtual ~window() = default;

    window(const window &) noexcept = delete;
    auto operator=(const window &) noexcept -> window & = delete;

    window(window &&) noexcept = delete;
    auto operator=(window &&) noexcept -> window & = delete;

    [[nodiscard]] virtual auto state_flags() const noexcept -> window_state_flags = 0;
    virtual void reset_state_flags() noexcept = 0;

    [[nodiscard]] virtual auto position() const noexcept -> math::vector2<std::int32_t> = 0;
    virtual void position(const math::vector2<std::int32_t> &pos) = 0;

    virtual void title(const common::string &str) = 0;

    [[nodiscard]] virtual auto dimensions() const noexcept -> math::size2d<std::uint32_t> = 0;
    virtual void dimensions(const math::size2d<std::uint32_t> &size) = 0;

    [[nodiscard]] virtual auto framebuffer_dimensions() const noexcept -> math::size2d<std::uint32_t> = 0;

    [[nodiscard]] virtual auto iconification_state() const noexcept -> window_iconification_state = 0;

    virtual void set_visible(const bool visible) const noexcept = 0;
    [[nodiscard]] virtual auto is_visible() const noexcept -> bool = 0;

    virtual void close() = 0;

    [[nodiscard]] virtual auto closed() const noexcept -> bool = 0;

    [[nodiscard]] virtual auto native_handles() const noexcept -> native_handles = 0;

    [[nodiscard]] virtual auto context() const noexcept -> const context & = 0;

    virtual void attach_window_listener(window_events &events) = 0;
    virtual void detach_window_listener(window_events &events) = 0;
    virtual void detach_all_window_listeners() = 0;
};

[[nodiscard]] inline auto position(const window &window) noexcept
{
    return window.position();
}

[[nodiscard]] inline auto dimensions(const window &window) noexcept
{
    return window.dimensions();
}

[[nodiscard]] inline auto rectangle(const window &window) noexcept
{
    return math::rectangle{position(window), math::size2d<std::int32_t>{dimensions(window)}};
}

} // namespace aeon::platform
