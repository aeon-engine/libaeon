// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/fence_ref.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>
#include <limits>

namespace aeon::vulkan
{

fence_ref::fence_ref() noexcept
    : device_{nullptr}
    , handle_{VK_NULL_HANDLE}
{
}

fence_ref::fence_ref(const VkDevice device, const VkFence handle)
    : device_{device}
    , handle_{handle}
{
}

auto fence_ref::handle() const noexcept -> VkFence
{
    return handle_;
}

auto fence_ref::handle_ptr() const noexcept -> const VkFence *
{
    return &handle_;
}

void fence_ref::wait() const
{
    checked_result{wait_result()};
}

void fence_ref::wait(const std::chrono::nanoseconds time) const
{
    checked_result{wait_result(time)};
}

void fence_ref::wait(const std::uint64_t nanosecond_time) const
{
    checked_result{wait_result(nanosecond_time)};
}

auto fence_ref::wait_result() const noexcept -> VkResult
{
    return wait_result(std::numeric_limits<std::uint64_t>::max());
}

auto fence_ref::wait_result(const std::chrono::nanoseconds time) const noexcept -> VkResult
{
    return wait_result(static_cast<std::uint64_t>(time.count()));
}

auto fence_ref::wait_result(const std::uint64_t nanosecond_time) const noexcept -> VkResult
{
    return vkWaitForFences(device_, 1, &handle_, true, nanosecond_time);
}

auto fence_ref::is_signaled() const noexcept -> bool
{
    return vkGetFenceStatus(device_, handle_) == VK_SUCCESS;
}

void fence_ref::reset() const
{
    checked_result{vkResetFences(device_, 1, &handle_)};
}

auto fence_ref::reset_sync() const -> bool
{
    const auto result = wait_result(std::numeric_limits<std::uint64_t>::max());
    reset();
    return result;
}

void fence_ref::destroy() noexcept
{
    if (handle_)
        vkDestroyFence(device_, handle_, nullptr);

    handle_ = VK_NULL_HANDLE;
}

} // namespace aeon::vulkan
