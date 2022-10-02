// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class pipeline_depth_stencil_state_description final : public VkPipelineDepthStencilStateCreateInfo
{
public:
    constexpr pipeline_depth_stencil_state_description() noexcept;
    ~pipeline_depth_stencil_state_description() noexcept = default;

    constexpr pipeline_depth_stencil_state_description(const pipeline_depth_stencil_state_description &) noexcept =
        default;
    constexpr auto operator=(const pipeline_depth_stencil_state_description &) noexcept
        -> pipeline_depth_stencil_state_description & = default;

    constexpr pipeline_depth_stencil_state_description(pipeline_depth_stencil_state_description &&) noexcept = default;
    constexpr auto operator=(pipeline_depth_stencil_state_description &&) noexcept
        -> pipeline_depth_stencil_state_description & = default;

    constexpr auto enable_depth_test(const bool enable = true) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto enable_depth_write(const bool enable = true) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto compare_op(const compare_op op) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto enable_depth_bounds_test(const bool enable = true) noexcept
        -> pipeline_depth_stencil_state_description &;
    constexpr auto enable_stencil_test(const bool enable = true) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto front(const stencil_op fail_op = stencil_op::keep, const stencil_op pass_op = stencil_op::keep,
                         const stencil_op depth_fail = stencil_op::keep,
                         const vulkan::compare_op compare = vulkan::compare_op::never,
                         const std::uint32_t compare_mask = 0, const std::uint32_t write_mask = 0,
                         const std::uint32_t reference = 0);
    constexpr auto front(const VkStencilOpState state) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto back(const stencil_op fail_op = stencil_op::keep, const stencil_op pass_op = stencil_op::keep,
                        const stencil_op depth_fail = stencil_op::keep,
                        const vulkan::compare_op compare = vulkan::compare_op::never,
                        const std::uint32_t compare_mask = 0, const std::uint32_t write_mask = 0,
                        const std::uint32_t reference = 0);
    constexpr auto back(const VkStencilOpState state) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto min_depth_bounds(const float value) noexcept -> pipeline_depth_stencil_state_description &;
    constexpr auto max_depth_bounds(const float value) noexcept -> pipeline_depth_stencil_state_description &;
};

static_assert(sizeof(pipeline_depth_stencil_state_description) == sizeof(VkPipelineDepthStencilStateCreateInfo));

inline constexpr pipeline_depth_stencil_state_description::pipeline_depth_stencil_state_description() noexcept
    : VkPipelineDepthStencilStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                            nullptr,
                                            0,
                                            VK_TRUE,
                                            VK_TRUE,
                                            VK_COMPARE_OP_LESS_OR_EQUAL,
                                            VK_FALSE,
                                            VK_FALSE,
                                            {},
                                            {},
                                            0.0f,
                                            0.0f}
{
}

inline constexpr auto pipeline_depth_stencil_state_description::enable_depth_test(const bool enable) noexcept
    -> pipeline_depth_stencil_state_description &
{
    depthTestEnable = enable;
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::enable_depth_write(const bool enable) noexcept
    -> pipeline_depth_stencil_state_description &
{
    depthWriteEnable = enable;
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::compare_op(const vulkan::compare_op op) noexcept
    -> pipeline_depth_stencil_state_description &
{
    depthCompareOp = static_cast<VkCompareOp>(op);
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::enable_depth_bounds_test(const bool enable) noexcept
    -> pipeline_depth_stencil_state_description &
{
    depthBoundsTestEnable = enable;
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::enable_stencil_test(const bool enable) noexcept
    -> pipeline_depth_stencil_state_description &
{
    stencilTestEnable = enable;
    return *this;
}

constexpr auto pipeline_depth_stencil_state_description::front(
    const stencil_op fail_op, const stencil_op pass_op, const stencil_op depth_fail, const vulkan::compare_op compare,
    const std::uint32_t compare_mask, const std::uint32_t write_mask, const std::uint32_t reference)
{
    return front(VkStencilOpState{static_cast<VkStencilOp>(fail_op), static_cast<VkStencilOp>(pass_op),
                                  static_cast<VkStencilOp>(depth_fail), static_cast<VkCompareOp>(compare), compare_mask,
                                  write_mask, reference});
}

inline constexpr auto pipeline_depth_stencil_state_description::front(const VkStencilOpState state) noexcept
    -> pipeline_depth_stencil_state_description &
{
    VkPipelineDepthStencilStateCreateInfo::front = state;
    return *this;
}

constexpr auto pipeline_depth_stencil_state_description::back(
    const stencil_op fail_op, const stencil_op pass_op, const stencil_op depth_fail, const vulkan::compare_op compare,
    const std::uint32_t compare_mask, const std::uint32_t write_mask, const std::uint32_t reference)
{
    return back(VkStencilOpState{static_cast<VkStencilOp>(fail_op), static_cast<VkStencilOp>(pass_op),
                                 static_cast<VkStencilOp>(depth_fail), static_cast<VkCompareOp>(compare), compare_mask,
                                 write_mask, reference});
}

inline constexpr auto pipeline_depth_stencil_state_description::back(const VkStencilOpState state) noexcept
    -> pipeline_depth_stencil_state_description &
{
    VkPipelineDepthStencilStateCreateInfo::back = state;
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::min_depth_bounds(const float value) noexcept
    -> pipeline_depth_stencil_state_description &
{
    minDepthBounds = value;
    return *this;
}

inline constexpr auto pipeline_depth_stencil_state_description::max_depth_bounds(const float value) noexcept
    -> pipeline_depth_stencil_state_description &
{
    maxDepthBounds = value;
    return *this;
}

} // namespace aeon::vulkan
