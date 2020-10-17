// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include "scoped_window_class.h"
#include "utility.h"

#define AEON_WINDOW_CLASSNAME_BASE L"AEON_WINDOW_"

#define ARROW_CURSOR MAKEINTRESOURCEW(32512)
#define DEFAULT_APP_ICON MAKEINTRESOURCEW(32512)

namespace aeon::platform
{

namespace internal
{
LRESULT CALLBACK window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
}

scoped_window_class::scoped_window_class()
    : classname_{}
{
    static auto index = 0;
    classname_ = AEON_WINDOW_CLASSNAME_BASE + std::to_wstring(++index);

    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = static_cast<WNDPROC>(internal::window_proc);
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.hCursor = LoadCursorW(nullptr, ARROW_CURSOR);
    wc.lpszClassName = classname();
    wc.hIcon = static_cast<HICON>(LoadImageW(nullptr, DEFAULT_APP_ICON, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

    if (!RegisterClassExW(&wc))
        internal::throw_last_error();
}

scoped_window_class::~scoped_window_class()
{
    UnregisterClassW(classname(), GetModuleHandleW(nullptr));
}

auto scoped_window_class::classname() const noexcept -> const wchar_t *
{
    return std::data(classname_);
}

} // namespace aeon::platform
