// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>
#include <cstdint>

namespace aeon::vulkan
{

class pipeline_tesselation_state_description final : public VkPipelineTessellationStateCreateInfo
{
public:
    constexpr pipeline_tesselation_state_description() noexcept;
    ~pipeline_tesselation_state_description() noexcept = default;

    constexpr pipeline_tesselation_state_description(const pipeline_tesselation_state_description &) noexcept = default;
    constexpr auto operator=(const pipeline_tesselation_state_description &) noexcept
        -> pipeline_tesselation_state_description & = default;

    constexpr pipeline_tesselation_state_description(pipeline_tesselation_state_description &&) noexcept = default;
    constexpr auto operator=(pipeline_tesselation_state_description &&) noexcept
        -> pipeline_tesselation_state_description & = default;

    constexpr auto patch_control_points(const std::uint32_t patch_control_points) noexcept
        -> pipeline_tesselation_state_description &;
};

static_assert(sizeof(pipeline_tesselation_state_description) == sizeof(VkPipelineTessellationStateCreateInfo));

inline constexpr pipeline_tesselation_state_description::pipeline_tesselation_state_description() noexcept
    : VkPipelineTessellationStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO, nullptr, 0, 0}
{
}

inline constexpr auto
    pipeline_tesselation_state_description::patch_control_points(const std::uint32_t patch_control_points) noexcept
    -> pipeline_tesselation_state_description &
{
    VkPipelineTessellationStateCreateInfo::patchControlPoints = patch_control_points;
    return *this;
}

} // namespace aeon::vulkan
