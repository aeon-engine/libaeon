// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/vma/vulkan_vma_export.h>
#include <aeon/common/platform.h>

#ifdef VMA_CALL_PRE
#undef VMA_CALL_PRE
#endif
#define VMA_CALL_PRE AEON_VULKAN_VMA_EXPORT

#ifdef VMA_CALL_POST
#undef VMA_CALL_POST
#endif

#if (AEON_PLATFORM_OS_WINDOWS)
#define VMA_CALL_POST __cdecl
#endif

#include <vk_mem_alloc.h>
