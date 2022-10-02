// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/semaphore_ref.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_semaphore(const VkDevice device) -> VkSemaphore;

} // namespace internal

class device;

class semaphore final : public semaphore_ref
{
public:
    semaphore() noexcept;
    explicit semaphore(const device &dev);
    explicit semaphore(const VkDevice device);
    explicit semaphore(const VkDevice device, const VkSemaphore handle);
    ~semaphore() noexcept;

    semaphore(const semaphore &) noexcept = delete;
    auto operator=(const semaphore &) noexcept -> semaphore & = delete;

    semaphore(semaphore &&other) noexcept;
    auto operator=(semaphore &&other) noexcept -> semaphore &;
};

} // namespace aeon::vulkan
