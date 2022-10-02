// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/sampler_create_info.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;

class sampler final
{
public:
    sampler() noexcept;
    explicit sampler(const device &device, const sampler_create_info &info = sampler_create_info{});
    ~sampler();

    sampler(const sampler &) = delete;
    auto operator=(const sampler &) -> sampler & = delete;

    sampler(sampler &&other) noexcept;
    auto operator=(sampler &&other) noexcept -> sampler &;

    [[nodiscard]] auto handle() const noexcept -> VkSampler;

private:
    void destroy() const noexcept;

    VkSampler handle_;
    VkDevice device_;
};

[[nodiscard]] inline auto handle(const sampler &s) noexcept
{
    return s.handle();
}

[[nodiscard]] inline auto handle(const sampler *s) noexcept
{
    return s->handle();
}

} // namespace aeon::vulkan
