// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

enum class attachment_load_op
{
    load = VK_ATTACHMENT_LOAD_OP_LOAD,
    clear = VK_ATTACHMENT_LOAD_OP_CLEAR,
    dont_care = VK_ATTACHMENT_LOAD_OP_DONT_CARE
};

enum class attachment_store_op
{
    store = VK_ATTACHMENT_STORE_OP_STORE,
    dont_care = VK_ATTACHMENT_STORE_OP_DONT_CARE,
};

enum class blend_factor
{
    zero = VK_BLEND_FACTOR_ZERO,
    one = VK_BLEND_FACTOR_ONE,
    src_color = VK_BLEND_FACTOR_SRC_COLOR,
    one_minus_src_color = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
    dst_color = VK_BLEND_FACTOR_DST_COLOR,
    one_minus_dst_color = VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,
    src_alpha = VK_BLEND_FACTOR_SRC_ALPHA,
    one_minus_src_alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
    dst_alpha = VK_BLEND_FACTOR_DST_ALPHA,
    one_minus_dst_alpha = VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
    constant_color = VK_BLEND_FACTOR_CONSTANT_COLOR,
    one_minus_constant_color = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
    constant_alpha = VK_BLEND_FACTOR_CONSTANT_ALPHA,
    one_minus_constant_alpha = VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
    src_alpha_saturate = VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,
    src1_color = VK_BLEND_FACTOR_SRC1_COLOR,
    one_minus_src1_color = VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
    src1_alpha = VK_BLEND_FACTOR_SRC1_ALPHA,
    one_minus_src1_alpha = VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA
};

enum class blend_op
{
    add = VK_BLEND_OP_ADD,
    subtract = VK_BLEND_OP_SUBTRACT,
    reverse_subtract = VK_BLEND_OP_REVERSE_SUBTRACT,
    min = VK_BLEND_OP_MIN,
    max = VK_BLEND_OP_MAX,
    zero_ext = VK_BLEND_OP_ZERO_EXT,
    src_ext = VK_BLEND_OP_SRC_EXT,
    dst_ext = VK_BLEND_OP_DST_EXT,
    src_over_ext = VK_BLEND_OP_SRC_OVER_EXT,
    dst_over_ext = VK_BLEND_OP_DST_OVER_EXT,
    src_in_ext = VK_BLEND_OP_SRC_IN_EXT,
    dst_in_ext = VK_BLEND_OP_DST_IN_EXT,
    src_out_ext = VK_BLEND_OP_SRC_OUT_EXT,
    dst_out_ext = VK_BLEND_OP_DST_OUT_EXT,
    src_atop_ext = VK_BLEND_OP_SRC_ATOP_EXT,
    dst_atop_ext = VK_BLEND_OP_DST_ATOP_EXT,
    xor_ext = VK_BLEND_OP_XOR_EXT,
    multiply_ext = VK_BLEND_OP_MULTIPLY_EXT,
    screen_ext = VK_BLEND_OP_SCREEN_EXT,
    overlay_ext = VK_BLEND_OP_OVERLAY_EXT,
    darken_ext = VK_BLEND_OP_DARKEN_EXT,
    lighten_ext = VK_BLEND_OP_LIGHTEN_EXT,
    colordodge_ext = VK_BLEND_OP_COLORDODGE_EXT,
    colorburn_ext = VK_BLEND_OP_COLORBURN_EXT,
    hardlight_ext = VK_BLEND_OP_HARDLIGHT_EXT,
    softlight_ext = VK_BLEND_OP_SOFTLIGHT_EXT,
    difference_ext = VK_BLEND_OP_DIFFERENCE_EXT,
    exclusion_ext = VK_BLEND_OP_EXCLUSION_EXT,
    invert_ext = VK_BLEND_OP_INVERT_EXT,
    invert_rgb_ext = VK_BLEND_OP_INVERT_RGB_EXT,
    lineardodge_ext = VK_BLEND_OP_LINEARDODGE_EXT,
    linearburn_ext = VK_BLEND_OP_LINEARBURN_EXT,
    vividlight_ext = VK_BLEND_OP_VIVIDLIGHT_EXT,
    linearlight_ext = VK_BLEND_OP_LINEARLIGHT_EXT,
    pinlight_ext = VK_BLEND_OP_PINLIGHT_EXT,
    hardmix_ext = VK_BLEND_OP_HARDMIX_EXT,
    hsl_hue_ext = VK_BLEND_OP_HSL_HUE_EXT,
    hsl_saturation_ext = VK_BLEND_OP_HSL_SATURATION_EXT,
    hsl_color_ext = VK_BLEND_OP_HSL_COLOR_EXT,
    hsl_luminosity_ext = VK_BLEND_OP_HSL_LUMINOSITY_EXT,
    plus_ext = VK_BLEND_OP_PLUS_EXT,
    plus_clamped_ext = VK_BLEND_OP_PLUS_CLAMPED_EXT,
    plus_clamped_alpha_ext = VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
    plus_darker_ext = VK_BLEND_OP_PLUS_DARKER_EXT,
    minus_ext = VK_BLEND_OP_MINUS_EXT,
    minus_clamped_ext = VK_BLEND_OP_MINUS_CLAMPED_EXT,
    contrast_ext = VK_BLEND_OP_CONTRAST_EXT,
    invert_ovg_ext = VK_BLEND_OP_INVERT_OVG_EXT,
    red_ext = VK_BLEND_OP_RED_EXT,
    green_ext = VK_BLEND_OP_GREEN_EXT,
    blue_ext = VK_BLEND_OP_BLUE_EXT
};

enum class buffer_sharing_mode
{
    exclusive = VK_SHARING_MODE_EXCLUSIVE,
    concurrent = VK_SHARING_MODE_CONCURRENT
};

enum class command_buffer_auto_begin
{
    disabled,
    enabled
};

enum class command_buffer_level
{
    primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
};

enum class compare_op
{
    never = VK_COMPARE_OP_NEVER,
    less = VK_COMPARE_OP_LESS,
    equal = VK_COMPARE_OP_EQUAL,
    less_of_equal = VK_COMPARE_OP_LESS_OR_EQUAL,
    greater = VK_COMPARE_OP_GREATER,
    not_equal = VK_COMPARE_OP_NOT_EQUAL,
    greater_or_equal = VK_COMPARE_OP_GREATER_OR_EQUAL,
    always = VK_COMPARE_OP_ALWAYS
};

enum class cull_mode
{
    none = VK_CULL_MODE_NONE,
    front = VK_CULL_MODE_FRONT_BIT,
    back = VK_CULL_MODE_BACK_BIT,
    front_and_back = VK_CULL_MODE_FRONT_AND_BACK
};

enum class descriptor_type
{
    sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
    combined_image_sampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    sampled_image = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
    storage_image = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
    uniform_texel_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
    storage_texel_buffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
    uniform_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    storage_buffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
    uniform_buffer_dynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
    storage_buffer_dynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
    input_attachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
};

enum class dynamic_state
{
    viewport = VK_DYNAMIC_STATE_VIEWPORT,
    scissor = VK_DYNAMIC_STATE_SCISSOR,
    line_width = VK_DYNAMIC_STATE_LINE_WIDTH,
    depth_bias = VK_DYNAMIC_STATE_DEPTH_BIAS,
    blend_constants = VK_DYNAMIC_STATE_BLEND_CONSTANTS,
    depth_bounds = VK_DYNAMIC_STATE_DEPTH_BOUNDS,
    stencil_compare_mask = VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
    stencil_write_mask = VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
    stencil_reference = VK_DYNAMIC_STATE_STENCIL_REFERENCE,
    viewport_w_scaling_nv = VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
    discard_rectangle_ext = VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
    sample_locations_ext = VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
};

enum class fence_create_state
{
    unsignaled = 0,
    signaled = VK_FENCE_CREATE_SIGNALED_BIT
};

enum class front_face
{
    counter_clockwise = VK_FRONT_FACE_COUNTER_CLOCKWISE,
    clockwise = VK_FRONT_FACE_CLOCKWISE
};

enum class image_tiling
{
    optimal = VK_IMAGE_TILING_OPTIMAL,
    linear = VK_IMAGE_TILING_LINEAR,
};

enum class image_type
{
    image_1d = VK_IMAGE_TYPE_1D,
    image_2d = VK_IMAGE_TYPE_2D,
    image_3d = VK_IMAGE_TYPE_3D
};

enum class image_view_type
{
    image_view_1d = VK_IMAGE_VIEW_TYPE_1D,
    image_view_2d = VK_IMAGE_VIEW_TYPE_2D,
    image_view_3d = VK_IMAGE_VIEW_TYPE_3D,
    image_view_cube = VK_IMAGE_VIEW_TYPE_CUBE,
    image_view_1d_array = VK_IMAGE_VIEW_TYPE_1D_ARRAY,
    image_view_2d_array = VK_IMAGE_VIEW_TYPE_2D_ARRAY,
    image_view_3d_array = VK_IMAGE_VIEW_TYPE_CUBE_ARRAY
};

enum class image_layout
{
    undefined = VK_IMAGE_LAYOUT_UNDEFINED,
    general = VK_IMAGE_LAYOUT_GENERAL,
    color_attachment_optimal = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    depth_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
    depth_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
    shader_read_only_optimal = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
    transfer_src_optimal = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
    transfer_dst_optimal = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    preinitialized = VK_IMAGE_LAYOUT_PREINITIALIZED,
    depth_read_only_stencil_attachment_optimal = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL,
    depth_attachment_stencil_read_only_optimal = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL,
    present_src_khr = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    shared_present_khr = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR,
};

enum class index_type
{
    uint16 = VK_INDEX_TYPE_UINT16,
    uint32 = VK_INDEX_TYPE_UINT32
};

enum class logic_op
{
    clear = VK_LOGIC_OP_CLEAR,
    and_op = VK_LOGIC_OP_AND,
    and_reverse = VK_LOGIC_OP_AND_REVERSE,
    copy = VK_LOGIC_OP_COPY,
    and_inverted = VK_LOGIC_OP_AND_INVERTED,
    no_op = VK_LOGIC_OP_NO_OP,
    xor_op = VK_LOGIC_OP_XOR,
    or_op = VK_LOGIC_OP_OR,
    nor = VK_LOGIC_OP_NOR,
    equivalent = VK_LOGIC_OP_EQUIVALENT,
    invert = VK_LOGIC_OP_INVERT,
    or_reverse = VK_LOGIC_OP_OR_REVERSE,
    copy_inverted = VK_LOGIC_OP_COPY_INVERTED,
    or_inverted = VK_LOGIC_OP_OR_INVERTED,
    nand = VK_LOGIC_OP_NAND,
    set = VK_LOGIC_OP_SET
};

enum class physical_device_type
{
    other = VK_PHYSICAL_DEVICE_TYPE_OTHER,
    integrated_gpu = VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU,
    discrete_gpu = VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
    virtual_gpu = VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,
    cpu = VK_PHYSICAL_DEVICE_TYPE_CPU
};

enum class pipeline_bind_point
{
    graphics = VK_PIPELINE_BIND_POINT_GRAPHICS,
    compute = VK_PIPELINE_BIND_POINT_COMPUTE
};

enum class polygon_mode
{
    fill = VK_POLYGON_MODE_FILL,
    line = VK_POLYGON_MODE_LINE,
    point = VK_POLYGON_MODE_POINT,
    fill_rectangle_nv = VK_POLYGON_MODE_FILL_RECTANGLE_NV
};

enum class primitive_topology
{
    point_list = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
    line_list = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
    line_strip = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,
    triangle_list = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    triangle_strip = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
    triangle_fan = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
    line_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
    line_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
    triangle_list_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
    triangle_strip_with_adjacency = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
    patch_list = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST,
};

enum class stencil_op
{
    keep = VK_STENCIL_OP_KEEP,
    zero = VK_STENCIL_OP_ZERO,
    replace = VK_STENCIL_OP_REPLACE,
    increment_and_clamp = VK_STENCIL_OP_INCREMENT_AND_CLAMP,
    decrement_and_clamp = VK_STENCIL_OP_DECREMENT_AND_CLAMP,
    invert = VK_STENCIL_OP_INVERT,
    increment_and_wrap = VK_STENCIL_OP_INCREMENT_AND_WRAP,
    decrement_and_wrap = VK_STENCIL_OP_DECREMENT_AND_WRAP
};

enum class subpass_contents
{
    inline_contents = VK_SUBPASS_CONTENTS_INLINE,
    secondary_command_buffers = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS
};

enum class vertex_input_rate
{
    vertex = VK_VERTEX_INPUT_RATE_VERTEX,
    instance = VK_VERTEX_INPUT_RATE_INSTANCE
};

} // namespace aeon::vulkan
