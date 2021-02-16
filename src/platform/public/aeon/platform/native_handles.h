// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// Undef near and far because these common names clash with the math library
#undef near
#undef far
#endif

namespace aeon::platform
{

struct native_handles
{
#if (AEON_PLATFORM_OS_WINDOWS)
    HWND hwnd;
    HINSTANCE hinstance;
#endif
};

} // namespace aeon::platform
