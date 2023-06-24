// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class pipeline_dynamic_state_description final : public VkPipelineDynamicStateCreateInfo
{
public:
    pipeline_dynamic_state_description() noexcept;
    ~pipeline_dynamic_state_description() noexcept = default;

    pipeline_dynamic_state_description(const pipeline_dynamic_state_description &other);
    auto operator=(const pipeline_dynamic_state_description &other) -> pipeline_dynamic_state_description &;

    pipeline_dynamic_state_description(pipeline_dynamic_state_description &&) noexcept = default;
    auto operator=(pipeline_dynamic_state_description &&) noexcept -> pipeline_dynamic_state_description & = default;

    auto add_dynamic_state(const dynamic_state state) -> pipeline_dynamic_state_description &;
    auto add_dynamic_state(const VkDynamicState state) -> pipeline_dynamic_state_description &;

private:
    std::vector<VkDynamicState> dynamic_states_;
};

static_assert(sizeof(pipeline_dynamic_state_description) >= sizeof(VkPipelineDynamicStateCreateInfo));

inline pipeline_dynamic_state_description::pipeline_dynamic_state_description() noexcept
    : VkPipelineDynamicStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, nullptr, 0, 0, nullptr}
    , dynamic_states_{}
{
}

inline pipeline_dynamic_state_description::pipeline_dynamic_state_description(
    const pipeline_dynamic_state_description &other)
    : VkPipelineDynamicStateCreateInfo{other}
    , dynamic_states_{other.dynamic_states_}
{
    if (!std::empty(dynamic_states_))
    {
        dynamicStateCount = static_cast<std::uint32_t>(std::size(dynamic_states_));
        pDynamicStates = std::data(dynamic_states_);
    }
}

inline auto pipeline_dynamic_state_description::operator=(const pipeline_dynamic_state_description &other)
    -> pipeline_dynamic_state_description &
{
    if (this == &other) [[unlikely]]
        return *this;

    sType = other.sType;
    pNext = other.pNext;
    flags = other.flags;

    dynamic_states_ = other.dynamic_states_;

    if (!std::empty(dynamic_states_))
    {
        dynamicStateCount = other.dynamicStateCount;
        pDynamicStates = other.pDynamicStates;
    }
    else
    {
        dynamicStateCount = 0;
        pDynamicStates = nullptr;
    }

    return *this;
}

inline auto pipeline_dynamic_state_description::add_dynamic_state(const dynamic_state state)
    -> pipeline_dynamic_state_description &
{
    return add_dynamic_state(static_cast<VkDynamicState>(state));
}

inline auto pipeline_dynamic_state_description::add_dynamic_state(const VkDynamicState state)
    -> pipeline_dynamic_state_description &
{
    dynamic_states_.push_back(state);
    dynamicStateCount = static_cast<std::uint32_t>(std::size(dynamic_states_));
    pDynamicStates = std::data(dynamic_states_);
    return *this;
}

} // namespace aeon::vulkan
