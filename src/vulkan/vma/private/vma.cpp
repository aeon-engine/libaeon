// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/vma/vulkan_vma_export.h>

#ifdef VMA_CALL_PRE
#undef VMA_CALL_PRE
#endif
#define VMA_CALL_PRE AEON_VULKAN_VMA_EXPORT

#ifdef VMA_CALL_POST
#undef VMA_CALL_POST
#endif
#define VMA_CALL_POST __cdecl

#define VMA_IMPLEMENTATION

#include <vk_mem_alloc.h>
