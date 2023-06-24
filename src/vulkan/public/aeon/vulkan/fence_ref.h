// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>
#include <chrono>
#include <cstdint>

namespace aeon::vulkan
{

class fence_ref
{
public:
    fence_ref() noexcept;
    explicit fence_ref(const VkDevice device, const VkFence handle);
    ~fence_ref() noexcept = default;

    fence_ref(const fence_ref &) noexcept = default;
    auto operator=(const fence_ref &) noexcept -> fence_ref & = default;

    fence_ref(fence_ref &&) noexcept = default;
    auto operator=(fence_ref &&) noexcept -> fence_ref & = default;

    [[nodiscard]] auto handle() const noexcept -> VkFence;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkFence *;

    void wait() const;
    void wait(const std::chrono::nanoseconds time) const;
    void wait(const std::uint64_t nanosecond_time) const;

    auto wait_result() const noexcept -> VkResult;
    auto wait_result(const std::chrono::nanoseconds time) const noexcept -> VkResult;
    auto wait_result(const std::uint64_t nanosecond_time) const noexcept -> VkResult;

    [[nodiscard]] auto is_signaled() const noexcept -> bool;

    void reset() const;

    [[nodiscard]] auto reset_sync() const -> bool;

    void destroy() noexcept;

protected:
    VkDevice device_;
    VkFence handle_;
};

[[nodiscard]] inline auto handle(const fence_ref &f) noexcept
{
    return f.handle();
}

[[nodiscard]] inline auto handle_ptr(const fence_ref &f) noexcept
{
    return f.handle_ptr();
}

} // namespace aeon::vulkan
