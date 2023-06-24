// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/fence.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/initializers.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_fence(const VkDevice device, const fence_create_state create_state) -> VkFence
{
    const auto create_info = initializers::fence_create_info(create_state);

    VkFence handle = VK_NULL_HANDLE;
    checked_result{vkCreateFence(device, &create_info, nullptr, &handle)};
    return handle;
}

} // namespace internal

fence::fence() noexcept
    : fence_ref{}
{
}

fence::fence(const device &dev, const fence_create_state create_state)
    : fence{vulkan::handle(dev), create_state}
{
}

fence::fence(const VkDevice device, const fence_create_state create_state)
    : fence{device, internal::create_fence(device, create_state)}
{
}

fence::fence(const VkDevice device, const VkFence handle)
    : fence_ref{device, handle}
{
}

fence::~fence() noexcept
{
    destroy();
}

fence::fence(fence &&other) noexcept
    : fence_ref{other}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto fence::operator=(fence &&other) noexcept -> fence &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;
        other.handle_ = VK_NULL_HANDLE;
    }

    return *this;
}

} // namespace aeon::vulkan
