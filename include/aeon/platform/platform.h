/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

/* OS Detection mechanism based on Boost Predef (boost >= 1.55)
 * This header defines one or more of the following macro's:
 *
 * AEON_PLATFORM_OS_WINDOWS
 * AEON_PLATFORM_OS_WINDOWS_CYGWIN
 * AEON_PLATFORM_OS_LINUX
 * AEON_PLATFORM_OS_OSX
 * AEON_PLATFORM_OS_FREEBSD
 * AEON_PLATFORM_OS_NETBSD
 * AEON_PLATFORM_OS_OPENBSD
 * AEON_PLATFORM_OS_ANDROID
 * AEON_PLATFORM_OS_UNIX
 */

#if (BOOST_OS_WINDOWS)
#define AEON_PLATFORM_OS_WINDOWS 1
#endif // BOOST_OS_WINDOWS

#if (BOOST_OS_CYGWIN)
#define AEON_PLATFORM_OS_WINDOWS_CYGWIN 1
#endif // BOOST_OS_CYGWIN

#if (BOOST_OS_LINUX)
#define AEON_PLATFORM_OS_LINUX 1
#endif // BOOST_OS_LINUX

#if (BOOST_OS_MACOS)
#define AEON_PLATFORM_OS_OSX 1
#endif // BOOST_OS_MACOS

#if (BOOST_OS_BSD_FREE)
#define AEON_PLATFORM_OS_FREEBSD 1
#endif // BOOST_OS_BSD_FREE

#if (BOOST_OS_BSD_NET)
#define AEON_PLATFORM_OS_NETBSD 1
#endif // BOOST_OS_BSD_NET

#if (BOOST_OS_BSD_OPEN)
#define AEON_PLATFORM_OS_OPENBSD 1
#endif // BOOST_OS_BSD_OPEN

#if (BOOST_OS_ANDROID)
#define AEON_PLATFORM_OS_ANDROID 1
#endif // BOOST_OS_ANDROID

#if (BOOST_OS_UNIX)
#define AEON_PLATFORM_OS_UNIX 1
#endif // BOOST_OS_UNIX
