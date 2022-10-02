// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::platform
{

class scoped_window_handle final
{
public:
    scoped_window_handle();

    explicit scoped_window_handle(const HWND handle);

    ~scoped_window_handle();

    scoped_window_handle(const scoped_window_handle &) noexcept = delete;
    auto operator=(const scoped_window_handle &) noexcept -> scoped_window_handle & = delete;

    scoped_window_handle(scoped_window_handle &&) noexcept = delete;
    auto operator=(scoped_window_handle &&) noexcept -> scoped_window_handle & = delete;

    auto operator=(const HWND handle) noexcept -> scoped_window_handle &;

    operator HWND() const;

private:
    HWND handle_;
};

inline scoped_window_handle::scoped_window_handle()
    : handle_{nullptr}
{
}

inline scoped_window_handle::scoped_window_handle(const HWND handle)
    : handle_{handle}
{
}

inline scoped_window_handle::~scoped_window_handle()
{
    if (handle_)
        DestroyWindow(handle_);
}

inline auto scoped_window_handle::operator=(const HWND handle) noexcept -> scoped_window_handle &
{
    handle_ = handle;
    return *this;
}

inline scoped_window_handle::operator HWND() const
{
    return handle_;
}

} // namespace aeon::platform
