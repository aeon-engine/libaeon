// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class pipeline_multisample_state_description final : public VkPipelineMultisampleStateCreateInfo
{
public:
    constexpr pipeline_multisample_state_description() noexcept;
    ~pipeline_multisample_state_description() noexcept = default;

    constexpr pipeline_multisample_state_description(const pipeline_multisample_state_description &) noexcept = default;
    constexpr auto operator=(const pipeline_multisample_state_description &) noexcept
        -> pipeline_multisample_state_description & = default;

    constexpr pipeline_multisample_state_description(pipeline_multisample_state_description &&) noexcept = default;
    constexpr auto operator=(pipeline_multisample_state_description &&) noexcept
        -> pipeline_multisample_state_description & = default;

    constexpr auto sample_count(const sample_count samples) noexcept -> pipeline_multisample_state_description &;
    constexpr auto enable_sample_shading(const bool enable = true) noexcept -> pipeline_multisample_state_description &;
    constexpr auto min_sample_shading(const float value) noexcept -> pipeline_multisample_state_description &;
    constexpr auto enable_alpha_to_coverage(const bool enable = true) noexcept
        -> pipeline_multisample_state_description &;
    constexpr auto enable_alpha_to_one(const bool enable = true) noexcept -> pipeline_multisample_state_description &;
};

static_assert(sizeof(pipeline_multisample_state_description) == sizeof(VkPipelineMultisampleStateCreateInfo));

inline constexpr pipeline_multisample_state_description::pipeline_multisample_state_description() noexcept
    : VkPipelineMultisampleStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                                           nullptr,
                                           0,
                                           VK_SAMPLE_COUNT_1_BIT,
                                           VK_FALSE,
                                           0.0f,
                                           nullptr,
                                           VK_FALSE,
                                           VK_FALSE}
{
}

inline constexpr auto pipeline_multisample_state_description::sample_count(const vulkan::sample_count samples) noexcept
    -> pipeline_multisample_state_description &
{
    rasterizationSamples = static_cast<VkSampleCountFlagBits>(samples);
    return *this;
}

inline constexpr auto pipeline_multisample_state_description::enable_sample_shading(const bool enable) noexcept
    -> pipeline_multisample_state_description &
{
    sampleShadingEnable = enable;
    return *this;
}

inline constexpr auto pipeline_multisample_state_description::min_sample_shading(const float value) noexcept
    -> pipeline_multisample_state_description &
{
    minSampleShading = value;
    return *this;
}

inline constexpr auto pipeline_multisample_state_description::enable_alpha_to_coverage(const bool enable) noexcept
    -> pipeline_multisample_state_description &
{
    alphaToCoverageEnable = enable;
    return *this;
}

inline constexpr auto pipeline_multisample_state_description::enable_alpha_to_one(const bool enable) noexcept
    -> pipeline_multisample_state_description &
{
    alphaToOneEnable = enable;
    return *this;
}

} // namespace aeon::vulkan
