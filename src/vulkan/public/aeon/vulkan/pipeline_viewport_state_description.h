// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/viewport.h>
#include <aeon/vulkan/rectangle.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class pipeline_viewport_state_description final : public VkPipelineViewportStateCreateInfo
{
public:
    pipeline_viewport_state_description() noexcept;
    ~pipeline_viewport_state_description() noexcept = default;

    pipeline_viewport_state_description(const pipeline_viewport_state_description &other);
    auto operator=(const pipeline_viewport_state_description &other) -> pipeline_viewport_state_description &;

    pipeline_viewport_state_description(pipeline_viewport_state_description &&) noexcept = default;
    auto operator=(pipeline_viewport_state_description &&) noexcept -> pipeline_viewport_state_description & = default;

    auto add_viewport(const viewport vp) -> pipeline_viewport_state_description &;
    auto add_viewport(const VkViewport vp) -> pipeline_viewport_state_description &;

    auto add_scissor(const rectangle rect) -> pipeline_viewport_state_description &;
    auto add_scissor(const VkRect2D vp) -> pipeline_viewport_state_description &;

private:
    std::vector<viewport> viewports_;
    std::vector<rectangle> scissors_;
};

static_assert(sizeof(pipeline_viewport_state_description) >= sizeof(VkPipelineViewportStateCreateInfo));

inline pipeline_viewport_state_description::pipeline_viewport_state_description() noexcept
    : VkPipelineViewportStateCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, nullptr, 0,
                                        1, // TODO: When dynamic viewports and scissors are enabled, this is expected to
                                           // be 1. This needs to be properly handled.
                                        nullptr, 1, nullptr}
    , viewports_{}
    , scissors_{}
{
}

inline pipeline_viewport_state_description::pipeline_viewport_state_description(
    const pipeline_viewport_state_description &other)
    : VkPipelineViewportStateCreateInfo{other}
    , viewports_{other.viewports_}
    , scissors_{other.scissors_}
{
    if (!std::empty(viewports_))
    {
        viewportCount = static_cast<std::uint32_t>(std::size(viewports_));
        pViewports = std::data(viewports_);
    }

    if (!std::empty(scissors_))
    {
        scissorCount = static_cast<std::uint32_t>(std::size(scissors_));
        pScissors = std::data(scissors_);
    }
}

inline auto pipeline_viewport_state_description::operator=(const pipeline_viewport_state_description &other)
    -> pipeline_viewport_state_description &
{
    if (this == &other) [[unlikely]]
        return *this;

    sType = other.sType;
    pNext = other.pNext;
    flags = other.flags;

    viewports_ = other.viewports_;
    if (!std::empty(viewports_))
    {
        viewportCount = static_cast<std::uint32_t>(std::size(viewports_));
        pViewports = std::data(viewports_);
    }
    else
    {
        viewportCount = 1; // TODO: See ctor
        pViewports = nullptr;
    }

    scissors_ = other.scissors_;
    if (!std::empty(scissors_))
    {
        scissorCount = static_cast<std::uint32_t>(std::size(scissors_));
        pScissors = std::data(scissors_);
    }
    else
    {
        scissorCount = 1; // TODO: See ctor
        pScissors = nullptr;
    }

    return *this;
}

inline auto pipeline_viewport_state_description::add_viewport(const viewport vp)
    -> pipeline_viewport_state_description &
{
    viewports_.push_back(vp);
    viewportCount = static_cast<std::uint32_t>(std::size(viewports_));
    pViewports = std::data(viewports_);
    return *this;
}

inline auto pipeline_viewport_state_description::add_viewport(const VkViewport vp)
    -> pipeline_viewport_state_description &
{
    viewports_.emplace_back(vp);
    viewportCount = static_cast<std::uint32_t>(std::size(viewports_));
    pViewports = std::data(viewports_);
    return *this;
}

inline auto pipeline_viewport_state_description::add_scissor(const rectangle rect)
    -> pipeline_viewport_state_description &
{
    scissors_.push_back(rect);
    scissorCount = static_cast<std::uint32_t>(std::size(scissors_));
    pScissors = std::data(scissors_);
    return *this;
}

inline auto pipeline_viewport_state_description::add_scissor(const VkRect2D vp) -> pipeline_viewport_state_description &
{
    scissors_.emplace_back(vp);
    scissorCount = static_cast<std::uint32_t>(std::size(scissors_));
    pScissors = std::data(scissors_);
    return *this;
}

} // namespace aeon::vulkan
