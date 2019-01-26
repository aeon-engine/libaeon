// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#ifdef AEON_DLL_EXPORT
#undef AEON_DLL_EXPORT
#endif // AEON_DLL_EXPORT

#ifdef AEON_DLL_IMPORT
#undef AEON_DLL_IMPORT
#endif // AEON_DLL_IMPORT

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define AEON_DLL_EXPORT __declspec(dllexport)
#define AEON_DLL_IMPORT __declspec(dllimport)
#endif

#if (defined(AEON_PLATFORM_OS_LINUX) || defined(AEON_PLATFORM_OS_OSX))
#define AEON_DLL_EXPORT __attribute__((visibility("default")))
#define AEON_DLL_IMPORT __attribute__((visibility("default")))
#endif
