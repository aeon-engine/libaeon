// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/fence_ref.h>
#include <aeon/vulkan/enums.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_fence(const VkDevice device) -> VkFence;

} // namespace internal

class device;

class fence final : public fence_ref
{
public:
    fence() noexcept;
    explicit fence(const device &dev, const fence_create_state create_state = fence_create_state::unsignaled);
    explicit fence(const VkDevice device, const fence_create_state create_state = fence_create_state::unsignaled);
    explicit fence(const VkDevice device, const VkFence handle);
    ~fence() noexcept;

    fence(const fence &) noexcept = delete;
    auto operator=(const fence &) noexcept -> fence & = delete;

    fence(fence &&other) noexcept;
    auto operator=(fence &&other) noexcept -> fence &;
};

} // namespace aeon::vulkan
