// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include "window.h"
#include "exception.h"
#include "utility.h"
#include "context.h"
#include <aeon/platform/window_create_info.h>
#include <aeon/platform/window_events.h>
#include <aeon/platform/native_handles.h>
#include <windowsx.h>
#include <iostream>

namespace aeon::platform
{

namespace internal
{

static constexpr auto aeon_window_propname = L"AEON_WINDOW";
static constexpr auto aeon_context_propname = L"AEON_CONTEXT";

LRESULT CALLBACK window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    auto *const window = get_window_property<window_win32>(hwnd, aeon_window_propname);
    auto *const context = get_window_property<context_win32>(hwnd, aeon_context_propname);

    if (!window || !context)
        return DefWindowProcW(hwnd, umsg, wparam, lparam);

    switch (umsg)
    {
        case WM_CLOSE:
        case WM_QUIT:
        {
            window->on_closing();
            break;
        }
        case WM_SIZE:
        {
            window->on_size_changed(math::size2d<std::int32_t>{LOWORD(lparam), HIWORD(lparam)});
            break;
        }
        case WM_MOVE:
        {
            window->on_position_changed(math::vector2<std::int32_t>{GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam)});
            break;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            context->handle_keyboard_events(wparam, lparam, true);
            break;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            context->handle_keyboard_events(wparam, lparam, false);
            break;
        }
        case WM_MOUSEMOVE:
        {
            context->handle_mouse_move_events(lparam);
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
        {
            context->handle_mouse_events(umsg, wparam, true);
            break;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
        {
            context->handle_mouse_events(umsg, wparam, false);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const auto delta =
                static_cast<std::int32_t>(static_cast<SHORT>(HIWORD(wparam)) / static_cast<double>(WHEEL_DELTA));
            context->handle_mouse_scroll(delta);
            break;
        }
        case WM_SETFOCUS:
        {
            context->update_keyboard_modifier_key_states();
            window->on_focus_change(true);
            break;
        }
        case WM_KILLFOCUS:
        {
            window->on_focus_change(false);
            break;
        }
        default:
            break;
    }

    return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

[[nodiscard]] static auto get_style(const window_create_info &info) noexcept
{
    DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION;

    if (info.resizable)
        style |= WS_MAXIMIZEBOX | WS_THICKFRAME;

    if (info.visible)
        style |= WS_VISIBLE;

    return style;
}

} // namespace internal

window_win32::window_win32(const window_create_info &info, context_win32 &context)
    : context_{context}
    , class_{}
    , handle_{}
    , events_{info.events}
    , closing_{false}
{
    math::vector2<int> position{CW_USEDEFAULT, CW_USEDEFAULT};

    if (info.position.has_value())
        position = info.position.value();

    const auto title = internal::to_wstring(info.title);
    const auto style = internal::get_style(info);
    const auto ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

    RECT window_rect;
    window_rect.left = 0;
    window_rect.top = 0;
    window_rect.right = info.size.width;
    window_rect.bottom = info.size.height;

    if (info.client_area_size)
        AdjustWindowRectEx(&window_rect, style, FALSE, ex_style);

    handle_ = CreateWindowExW(ex_style, class_.classname(), std::data(title), style, position.x, position.y,
                              window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, nullptr,
                              nullptr, GetModuleHandleW(nullptr), nullptr);

    if (!handle_)
        internal::throw_last_error();

    internal::set_window_property(handle_, internal::aeon_window_propname, this);
    internal::set_window_property(handle_, internal::aeon_context_propname, &context);
}

window_win32::~window_win32() = default;

auto window_win32::position() const noexcept -> math::vector2<std::int32_t>
{
    RECT rect{};
    GetWindowRect(handle_, &rect);
    return math::vector2<std::int32_t>{rect.left, rect.top};
}

void window_win32::position(const math::vector2<std::int32_t> &pos)
{
    if (!SetWindowPos(handle_, nullptr, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER))
        internal::throw_last_error();
}

void window_win32::title(const std::u8string &str)
{
    const auto title = internal::to_wstring(str);
    SetWindowTextW(handle_, std::data(title));
}

auto window_win32::dimensions() const noexcept -> math::size2d<std::int32_t>
{
    RECT rect{};
    GetWindowRect(handle_, &rect);
    return math::size2d<std::int32_t>{rect.right - rect.left, rect.bottom - rect.top};
}

void window_win32::dimensions(const math::size2d<std::int32_t> &size)
{
    if (!SetWindowPos(handle_, nullptr, 0, 0, size.width, size.height, SWP_NOMOVE | SWP_NOZORDER))
        internal::throw_last_error();
}

auto window_win32::client_dimensions() const noexcept -> math::size2d<std::int32_t>
{
    RECT rect{};
    GetClientRect(handle_, &rect);
    return math::size2d<std::int32_t>{rect.right - rect.left, rect.bottom - rect.top};
}

void window_win32::close()
{
    SendMessageW(handle_, WM_CLOSE, 0, 0);
}

auto window_win32::closed() const noexcept -> bool
{
    return closing_;
}

auto window_win32::native_handles() const noexcept -> platform::native_handles
{
    return {handle_, GetModuleHandleW(nullptr)};
}

auto window_win32::context() const noexcept -> const platform::context &
{
    return context_;
}

void window_win32::on_position_changed(const math::vector2<std::int32_t> &position) const noexcept
{
    if (events_)
        events_->on_window_position_changed(context_, position);
}

void window_win32::on_size_changed(const math::size2d<std::int32_t> &size) const noexcept
{
    if (events_)
        events_->on_window_size_changed(context_, size);
}

void window_win32::on_closing() noexcept
{
    if (closing_)
        return;

    closing_ = true;

    if (events_)
        events_->on_window_closed(context_);
}

void window_win32::on_focus_change(const bool focus) const noexcept
{
    if (events_)
        events_->on_window_focus_changed(context_, focus);
}

} // namespace aeon::platform
