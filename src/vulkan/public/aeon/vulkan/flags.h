// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/flags.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

enum class access_flag : VkAccessFlags
{
    none = 0,
    indirect_command_read = VK_ACCESS_INDIRECT_COMMAND_READ_BIT,
    index_read = VK_ACCESS_INDEX_READ_BIT,
    vertex_attribute_read = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
    uniform_read = VK_ACCESS_UNIFORM_READ_BIT,
    input_attachment_read = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
    shader_read = VK_ACCESS_SHADER_READ_BIT,
    shader_write = VK_ACCESS_SHADER_WRITE_BIT,
    color_attachment_read = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
    color_attachment_write = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
    depth_stencil_attachment_read = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
    depth_stencil_attachment_write = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
    transfer_read = VK_ACCESS_TRANSFER_READ_BIT,
    transfer_write = VK_ACCESS_TRANSFER_WRITE_BIT,
    host_read = VK_ACCESS_HOST_READ_BIT,
    host_write = VK_ACCESS_HOST_WRITE_BIT,
    memory_read = VK_ACCESS_MEMORY_READ_BIT,
    memory_write = VK_ACCESS_MEMORY_WRITE_BIT,
    color_attachment_read_noncoherent_ext = VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT,
};

aeon_declare_flag_operators(access_flag)

enum class attachment_description_flag : VkAttachmentDescriptionFlags
{
    none = 0,
    may_alias = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
};

aeon_declare_flag_operators(attachment_description_flag)

enum class buffer_usage_flag : VkBufferUsageFlags
{
    transfer_src = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    transfer_dst = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
    uniform_texel_buffer = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
    storage_texel_buffer = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
    uniform_buffer = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
    storage_buffer = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
    index_buffer = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
    vertex_buffer = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
    indirect_buffer = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
};

aeon_declare_flag_operators(buffer_usage_flag)

enum class command_pool_create_flag : VkCommandPoolCreateFlags
{
    create_transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
    reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    created_protected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT
};

aeon_declare_flag_operators(command_pool_create_flag)

enum class command_buffer_usage_flag : VkCommandBufferUsageFlags
{
    none = 0,
    one_time = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    render_pass_continue = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT,
    simultaneous_use = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
};

aeon_declare_flag_operators(command_buffer_usage_flag)

enum class color_component_flag : VkColorComponentFlags
{
    red = VK_COLOR_COMPONENT_R_BIT,
    green = VK_COLOR_COMPONENT_G_BIT,
    blue = VK_COLOR_COMPONENT_B_BIT,
    alpha = VK_COLOR_COMPONENT_A_BIT,
    all = red | green | blue | alpha
};

aeon_declare_flag_operators(color_component_flag)

enum class dependency_flag : VkDependencyFlags
{
    by_region = VK_DEPENDENCY_BY_REGION_BIT,
    device_group = VK_DEPENDENCY_DEVICE_GROUP_BIT,
    view_local = VK_DEPENDENCY_VIEW_LOCAL_BIT
};

aeon_declare_flag_operators(dependency_flag)

enum class descriptor_pool_create_flag : VkDescriptorPoolCreateFlags
{
    none = 0,
    free_descriptor_set = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
};

aeon_declare_flag_operators(descriptor_pool_create_flag)

enum class descriptor_set_layout_create_flag : VkDescriptorSetLayoutCreateFlags
{
    none = 0,
    create_push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR
};

aeon_declare_flag_operators(descriptor_set_layout_create_flag)

enum class framebuffer_create_flag : VkFramebufferCreateFlags
{
    none = 0,
};

aeon_declare_flag_operators(framebuffer_create_flag)

enum class message_severity : VkDebugUtilsMessageSeverityFlagsEXT
{
    verbose = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT,
    info = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
    warning = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
    error = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    all = verbose | info | warning | error,
    important = warning | error
};

aeon_declare_flag_operators(message_severity)

enum class message_type : VkDebugUtilsMessageTypeFlagsEXT
{
    general = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT,
    validation = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
    performance = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    all = general | validation | performance
};

aeon_declare_flag_operators(message_type)

enum class image_create_flag : VkImageCreateFlags
{
    sparse_binding = VK_IMAGE_CREATE_SPARSE_BINDING_BIT,
    sparse_residency = VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT,
    sparse_aliased = VK_IMAGE_CREATE_SPARSE_ALIASED_BIT,
    mutable_format = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
    cube_compatible = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
    alias = VK_IMAGE_CREATE_ALIAS_BIT,
    split_instance_bind_regions = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT,
    create_2d_array_compatible = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT,
    block_texel_view_compatible = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,
    extended_usage = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT,
    create_protected = VK_IMAGE_CREATE_PROTECTED_BIT,
    disjoint = VK_IMAGE_CREATE_DISJOINT_BIT,
    sample_locations_compatible_depth_ext = VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT,
};

aeon_declare_flag_operators(image_create_flag)

enum class image_usage_flag : VkImageUsageFlags
{
    transfer_src = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
    transfer_dst = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
    sampled = VK_IMAGE_USAGE_SAMPLED_BIT,
    storage = VK_IMAGE_USAGE_STORAGE_BIT,
    color_attachment = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    depth_stencil_attachment = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    transient_attachment = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
    input_attachment = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
};

aeon_declare_flag_operators(image_usage_flag)

enum class memory_flag : VkMemoryPropertyFlags
{
    device_local = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    host_visible = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
    host_coherent = VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    host_cached = VK_MEMORY_PROPERTY_HOST_CACHED_BIT,
    lazily_allocated = VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT,
    property_protected = VK_MEMORY_PROPERTY_PROTECTED_BIT
};

aeon_declare_flag_operators(memory_flag)

enum class pipeline_create_flag : VkPipelineCreateFlags
{
    none = 0,
    disable_optimization = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT,
    allow_derivatives = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT,
    derivative = VK_PIPELINE_CREATE_DERIVATIVE_BIT,
    view_index_from_device_index = VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT,
};

aeon_declare_flag_operators(pipeline_create_flag)

enum class pipeline_stage_flag : VkPipelineStageFlags
{
    none = 0,
    top_of_pipe = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
    draw_indirect = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
    vertex_input = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
    vertex_shader = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
    tessellation_control_shader = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
    tessellation_evaluation_shader = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
    geometry_shader = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
    fragment_shader = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
    early_fragment_tests = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
    late_fragment_tests = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
    color_attachment_output = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    compute_shader = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
    transfer = VK_PIPELINE_STAGE_TRANSFER_BIT,
    bottom_of_pipe = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
    host = VK_PIPELINE_STAGE_HOST_BIT,
    all_graphics = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
    all_commands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
};

aeon_declare_flag_operators(pipeline_stage_flag)

enum class sample_count_flag : VkSampleCountFlags
{
    count_1 = VK_SAMPLE_COUNT_1_BIT,
    count_2 = VK_SAMPLE_COUNT_2_BIT,
    count_4 = VK_SAMPLE_COUNT_4_BIT,
    count_8 = VK_SAMPLE_COUNT_8_BIT,
    count_16 = VK_SAMPLE_COUNT_16_BIT,
    count_32 = VK_SAMPLE_COUNT_32_BIT,
    count_64 = VK_SAMPLE_COUNT_64_BIT
};

aeon_declare_flag_operators(sample_count_flag)

using sample_count = sample_count_flag;

enum class sampler_create_flag : VkSamplerCreateFlags
{
    none = 0,
    create_subsampled = VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT,
    create_subsampled_coarse_reconstruction = VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT
};

aeon_declare_flag_operators(sampler_create_flag)

enum class shader_stage_flag : VkShaderStageFlags
{
    vertex = VK_SHADER_STAGE_VERTEX_BIT,
    tessellation_control = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
    tessellation_evaluation = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
    geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
    fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
    compute = VK_SHADER_STAGE_COMPUTE_BIT,
    all_graphics = VK_SHADER_STAGE_ALL_GRAPHICS,
    all = VK_SHADER_STAGE_ALL
};

using shader_stage = shader_stage_flag;

aeon_declare_flag_operators(shader_stage_flag)

enum class subpass_description_flag : VkSubpassDescriptionFlags
{
    per_view_attributes_nvx = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
    per_view_position_x_only_nvx = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
};

aeon_declare_flag_operators(subpass_description_flag)

} // namespace aeon::vulkan
