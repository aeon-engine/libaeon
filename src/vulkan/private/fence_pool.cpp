// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/fence_pool.h>
#include <aeon/vulkan/fence.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

fence_pool::fence_pool(const device &dev)
    : device_{dev}
    , fences_{}
    , active_count_{0}
{
}

fence_pool::fence_pool(const device &dev, const std::uint64_t pre_allocate)
    : device_{dev}
    , fences_{}
    , active_count_{0}
{
    fences_.reserve(pre_allocate);
    for (auto i = 0ull; i < pre_allocate; ++i)
    {
        fences_.push_back(internal::create_fence(handle(device_)));
    }
}

fence_pool::~fence_pool() noexcept
{
    [[maybe_unused]] auto result = wait();
    reset();

    for (const auto fence : fences_)
    {
        fence_ref{handle(device_), fence}.destroy();
    }
}

void fence_pool::reserve(const std::uint64_t size)
{
    fences_.reserve(size);
}

auto fence_pool::request() -> fence_ref
{
    if (active_count_ < std::size(fences_))
        return fence_ref{handle(device_), fences_[active_count_++]};

    ++active_count_;
    return fence_ref{handle(device_), fences_.emplace_back(internal::create_fence(handle(device_)))};
}

auto fence_pool::reset() -> bool
{
    if (active_count_ == 0)
        return true;

    const auto result = vkResetFences(handle(device_), active_count_, std::data(fences_));
    active_count_ = 0;
    return result == VK_SUCCESS;
}

auto fence_pool::wait() const noexcept -> bool
{
    return wait(std::numeric_limits<std::uint64_t>::max());
}

auto fence_pool::wait(const std::chrono::nanoseconds time) const noexcept -> bool
{
    return wait(static_cast<std::uint64_t>(time.count()));
}

auto fence_pool::wait(const std::uint64_t nanosecond_time) const noexcept -> bool
{
    if (active_count_ == 0)
        return true;

    return vkWaitForFences(handle(device_), active_count_, std::data(fences_), true, nanosecond_time) == VK_SUCCESS;
}

} // namespace aeon::vulkan
