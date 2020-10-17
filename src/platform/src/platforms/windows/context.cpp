// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include "context.h"
#include "window.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

namespace aeon::platform
{

namespace internal
{

[[nodiscard]] auto translate_mouse_button(const UINT umsg, const WPARAM wparam) noexcept -> mouse_button
{
    switch (umsg)
    {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            return mouse_button::left;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            return mouse_button::right;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            return mouse_button::middle;
        default:
        {
            const auto xbutton = GET_XBUTTON_WPARAM(wparam);
            if (xbutton == XBUTTON1)
                return mouse_button::button4;
            else if (xbutton == XBUTTON2)
                return mouse_button::button5;

            break;
        }
    }

    return mouse_button::unknown;
}

} // namespace internal

AEON_PLATFORM_EXPORT [[nodiscard]] auto create_context() -> std::unique_ptr<context>
{
    return std::make_unique<context_win32>();
}

context_win32::context_win32() noexcept
    : base_context{}
{
    update_keyboard_modifier_key_states();
}

context_win32::~context_win32() = default;

auto context_win32::create_window(const window_create_info &info) -> std::unique_ptr<window>
{
    return std::make_unique<window_win32>(info, *this);
}

void context_win32::poll_events() noexcept
{
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

void context_win32::handle_keyboard_events(const WPARAM wparam, const LPARAM lparam, const bool key_down)
{
    auto key_code = static_cast<UINT>(wparam);
    auto is_repeated = (lparam & 0x40000000) != 0;

    switch (key_code)
    {
        case VK_SHIFT:
        {
            key_code = MapVirtualKey((lparam & 0x00ff0000) >> 16, MAPVK_VSC_TO_VK_EX);
            if (key_code == VK_LSHIFT)
            {
                is_repeated = key_states_.left_shift_state_;
                key_states_.left_shift_state_ = key_down;
            }
            else
            {
                is_repeated = key_states_.right_shift_state_;
                key_states_.right_shift_state_ = key_down;
            }
        }
        break;
        case VK_CONTROL:
        {
            if ((lparam & 0x1000000) == 0)
            {
                key_code = VK_LCONTROL;
                is_repeated = key_states_.left_ctrl_state_;
                key_states_.left_ctrl_state_ = key_down;
            }
            else
            {
                key_code = VK_RCONTROL;
                is_repeated = key_states_.right_ctrl_state_;
                key_states_.right_ctrl_state_ = key_down;
            }
        }
        break;
        case VK_MENU:
        {
            if ((lparam & 0x1000000) == 0)
            {
                key_code = VK_LMENU;
                is_repeated = key_states_.left_alt_state_;
                key_states_.left_alt_state_ = key_down;
            }
            else
            {
                key_code = VK_RMENU;
                is_repeated = key_states_.right_alt_state_;
                key_states_.right_alt_state_ = key_down;
            }
        }
        break;
        default:
            break;
    }

    key_states_.left_super_state_ = (GetAsyncKeyState(VK_LWIN) & 0x8000) != 0;
    key_states_.right_super_state_ = (GetAsyncKeyState(VK_RWIN) & 0x8000) != 0;
    key_states_.caps_lock_state_ = (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
    key_states_.num_lock_state_ = (GetAsyncKeyState(VK_NUMLOCK) & 0x0001) != 0;

    const auto char_code = MapVirtualKey(static_cast<UINT>(wparam), MAPVK_VK_TO_CHAR);

    if (key_down)
        input_listeners().invoke_each(&input_events::on_key_down, *this, key_code, char_code, is_repeated);
    else
        input_listeners().invoke_each(&input_events::on_key_up, *this, key_code, char_code, is_repeated);
}

void context_win32::handle_mouse_move_events(const LPARAM lparam)
{
    const auto x = GET_X_LPARAM(lparam);
    const auto y = GET_Y_LPARAM(lparam);
    input_listeners().invoke_each(&input_events::on_mouse_move, *this, math::vector2<std::int32_t>{x, y});
}

void context_win32::handle_mouse_events(const UINT umsg, const WPARAM wparam, const bool mouse_down)
{
    const auto button = internal::translate_mouse_button(umsg, wparam);

    if (mouse_down)
        input_listeners().invoke_each(&input_events::on_mouse_down, *this, button);
    else
        input_listeners().invoke_each(&input_events::on_mouse_up, *this, button);
}

void context_win32::handle_mouse_scroll(const std::int32_t delta)
{
    input_listeners().invoke_each(&input_events::on_mouse_scroll, *this, delta);
}

void context_win32::update_keyboard_modifier_key_states()
{
    key_states_.left_shift_state_ = (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0;
    key_states_.right_shift_state_ = (GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0;
    key_states_.left_ctrl_state_ = (GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0;
    key_states_.right_ctrl_state_ = (GetAsyncKeyState(VK_RCONTROL) & 0x8000) != 0;
    key_states_.left_alt_state_ = (GetAsyncKeyState(VK_LMENU) & 0x8000) != 0;
    key_states_.right_alt_state_ = (GetAsyncKeyState(VK_RMENU) & 0x8000) != 0;
    key_states_.left_super_state_ = (GetAsyncKeyState(VK_LWIN) & 0x8000) != 0;
    key_states_.right_super_state_ = (GetAsyncKeyState(VK_RWIN) & 0x8000) != 0;
    key_states_.caps_lock_state_ = (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
    key_states_.num_lock_state_ = (GetAsyncKeyState(VK_NUMLOCK) & 0x0001) != 0;
}

} // namespace aeon::platform
