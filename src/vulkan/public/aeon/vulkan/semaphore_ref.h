// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class semaphore_ref
{
public:
    semaphore_ref() noexcept;
    explicit semaphore_ref(const VkDevice device, const VkSemaphore handle) noexcept;
    ~semaphore_ref() noexcept = default;

    semaphore_ref(const semaphore_ref &) noexcept = default;
    auto operator=(const semaphore_ref &) noexcept -> semaphore_ref & = default;

    semaphore_ref(semaphore_ref &&) noexcept = default;
    auto operator=(semaphore_ref &&) noexcept -> semaphore_ref & = default;

    [[nodiscard]] auto handle() const noexcept -> VkSemaphore;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkSemaphore *;

    void destroy() noexcept;

protected:
    VkDevice device_;
    VkSemaphore handle_;
};

[[nodiscard]] inline auto handle(const semaphore_ref &s) noexcept
{
    return s.handle();
}

[[nodiscard]] inline auto handle_ptr(const semaphore_ref &s) noexcept
{
    return s.handle_ptr();
}

} // namespace aeon::vulkan
