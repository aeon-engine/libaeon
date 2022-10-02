// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;
class pipeline_layout_description;

class pipeline_layout final
{
public:
    pipeline_layout() noexcept;
    explicit pipeline_layout(const vulkan::device &device, const pipeline_layout_description &description);
    ~pipeline_layout() noexcept;

    pipeline_layout(const pipeline_layout &) noexcept = delete;
    auto operator=(const pipeline_layout &) noexcept -> pipeline_layout & = delete;

    pipeline_layout(pipeline_layout &&other) noexcept;
    auto operator=(pipeline_layout &&other) noexcept -> pipeline_layout &;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto handle() const noexcept -> VkPipelineLayout;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    VkPipelineLayout handle_;
};

[[nodiscard]] inline auto handle(const pipeline_layout &layout) noexcept
{
    return layout.handle();
}

} // namespace aeon::vulkan
