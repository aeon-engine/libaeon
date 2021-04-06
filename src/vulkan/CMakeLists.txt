# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

add_subdirectory(vma)

set(SOURCES
    private/buffer.cpp
    private/command_buffer.cpp
    private/command_buffer_ref.cpp
    private/command_pool.cpp
    private/debug.cpp
    private/descriptor_pool.cpp
    private/descriptor_set.cpp
    private/descriptor_set_layout.cpp
    private/descriptor_set_layout_ref.cpp
    private/device.cpp
    private/device_memory.cpp
    private/extension.cpp
    private/fence.cpp
    private/fence_pool.cpp
    private/fence_ref.cpp
    private/framebuffer.cpp
    private/image.cpp
    private/image_view.cpp
    private/image_view_ref.cpp
    private/instance.cpp
    private/layer.cpp
    private/physical_device.cpp
    private/pipeline.cpp
    private/pipeline_layout.cpp
    private/queue.cpp
    private/queue_indices.cpp
    private/render_pass.cpp
    private/render_pass_description.cpp
    private/semaphore.cpp
    private/semaphore_pool.cpp
    private/semaphore_ref.cpp
    private/shader_module.cpp
    private/subpass.cpp
    private/surface.cpp
    private/swap_chain.cpp
    public/aeon/vulkan/application_info.h
    public/aeon/vulkan/attachment.h
    public/aeon/vulkan/attachment_reference.h
    public/aeon/vulkan/buffer.h
    public/aeon/vulkan/checked_result.h
    public/aeon/vulkan/command_buffer.h
    public/aeon/vulkan/command_buffer_ref.h
    public/aeon/vulkan/command_pool.h
    public/aeon/vulkan/config.h
    public/aeon/vulkan/debug.h
    public/aeon/vulkan/descriptor_buffer_info.h
    public/aeon/vulkan/descriptor_pool.h
    public/aeon/vulkan/descriptor_pool_description.h
    public/aeon/vulkan/descriptor_set.h
    public/aeon/vulkan/descriptor_set_layout.h
    public/aeon/vulkan/descriptor_set_layout_description.h
    public/aeon/vulkan/descriptor_set_layout_ref.h
    public/aeon/vulkan/device.h
    public/aeon/vulkan/device_memory.h
    public/aeon/vulkan/enums.h
    public/aeon/vulkan/exception.h
    public/aeon/vulkan/extension.h
    public/aeon/vulkan/fence.h
    public/aeon/vulkan/fence_pool.h
    public/aeon/vulkan/fence_ref.h
    public/aeon/vulkan/flags.h
    public/aeon/vulkan/format.h
    public/aeon/vulkan/framebuffer.h
    public/aeon/vulkan/graphics_pipeline_description.h
    public/aeon/vulkan/image.h
    public/aeon/vulkan/image_view.h
    public/aeon/vulkan/image_view_ref.h
    public/aeon/vulkan/initializers.h
    public/aeon/vulkan/instance.h
    public/aeon/vulkan/layer.h
    public/aeon/vulkan/physical_device.h
    public/aeon/vulkan/pipeline.h
    public/aeon/vulkan/pipeline_color_blend_attachment_state.h
    public/aeon/vulkan/pipeline_color_blend_state_description.h
    public/aeon/vulkan/pipeline_depth_stencil_state_description.h
    public/aeon/vulkan/pipeline_dynamic_state_description.h
    public/aeon/vulkan/pipeline_input_assembly_state_description.h
    public/aeon/vulkan/pipeline_layout.h
    public/aeon/vulkan/pipeline_layout_description.h
    public/aeon/vulkan/pipeline_multisample_state_description.h
    public/aeon/vulkan/pipeline_rasterization_state_description.h
    public/aeon/vulkan/pipeline_shader_stage.h
    public/aeon/vulkan/pipeline_tesselation_state_description.h
    public/aeon/vulkan/pipeline_vertex_input_state_description.h
    public/aeon/vulkan/pipeline_viewport_state_description.h
    public/aeon/vulkan/queue.h
    public/aeon/vulkan/queue_indices.h
    public/aeon/vulkan/rectangle.h
    public/aeon/vulkan/render_pass.h
    public/aeon/vulkan/render_pass_begin_info.h
    public/aeon/vulkan/render_pass_description.h
    public/aeon/vulkan/semaphore.h
    public/aeon/vulkan/semaphore_pool.h
    public/aeon/vulkan/semaphore_ref.h
    public/aeon/vulkan/shader_module.h
    public/aeon/vulkan/subpass.h
    public/aeon/vulkan/subpass_dependency.h
    public/aeon/vulkan/surface.h
    public/aeon/vulkan/swap_chain.h
    public/aeon/vulkan/version.h
    public/aeon/vulkan/viewport.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_vulkan STATIC
    ${SOURCES}
)

set_target_properties(aeon_vulkan PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_vulkan
    PUBLIC
        public
    PRIVATE
        private
)

target_link_libraries(aeon_vulkan
    aeon_common
    aeon_streams
    aeon_math
    aeon_platform
    aeon_vulkan_vma
    LunarGVulkanSDK
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_subdirectory(example)
