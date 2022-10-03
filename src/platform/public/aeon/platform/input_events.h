// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/platform/keyboard_key.h>
#include <aeon/platform/keyboard_key_state.h>
#include <aeon/platform/mouse_button_state.h>
#include <aeon/platform/mouse_button.h>
#include <aeon/math/vector2.h>
#include <cstdint>

namespace aeon::platform
{

class context;

class input_events
{
public:
    input_events() noexcept = default;
    virtual ~input_events() = default;

    input_events(const input_events &) noexcept = default;
    auto operator=(const input_events &) noexcept -> input_events & = default;

    input_events(input_events &&) noexcept = default;
    auto operator=(input_events &&) noexcept -> input_events & = default;

    virtual void on_key([[maybe_unused]] const context &context, [[maybe_unused]] const keyboard_key key,
                        [[maybe_unused]] const std::uint32_t scan_code, [[maybe_unused]] const keyboard_key_state state)
    {
    }

    virtual void on_mouse_move([[maybe_unused]] const context &context,
                               [[maybe_unused]] const math::vector2<double> position)
    {
    }

    virtual void on_mouse_button([[maybe_unused]] const context &context, [[maybe_unused]] const mouse_button button,
                                 [[maybe_unused]] const mouse_button_state state)
    {
    }

    virtual void on_mouse_scroll([[maybe_unused]] const context &context, [[maybe_unused]] const double delta)
    {
    }
};

} // namespace aeon::platform
