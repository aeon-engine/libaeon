// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/pipeline_layout.h>
#include <aeon/vulkan/pipeline_layout_description.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_pipeline_layout(const device &device, const pipeline_layout_description &description)
{
    VkPipelineLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if (description.has_set_layouts())
    {
        info.setLayoutCount = description.set_layout_count();
        info.pSetLayouts = std::data(description.set_layouts());
    }

    if (description.has_push_constant_ranges())
    {
        info.pushConstantRangeCount = description.push_constant_range_count();
        info.pPushConstantRanges = std::data(description.push_constant_ranges());
    }

    VkPipelineLayout handle{};
    checked_result{vkCreatePipelineLayout(vulkan::handle(device), &info, nullptr, &handle)};
    return handle;
}

} // namespace internal

pipeline_layout::pipeline_layout() noexcept
    : device_{nullptr}
    , handle_{nullptr}
{
}

pipeline_layout::pipeline_layout(const vulkan::device &device, const pipeline_layout_description &description)
    : device_{&device}
    , handle_{internal::create_pipeline_layout(device, description)}
{
}

pipeline_layout::~pipeline_layout() noexcept
{
    destroy();
}

pipeline_layout::pipeline_layout(pipeline_layout &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
{
    other.handle_ = nullptr;
}

auto pipeline_layout::operator=(pipeline_layout &&other) noexcept -> pipeline_layout &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;

        other.handle_ = nullptr;
    }

    return *this;
}

auto pipeline_layout::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto pipeline_layout::handle() const noexcept -> VkPipelineLayout
{
    return handle_;
}

void pipeline_layout::destroy() const noexcept
{
    if (handle_)
        vkDestroyPipelineLayout(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan
