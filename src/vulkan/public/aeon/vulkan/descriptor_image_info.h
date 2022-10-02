// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/sampler.h>
#include <aeon/vulkan/image_view.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class descriptor_image_info final : public VkDescriptorImageInfo
{
public:
    descriptor_image_info() noexcept;
    explicit descriptor_image_info(const vulkan::sampler &sampler, const image_view &image_view,
                                   const image_layout layout = image_layout::shader_read_only_optimal) noexcept;

    ~descriptor_image_info() = default;

    descriptor_image_info(const descriptor_image_info &) noexcept = default;
    auto operator=(const descriptor_image_info &) noexcept -> descriptor_image_info & = default;

    descriptor_image_info(descriptor_image_info &&) noexcept = default;
    auto operator=(descriptor_image_info &&) noexcept -> descriptor_image_info & = default;
};

inline descriptor_image_info::descriptor_image_info() noexcept
    : VkDescriptorImageInfo{nullptr, nullptr, VK_IMAGE_LAYOUT_UNDEFINED}
{
}

inline descriptor_image_info::descriptor_image_info(const vulkan::sampler &sampler, const image_view &image_view,
                                                    const image_layout layout) noexcept
    : VkDescriptorImageInfo{vulkan::handle(sampler), vulkan::handle(image_view), static_cast<VkImageLayout>(layout)}
{
}

static_assert(sizeof(descriptor_image_info) == sizeof(VkDescriptorImageInfo));

} // namespace aeon::vulkan
