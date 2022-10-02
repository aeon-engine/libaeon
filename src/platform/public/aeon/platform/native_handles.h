// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
