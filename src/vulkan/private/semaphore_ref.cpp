// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/semaphore_ref.h>

namespace aeon::vulkan
{

semaphore_ref::semaphore_ref() noexcept
    : device_{nullptr}
    , handle_{nullptr}
{
}

semaphore_ref::semaphore_ref(const VkDevice device, const VkSemaphore handle) noexcept
    : device_{device}
    , handle_{handle}
{
}

auto semaphore_ref::handle() const noexcept -> VkSemaphore
{
    return handle_;
}

auto semaphore_ref::handle_ptr() const noexcept -> const VkSemaphore *
{
    return &handle_;
}

void semaphore_ref::destroy() noexcept
{
    if (handle_)
        vkDestroySemaphore(device_, handle_, nullptr);

    handle_ = nullptr;
}

} // namespace aeon::vulkan
