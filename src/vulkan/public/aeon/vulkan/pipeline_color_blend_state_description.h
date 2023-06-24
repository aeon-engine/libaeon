// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/pipeline_color_blend_attachment_state.h>
#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <array>

namespace aeon::vulkan
{

class pipeline_color_blend_state_description final : public VkPipelineColorBlendStateCreateInfo
{
public:
    pipeline_color_blend_state_description() noexcept;
    ~pipeline_color_blend_state_description() noexcept = default;

    pipeline_color_blend_state_description(const pipeline_color_blend_state_description &other);
    auto operator=(const pipeline_color_blend_state_description &other) -> pipeline_color_blend_state_description &;

    pipeline_color_blend_state_description(pipeline_color_blend_state_description &&) noexcept = default;
    auto operator=(pipeline_color_blend_state_description &&) noexcept
        -> pipeline_color_blend_state_description & = default;

    auto enable_logic_op(const bool enable = true) noexcept -> pipeline_color_blend_state_description &;
    auto logic_op(const logic_op op) noexcept -> pipeline_color_blend_state_description &;

    auto blend_constants(const std::array<float, 4> constant) noexcept -> pipeline_color_blend_state_description &;

    auto add_attachment() -> pipeline_color_blend_attachment_state &;

private:
    std::vector<pipeline_color_blend_attachment_state> attachments_;
};

static_assert(sizeof(pipeline_color_blend_state_description) >= sizeof(VkPipelineColorBlendStateCreateInfo));

inline pipeline_color_blend_state_description::pipeline_color_blend_state_description() noexcept
    : VkPipelineColorBlendStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                                          nullptr,
                                          0,
                                          VK_FALSE,
                                          VK_LOGIC_OP_COPY,
                                          0,
                                          nullptr,
                                          {0.0f, 0.0f, 0.0f, 0.0f}}
{
}

inline pipeline_color_blend_state_description::pipeline_color_blend_state_description(
    const pipeline_color_blend_state_description &other)
    : VkPipelineColorBlendStateCreateInfo{other}
    , attachments_{other.attachments_}
{
    if (!std::empty(attachments_))
    {
        attachmentCount = static_cast<std::uint32_t>(std::size(attachments_));
        pAttachments = std::data(attachments_);
    }
}

inline auto pipeline_color_blend_state_description::operator=(const pipeline_color_blend_state_description &other)
    -> pipeline_color_blend_state_description &
{
    if (this == &other) [[unlikely]]
        return *this;

    sType = other.sType;
    pNext = other.pNext;
    flags = other.flags;
    logicOpEnable = other.logicOpEnable;
    logicOp = other.logicOp;
    attachmentCount = other.attachmentCount;
    pAttachments = other.pAttachments;
    blendConstants[0] = other.blendConstants[0];
    blendConstants[1] = other.blendConstants[1];
    blendConstants[2] = other.blendConstants[2];
    blendConstants[3] = other.blendConstants[3];

    attachments_ = other.attachments_;

    if (!std::empty(attachments_))
    {
        attachmentCount = static_cast<std::uint32_t>(std::size(attachments_));
        pAttachments = std::data(attachments_);
    }
    else
    {
        attachmentCount = 0;
        pAttachments = nullptr;
    }

    return *this;
}

inline auto pipeline_color_blend_state_description::enable_logic_op(const bool enable) noexcept
    -> pipeline_color_blend_state_description &
{
    logicOpEnable = enable;
    return *this;
}

inline auto pipeline_color_blend_state_description::logic_op(const vulkan::logic_op op) noexcept
    -> pipeline_color_blend_state_description &
{
    logicOp = static_cast<VkLogicOp>(op);
    return *this;
}

inline auto pipeline_color_blend_state_description::blend_constants(const std::array<float, 4> constant) noexcept
    -> pipeline_color_blend_state_description &
{
    blendConstants[0] = constant[0];
    blendConstants[1] = constant[1];
    blendConstants[2] = constant[2];
    blendConstants[3] = constant[3];
    return *this;
}

inline auto pipeline_color_blend_state_description::add_attachment() -> pipeline_color_blend_attachment_state &
{
    auto &result = attachments_.emplace_back();
    attachmentCount = static_cast<std::uint32_t>(std::size(attachments_));
    pAttachments = std::data(attachments_);
    return result;
}

} // namespace aeon::vulkan
