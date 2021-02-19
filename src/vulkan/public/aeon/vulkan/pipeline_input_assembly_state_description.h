// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>

namespace aeon::vulkan
{

class pipeline_input_assembly_state_description final : public VkPipelineInputAssemblyStateCreateInfo
{
public:
    pipeline_input_assembly_state_description() noexcept;
    ~pipeline_input_assembly_state_description() noexcept = default;

    pipeline_input_assembly_state_description(const pipeline_input_assembly_state_description &) noexcept = default;
    auto operator=(const pipeline_input_assembly_state_description &) noexcept
        -> pipeline_input_assembly_state_description & = default;

    pipeline_input_assembly_state_description(pipeline_input_assembly_state_description &&) noexcept = default;
    auto operator=(pipeline_input_assembly_state_description &&) noexcept
        -> pipeline_input_assembly_state_description & = default;

    auto primitive_topology(const primitive_topology t) noexcept -> pipeline_input_assembly_state_description &;
    auto enable_primitive_restart(const bool enabled = true) noexcept -> pipeline_input_assembly_state_description &;
};

static_assert(sizeof(pipeline_input_assembly_state_description) == sizeof(VkPipelineInputAssemblyStateCreateInfo));

inline pipeline_input_assembly_state_description::pipeline_input_assembly_state_description() noexcept
    : VkPipelineInputAssemblyStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, nullptr, 0,
                                             VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE}
{
}

inline auto pipeline_input_assembly_state_description::primitive_topology(const vulkan::primitive_topology t) noexcept
    -> pipeline_input_assembly_state_description &
{
    VkPipelineInputAssemblyStateCreateInfo::topology = static_cast<VkPrimitiveTopology>(t);
    return *this;
}

inline auto pipeline_input_assembly_state_description::enable_primitive_restart(const bool enabled) noexcept
    -> pipeline_input_assembly_state_description &
{
    VkPipelineInputAssemblyStateCreateInfo::primitiveRestartEnable = enabled;
    return *this;
}

} // namespace aeon::vulkan
