// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/descriptor_set_layout_ref.h>
#include <aeon/vulkan/device.h>

namespace aeon::vulkan
{

descriptor_set_layout_ref::descriptor_set_layout_ref() noexcept
    : device_{nullptr}
    , handle_{VK_NULL_HANDLE}
{
}

descriptor_set_layout_ref::descriptor_set_layout_ref(const device &device, const VkDescriptorSetLayout handle) noexcept
    : device_{&device}
    , handle_{handle}
{
}

auto descriptor_set_layout_ref::handle() const noexcept -> VkDescriptorSetLayout
{
    return handle_;
}

auto descriptor_set_layout_ref::handle_ptr() const noexcept -> const VkDescriptorSetLayout *
{
    return &handle_;
}

void descriptor_set_layout_ref::destroy() noexcept
{
    if (handle_)
        vkDestroyDescriptorSetLayout(vulkan::handle(device_), handle_, nullptr);

    handle_ = VK_NULL_HANDLE;
}

} // namespace aeon::vulkan
