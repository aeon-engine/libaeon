// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;

class descriptor_set_layout_ref
{
public:
    descriptor_set_layout_ref() noexcept;
    explicit descriptor_set_layout_ref(const device &device, const VkDescriptorSetLayout handle) noexcept;
    ~descriptor_set_layout_ref() = default;

    descriptor_set_layout_ref(const descriptor_set_layout_ref &) noexcept = default;
    auto operator=(const descriptor_set_layout_ref &) noexcept -> descriptor_set_layout_ref & = default;

    descriptor_set_layout_ref(descriptor_set_layout_ref &&) noexcept = default;
    auto operator=(descriptor_set_layout_ref &&) noexcept -> descriptor_set_layout_ref & = default;

    [[nodiscard]] auto handle() const noexcept -> VkDescriptorSetLayout;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkDescriptorSetLayout *;

    void destroy() noexcept;

protected:
    const device *device_;
    VkDescriptorSetLayout handle_;
};

[[nodiscard]] inline auto handle(const descriptor_set_layout_ref &d) noexcept
{
    return d.handle();
}

[[nodiscard]] inline auto handle_ptr(const descriptor_set_layout_ref &d) noexcept
{
    return d.handle_ptr();
}

} // namespace aeon::vulkan
