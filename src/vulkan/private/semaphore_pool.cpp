// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/semaphore_pool.h>
#include <aeon/vulkan/semaphore.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

semaphore_pool::semaphore_pool(const device &dev)
    : device_{dev}
    , semaphores_{}
    , active_count_{0}
{
}

semaphore_pool::semaphore_pool(const device &dev, const std::uint64_t pre_allocate)
    : device_{dev}
    , semaphores_{}
    , active_count_{0}
{
    semaphores_.reserve(pre_allocate);
    for (auto i = 0ull; i < pre_allocate; ++i)
    {
        semaphores_.push_back(internal::create_semaphore(handle(device_)));
    }
}

semaphore_pool::~semaphore_pool() noexcept
{
    reset();

    for (const auto semaphore : semaphores_)
    {
        semaphore_ref{handle(device_), semaphore}.destroy();
    }
}

void semaphore_pool::reserve(const std::uint64_t size)
{
    semaphores_.reserve(size);
}

auto semaphore_pool::request() -> semaphore_ref
{
    if (active_count_ < std::size(semaphores_))
        return semaphore_ref{handle(device_), semaphores_[active_count_++]};

    ++active_count_;
    return semaphore_ref{handle(device_), semaphores_.emplace_back(internal::create_semaphore(handle(device_)))};
}

void semaphore_pool::reset() noexcept
{
    active_count_ = 0;
}

} // namespace aeon::vulkan
