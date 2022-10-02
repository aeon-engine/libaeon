# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

find_package(vulkan-memory-allocator CONFIG)

include(GenerateExportHeader)

set(SOURCES
    private/vma.cpp
    public/aeon/vulkan/vma/vma.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_vulkan_vma SHARED
    ${SOURCES}
)

if (MSVC)
    target_compile_options(aeon_vulkan_vma
        PRIVATE
            /wd4100
            /wd4127
            /wd4189
            /wd4324
    )
endif ()

generate_export_header(aeon_vulkan_vma
    EXPORT_FILE_NAME public/aeon/vulkan/vma/vulkan_vma_export.h
)

target_include_directories(aeon_vulkan_vma
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_vulkan_vma
    LunarGVulkanSDK
    vulkan-memory-allocator::vulkan-memory-allocator
)

set_target_properties(aeon_vulkan_vma PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
