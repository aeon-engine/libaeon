// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/descriptor_set_layout.h>
#include <aeon/vulkan/descriptor_set_layout_description.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_descriptor_set_layout(const device &device,
                                                const descriptor_set_layout_description &description)
{
    VkDescriptorSetLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.flags = description.flags();

    if (description.has_bindings())
    {
        info.bindingCount = description.binding_count();
        info.pBindings = std::data(description.bindings());
    }

    VkDescriptorSetLayout handle{};
    checked_result{vkCreateDescriptorSetLayout(vulkan::handle(device), &info, nullptr, &handle)};
    return handle;
}

} // namespace internal

descriptor_set_layout::descriptor_set_layout() noexcept
    : descriptor_set_layout_ref{}
{
}

descriptor_set_layout::descriptor_set_layout(const device &device, const descriptor_set_layout_description &description)
    : descriptor_set_layout_ref{device, internal::create_descriptor_set_layout(device, description)}
{
}

descriptor_set_layout::~descriptor_set_layout()
{
    destroy();
}

descriptor_set_layout::descriptor_set_layout(descriptor_set_layout &&other) noexcept
    : descriptor_set_layout_ref{other}
{
    other.handle_ = nullptr;
}

auto descriptor_set_layout::operator=(descriptor_set_layout &&other) noexcept -> descriptor_set_layout &
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

} // namespace aeon::vulkan
