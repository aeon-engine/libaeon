// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class pipeline_rasterization_state_description final : public VkPipelineRasterizationStateCreateInfo
{
public:
    constexpr pipeline_rasterization_state_description() noexcept;
    ~pipeline_rasterization_state_description() noexcept = default;

    constexpr pipeline_rasterization_state_description(const pipeline_rasterization_state_description &) noexcept =
        default;
    constexpr auto operator=(const pipeline_rasterization_state_description &) noexcept
        -> pipeline_rasterization_state_description & = default;

    constexpr pipeline_rasterization_state_description(pipeline_rasterization_state_description &&) noexcept = default;
    constexpr auto operator=(pipeline_rasterization_state_description &&) noexcept
        -> pipeline_rasterization_state_description & = default;

    constexpr auto enable_depth_clamp(const bool enable = true) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto enable_rasterizer_discard(const bool enable = true) noexcept
        -> pipeline_rasterization_state_description &;
    constexpr auto polygon_mode(const polygon_mode mode) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto cull_mode(const cull_mode mode) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto front_face(const front_face ff) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto enable_depth_bias(const bool enable = true) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto depth_bias_constant_factor(const float value) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto depth_bias_clamp(const float value) noexcept -> pipeline_rasterization_state_description &;
    constexpr auto depth_bias_slope_factor(const float value) -> pipeline_rasterization_state_description &;
    constexpr auto depth_bias(const float constant_factor, const float clamp, const float slope_factor)
        -> pipeline_rasterization_state_description &;
    constexpr auto line_width(const float value) -> pipeline_rasterization_state_description &;
};

static_assert(sizeof(pipeline_rasterization_state_description) == sizeof(VkPipelineRasterizationStateCreateInfo));

inline constexpr pipeline_rasterization_state_description::pipeline_rasterization_state_description() noexcept
    : VkPipelineRasterizationStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                                             nullptr,
                                             0,
                                             VK_FALSE,
                                             VK_FALSE,
                                             VK_POLYGON_MODE_FILL,
                                             VK_CULL_MODE_BACK_BIT,
                                             VK_FRONT_FACE_COUNTER_CLOCKWISE,
                                             VK_FALSE,
                                             0.0f,
                                             0.0f,
                                             0.0f,
                                             1.0f}
{
}

inline constexpr auto pipeline_rasterization_state_description::enable_depth_clamp(const bool enable) noexcept
    -> pipeline_rasterization_state_description &
{
    depthClampEnable = enable;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::enable_rasterizer_discard(const bool enable) noexcept
    -> pipeline_rasterization_state_description &
{
    rasterizerDiscardEnable = enable;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::polygon_mode(const vulkan::polygon_mode mode) noexcept
    -> pipeline_rasterization_state_description &
{
    polygonMode = static_cast<VkPolygonMode>(mode);
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::cull_mode(const vulkan::cull_mode mode) noexcept
    -> pipeline_rasterization_state_description &
{
    cullMode = static_cast<VkCullModeFlags>(mode);
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::front_face(const vulkan::front_face ff) noexcept
    -> pipeline_rasterization_state_description &
{
    frontFace = static_cast<VkFrontFace>(ff);
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::enable_depth_bias(const bool enable) noexcept
    -> pipeline_rasterization_state_description &
{
    depthBiasEnable = enable;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::depth_bias_constant_factor(const float value) noexcept
    -> pipeline_rasterization_state_description &
{
    depthBiasConstantFactor = value;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::depth_bias_clamp(const float value) noexcept
    -> pipeline_rasterization_state_description &
{
    depthBiasClamp = value;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::depth_bias_slope_factor(const float value)
    -> pipeline_rasterization_state_description &
{
    depthBiasSlopeFactor = value;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::depth_bias(const float constant_factor,
                                                                           const float clamp, const float slope_factor)
    -> pipeline_rasterization_state_description &
{
    depthBiasEnable = true;
    depthBiasConstantFactor = constant_factor;
    depthBiasClamp = clamp;
    depthBiasSlopeFactor = slope_factor;
    return *this;
}

inline constexpr auto pipeline_rasterization_state_description::line_width(const float value)
    -> pipeline_rasterization_state_description &
{
    lineWidth = value;
    return *this;
}

} // namespace aeon::vulkan
