// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/image_view_ref.h>
#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/format.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class image;
class device;

static constexpr auto default_component_mapping =
    VkComponentMapping{VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                       VK_COMPONENT_SWIZZLE_IDENTITY};

class image_view final : public image_view_ref
{
public:
    image_view() noexcept;
    explicit image_view(const device &device, const image &image, const image_view_type view_type,
                        const VkFormat format, const VkImageSubresourceRange subresource_range,
                        const VkComponentMapping components = default_component_mapping);
    explicit image_view(const device &device, const VkImage image, const image_view_type view_type,
                        const VkFormat format, const VkImageSubresourceRange subresource_range,
                        const VkComponentMapping components = default_component_mapping);
    explicit image_view(const device &device, const image &image, const image_view_type view_type, const format format,
                        const VkImageSubresourceRange subresource_range,
                        const VkComponentMapping components = default_component_mapping);
    explicit image_view(const device &device, const VkImage image, const image_view_type view_type, const format format,
                        const VkImageSubresourceRange subresource_range,
                        const VkComponentMapping components = default_component_mapping);
    ~image_view();

    image_view(const image_view &) = delete;
    auto operator=(const image_view &) -> image_view & = delete;

    image_view(image_view &&other) noexcept;
    auto operator=(image_view &&other) noexcept -> image_view &;
};

} // namespace aeon::vulkan
