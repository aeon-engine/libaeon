// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/semaphore.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_semaphore(const VkDevice device) -> VkSemaphore
{
    const auto create_info = initializers::semaphore_create_info();

    VkSemaphore handle = nullptr;
    checked_result{vkCreateSemaphore(device, &create_info, nullptr, &handle)};
    return handle;
}

} // namespace internal

semaphore::semaphore() noexcept
    : semaphore_ref{}
{
}

semaphore::semaphore(const device &dev)
    : semaphore{vulkan::handle(dev)}
{
}

semaphore::semaphore(const VkDevice device)
    : semaphore{device, internal::create_semaphore(device)}
{
}

semaphore::semaphore(const VkDevice device, const VkSemaphore handle)
    : semaphore_ref{device, handle}
{
}

semaphore::~semaphore() noexcept
{
    destroy();
}

semaphore::semaphore(semaphore &&other) noexcept
    : semaphore_ref{other}
{
    other.handle_ = nullptr;
}

auto semaphore::operator=(semaphore &&other) noexcept -> semaphore &
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
