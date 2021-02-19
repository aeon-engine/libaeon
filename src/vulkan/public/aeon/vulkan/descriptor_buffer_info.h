// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/buffer.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class descriptor_buffer_info final : public VkDescriptorBufferInfo
{
public:
    descriptor_buffer_info() noexcept;
    explicit descriptor_buffer_info(const vulkan::buffer &buffer, const VkDeviceSize size) noexcept;
    explicit descriptor_buffer_info(const vulkan::buffer &buffer, const VkDeviceSize offset,
                                    const VkDeviceSize size) noexcept;

    explicit descriptor_buffer_info(const VkBuffer buffer, const VkDeviceSize size) noexcept;
    explicit descriptor_buffer_info(const VkBuffer buffer, const VkDeviceSize offset, const VkDeviceSize size) noexcept;

    ~descriptor_buffer_info() = default;

    descriptor_buffer_info(const descriptor_buffer_info &) noexcept = default;
    auto operator=(const descriptor_buffer_info &) noexcept -> descriptor_buffer_info & = default;

    descriptor_buffer_info(descriptor_buffer_info &&) noexcept = default;
    auto operator=(descriptor_buffer_info &&) noexcept -> descriptor_buffer_info & = default;
};

inline descriptor_buffer_info::descriptor_buffer_info() noexcept
    : descriptor_buffer_info{nullptr, 0, 0}
{
}

inline descriptor_buffer_info::descriptor_buffer_info(const vulkan::buffer &buffer, const VkDeviceSize size) noexcept
    : descriptor_buffer_info{buffer, 0, size}
{
}

inline descriptor_buffer_info::descriptor_buffer_info(const vulkan::buffer &buffer, const VkDeviceSize offset,
                                                      const VkDeviceSize size) noexcept
    : descriptor_buffer_info{handle(buffer), offset, size}
{
}

inline descriptor_buffer_info::descriptor_buffer_info(const VkBuffer buffer, const VkDeviceSize size) noexcept
    : descriptor_buffer_info{buffer, 0, size}
{
}

inline descriptor_buffer_info::descriptor_buffer_info(const VkBuffer buffer, const VkDeviceSize offset,
                                                      const VkDeviceSize size) noexcept
    : VkDescriptorBufferInfo{buffer, offset, size}
{
}

static_assert(sizeof(descriptor_buffer_info) == sizeof(VkDescriptorBufferInfo));

} // namespace aeon::vulkan
