// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/semaphore_ref.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <cstdint>

namespace aeon::vulkan
{

class device;

class semaphore_pool final
{
public:
    explicit semaphore_pool(const device &dev);
    explicit semaphore_pool(const device &dev, const std::uint64_t pre_allocate);
    ~semaphore_pool() noexcept;

    semaphore_pool(const semaphore_pool &) noexcept = delete;
    auto operator=(const semaphore_pool &) noexcept -> semaphore_pool & = delete;

    semaphore_pool(semaphore_pool &&other) noexcept = delete;
    auto operator=(semaphore_pool &&other) noexcept -> semaphore_pool & = delete;

    void reserve(const std::uint64_t size);
    [[nodiscard]] auto request() -> semaphore_ref;
    void reset() noexcept;

private:
    const device &device_;
    std::vector<VkSemaphore> semaphores_;
    std::uint32_t active_count_;
};

} // namespace aeon::vulkan
