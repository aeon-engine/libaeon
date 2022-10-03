// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif (AEON_PLATFORM_OS_LINUX)
#include <X11/X.h>
#include <X11/Xlib.h>
#endif

namespace aeon::platform
{

struct native_handles
{
#if (AEON_PLATFORM_OS_WINDOWS)
    HWND hwnd = nullptr;
#elif (AEON_PLATFORM_OS_LINUX)
    Window window;
    Display *display;
#endif
};

} // namespace aeon::platform
