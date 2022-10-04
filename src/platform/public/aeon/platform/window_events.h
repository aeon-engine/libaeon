// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/platform/window_iconification_state.h>
#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <cstdint>

namespace aeon::platform
{

class context;

class window_events
{
public:
    window_events() noexcept = default;
    virtual ~window_events() = default;

    window_events(const window_events &) noexcept = default;
    auto operator=(const window_events &) noexcept -> window_events & = default;

    window_events(window_events &&) noexcept = default;
    auto operator=(window_events &&) noexcept -> window_events & = default;

    virtual void on_window_position_changed([[maybe_unused]] const context &context,
                                            [[maybe_unused]] const math::vector2<std::int32_t> &position) noexcept
    {
    }

    virtual void on_window_size_changed([[maybe_unused]] const context &context,
                                        [[maybe_unused]] const math::size2d<std::int32_t> &size) noexcept
    {
    }

    virtual void on_window_framebuffer_size_changed([[maybe_unused]] const context &context,
                                                    [[maybe_unused]] const math::size2d<std::int32_t> &size) noexcept
    {
    }

    virtual void on_window_focus_changed([[maybe_unused]] const context &context,
                                         [[maybe_unused]] const bool focus) noexcept
    {
    }

    virtual void on_window_iconification_changed([[maybe_unused]] const context &context,
                                                 [[maybe_unused]] const window_iconification_state state) noexcept
    {
    }

    virtual void on_window_closed([[maybe_unused]] const context &context) noexcept
    {
    }
};

} // namespace aeon::platform
