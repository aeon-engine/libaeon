// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/descriptor_pool.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_descriptor_pool(const vulkan::device &device, const descriptor_pool_description &description)
{
    VkDescriptorPool handle{};
    checked_result{vkCreateDescriptorPool(vulkan::handle(device), &description, nullptr, &handle)};
    return handle;
}

} // namespace internal

descriptor_pool::descriptor_pool() noexcept
    : device_{nullptr}
    , handle_{VK_NULL_HANDLE}
{
}

descriptor_pool::descriptor_pool(const vulkan::device &device, const descriptor_pool_description &description)
    : device_{&device}
    , handle_{internal::create_descriptor_pool(device, description)}
{
}

descriptor_pool::~descriptor_pool() noexcept
{
    destroy();
}

descriptor_pool::descriptor_pool(descriptor_pool &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto descriptor_pool::operator=(descriptor_pool &&other) noexcept -> descriptor_pool &
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

auto descriptor_pool::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto descriptor_pool::handle() const noexcept -> VkDescriptorPool
{
    return handle_;
}

void descriptor_pool::destroy() const noexcept
{
    if (handle_)
        vkDestroyDescriptorPool(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan
