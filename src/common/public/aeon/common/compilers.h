// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

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

#if (defined(AEON_PLATFORM_OS_WINDOWS) && !defined(__clang__))
#define AEON_PACK_STRUCT_PUSH(nnn) __pragma(pack(push, nnn))
#define AEON_PACK_STRUCT_POP(nnn) __pragma(pack(pop))
#else
#define AEON_PACK_STRUCT_PUSH(nnn)
#define AEON_PACK_STRUCT_POP(nnn) __attribute__((aligned(nnn), packed))
#endif

#if (defined(AEON_PLATFORM_OS_WINDOWS) && !defined(__clang__))
#define AEON_FORCE_INLINE __forceinline
#else
#define AEON_FORCE_INLINE inline
#endif

#if (defined(AEON_PLATFORM_OS_WINDOWS) && !defined(__clang__))
#define AEON_RESTRICT __restrict
#else
#define AEON_RESTRICT __restrict__
#endif

#if (!defined(NDEBUG))
#define AEON_DEBUG
#else
#undef AEON_DEBUG
#endif
