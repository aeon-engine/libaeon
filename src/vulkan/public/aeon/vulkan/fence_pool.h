// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/fence_ref.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <chrono>
#include <cstdint>

namespace aeon::vulkan
{

class device;

class fence_pool final
{
public:
    explicit fence_pool(const device &dev);
    explicit fence_pool(const device &dev, const std::uint64_t pre_allocate);
    ~fence_pool() noexcept;

    fence_pool(const fence_pool &) noexcept = delete;
    auto operator=(const fence_pool &) noexcept -> fence_pool & = delete;

    fence_pool(fence_pool &&other) noexcept = delete;
    auto operator=(fence_pool &&other) noexcept -> fence_pool & = delete;

    void reserve(const std::uint64_t size);
    [[nodiscard]] auto request() -> fence_ref;
    auto reset() -> bool;

    auto wait() const noexcept -> bool;
    auto wait(const std::chrono::nanoseconds time) const noexcept -> bool;
    auto wait(const std::uint64_t nanosecond_time) const noexcept -> bool;

private:
    const device &device_;
    std::vector<VkFence> fences_;
    std::uint32_t active_count_;
};

} // namespace aeon::vulkan
