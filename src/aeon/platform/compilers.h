/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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
#define AEON_PACK_STRUCT_POP(nnn) __attribute__((aligned(nnn)))
#endif
