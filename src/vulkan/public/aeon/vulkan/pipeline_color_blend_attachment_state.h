// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class pipeline_color_blend_attachment_state final : public VkPipelineColorBlendAttachmentState
{
public:
    constexpr pipeline_color_blend_attachment_state() noexcept;
    ~pipeline_color_blend_attachment_state() noexcept = default;

    constexpr pipeline_color_blend_attachment_state(const pipeline_color_blend_attachment_state &) noexcept = default;
    constexpr auto operator=(const pipeline_color_blend_attachment_state &) noexcept
        -> pipeline_color_blend_attachment_state & = default;

    constexpr pipeline_color_blend_attachment_state(pipeline_color_blend_attachment_state &&) noexcept = default;
    constexpr auto operator=(pipeline_color_blend_attachment_state &&) noexcept
        -> pipeline_color_blend_attachment_state & = default;

    constexpr auto enable_blend(const bool enable = true) noexcept -> pipeline_color_blend_attachment_state &;
    constexpr auto source_color_blend_factor(const blend_factor factor) noexcept
        -> pipeline_color_blend_attachment_state &;
    constexpr auto destination_color_blend_factor(const blend_factor factor) noexcept
        -> pipeline_color_blend_attachment_state &;
    constexpr auto color_blend_op(const blend_op op) noexcept -> pipeline_color_blend_attachment_state &;
    constexpr auto source_alpha_blend_factor(const blend_factor factor) noexcept
        -> pipeline_color_blend_attachment_state &;
    constexpr auto destination_alpha_blend_factor(const blend_factor factor) noexcept
        -> pipeline_color_blend_attachment_state &;
    constexpr auto alpha_blend_op(const blend_op op) noexcept -> pipeline_color_blend_attachment_state &;
    constexpr auto color_write_mask(const common::flags<color_component_flag> mask) noexcept
        -> pipeline_color_blend_attachment_state &;
};

static_assert(sizeof(pipeline_color_blend_attachment_state) == sizeof(VkPipelineColorBlendAttachmentState));

inline constexpr pipeline_color_blend_attachment_state::pipeline_color_blend_attachment_state() noexcept
    : VkPipelineColorBlendAttachmentState{VK_FALSE,
                                          VK_BLEND_FACTOR_ZERO,
                                          VK_BLEND_FACTOR_ZERO,
                                          VK_BLEND_OP_ADD,
                                          VK_BLEND_FACTOR_ZERO,
                                          VK_BLEND_FACTOR_ZERO,
                                          VK_BLEND_OP_ADD,
                                          VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                              VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT}
{
}

inline constexpr auto pipeline_color_blend_attachment_state::enable_blend(const bool enable) noexcept
    -> pipeline_color_blend_attachment_state &
{
    blendEnable = enable;
    return *this;
}

inline constexpr auto
    pipeline_color_blend_attachment_state::source_color_blend_factor(const blend_factor factor) noexcept
    -> pipeline_color_blend_attachment_state &
{
    srcColorBlendFactor = static_cast<VkBlendFactor>(factor);
    return *this;
}

inline constexpr auto
    pipeline_color_blend_attachment_state::destination_color_blend_factor(const blend_factor factor) noexcept
    -> pipeline_color_blend_attachment_state &
{
    dstColorBlendFactor = static_cast<VkBlendFactor>(factor);
    return *this;
}

inline constexpr auto pipeline_color_blend_attachment_state::color_blend_op(const blend_op op) noexcept
    -> pipeline_color_blend_attachment_state &
{
    colorBlendOp = static_cast<VkBlendOp>(op);
    return *this;
}

inline constexpr auto
    pipeline_color_blend_attachment_state::source_alpha_blend_factor(const blend_factor factor) noexcept
    -> pipeline_color_blend_attachment_state &
{
    srcAlphaBlendFactor = static_cast<VkBlendFactor>(factor);
    return *this;
}

inline constexpr auto
    pipeline_color_blend_attachment_state::destination_alpha_blend_factor(const blend_factor factor) noexcept
    -> pipeline_color_blend_attachment_state &
{
    dstAlphaBlendFactor = static_cast<VkBlendFactor>(factor);
    return *this;
}

inline constexpr auto pipeline_color_blend_attachment_state::alpha_blend_op(const blend_op op) noexcept
    -> pipeline_color_blend_attachment_state &
{
    alphaBlendOp = static_cast<VkBlendOp>(op);
    return *this;
}

inline constexpr auto
    pipeline_color_blend_attachment_state::color_write_mask(const common::flags<color_component_flag> mask) noexcept
    -> pipeline_color_blend_attachment_state &
{
    colorWriteMask = mask;
    return *this;
}

} // namespace aeon::vulkan
