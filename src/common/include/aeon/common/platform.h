// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

/* This header defines one or more of the following macro's:
 *
 * AEON_PLATFORM_OS_WINDOWS
 * AEON_PLATFORM_OS_WINDOWS_CYGWIN
 * AEON_PLATFORM_OS_LINUX
 * AEON_PLATFORM_OS_MACOS (AEON_PLATFORM_OS_OSX for backwards compatibility)
 * AEON_PLATFORM_OS_BSD
 * AEON_PLATFORM_OS_ANDROID
 * AEON_PLATFORM_OS_IOS
 * AEON_PLATFORM_OS_UNIX
 */

#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#define AEON_PLATFORM_OS_WINDOWS 1
#endif

#if (defined(__CYGWIN__))
#define AEON_PLATFORM_OS_WINDOWS_CYGWIN 1
#endif

#if (defined(linux) || defined(__linux))
#define AEON_PLATFORM_OS_LINUX 1
#endif

#if (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
#define AEON_PLATFORM_OS_OSX 1
#define AEON_PLATFORM_OS_MACOS 1
#endif

#if (defined(BSD) || defined(_SYSTYPE_BSD))
#define AEON_PLATFORM_OS_BSD 1
#endif

#if (__ANDROID__)
#define AEON_PLATFORM_OS_ANDROID 1
#endif

#if (defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__))
#define AEON_PLATFORM_OS_IOS
#endif

#if (defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE))
#define AEON_PLATFORM_OS_UNIX 1
#endif
