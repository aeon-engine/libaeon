// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define AEON_IGNORE_VS_WARNING(nnn) __pragma(warning(disable : nnn))
#define AEON_IGNORE_VS_WARNING_PUSH(nnn) __pragma(warning(push)) __pragma(warning(disable : nnn))
#define AEON_IGNORE_VS_WARNING_POP() __pragma(warning(pop))
#else // (AEON_PLATFORM_OS_WINDOWS)
#define AEON_IGNORE_VS_WARNING(nnn)
#define AEON_IGNORE_VS_WARNING_PUSH(nnn)
#define AEON_IGNORE_VS_WARNING_POP()
#endif

#if (AEON_PLATFORM_OS_WINDOWS)
#define AEON_PACK_STRUCT_PUSH(nnn) __pragma(pack(push, nnn))
#define AEON_PACK_STRUCT_POP(nnn) __pragma(pack(pop))
#else
#define AEON_PACK_STRUCT_PUSH(nnn)
#define AEON_PACK_STRUCT_POP(nnn) __attribute__((aligned(nnn), packed))
#endif
