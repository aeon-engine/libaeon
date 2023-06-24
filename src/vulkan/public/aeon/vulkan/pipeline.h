// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/graphics_pipeline_description.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;

class pipeline
{
public:
    pipeline() noexcept;
    explicit pipeline(const vulkan::device &device, const graphics_pipeline_description &description);
    ~pipeline() noexcept;

    pipeline(const pipeline &) noexcept = delete;
    auto operator=(const pipeline &) noexcept -> pipeline & = delete;

    pipeline(pipeline &&other) noexcept;
    auto operator=(pipeline &&other) noexcept -> pipeline &;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto handle() const noexcept -> VkPipeline;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    VkPipeline handle_;
};

[[nodiscard]] inline auto handle(const pipeline &p) noexcept
{
    return p.handle();
}

} // namespace aeon::vulkan
