# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(AddVulkanGLSLProgram)

set(SOURCES
    private/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(aeon_vulkan_example
    ${SOURCES}
)

set_target_properties(aeon_vulkan_example PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$(Configuration)"
)

target_include_directories(aeon_vulkan_example
    PRIVATE
        private
)

target_link_libraries(aeon_vulkan_example
    aeon_vulkan
    aeon_platform
)

add_vulkan_glsl_program(
    TARGET aeon_vulkan_example_shaders
    SOURCES
        shaders/shader.frag
        shaders/shader.vert
)

set_target_properties(aeon_vulkan_example_shaders PROPERTIES
    FOLDER dep/libaeon
)

add_dependencies(aeon_vulkan_example aeon_vulkan_example_shaders)
