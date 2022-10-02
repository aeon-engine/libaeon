// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/platform/modifier_keys_state.h>
#include "base_context.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <array>

namespace aeon::platform
{

class context_win32 final : public base_context
{
public:
    context_win32() noexcept;
    ~context_win32() final;

    context_win32(const context_win32 &) noexcept = delete;
    auto operator=(const context_win32 &) noexcept -> context_win32 & = delete;

    context_win32(context_win32 &&) noexcept = delete;
    auto operator=(context_win32 &&) noexcept -> context_win32 & = delete;

    [[nodiscard]] auto create_window(const window_create_info &info) -> std::unique_ptr<window> final;
    void poll_events() noexcept final;

    void handle_keyboard_events(const WPARAM wparam, const LPARAM lparam, const bool key_down);
    void handle_mouse_move_events(const LPARAM lparam);
    void handle_mouse_events(const UINT umsg, const WPARAM wparam, const bool mouse_down);
    void handle_mouse_scroll(const std::int32_t delta);

    void update_keyboard_modifier_key_states();
};

} // namespace aeon::platform
