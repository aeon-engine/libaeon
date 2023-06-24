// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/image_view.h>
#include <aeon/vulkan/image.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_image_view(const device &device, const VkImage image, const image_view_type view_type,
                                     const VkFormat format, const VkComponentMapping components,
                                     const VkImageSubresourceRange subresource_range)
{
    const auto create_info =
        initializers::image_view_create_info(image, view_type, format, components, subresource_range);
    VkImageView image_view{};
    checked_result{vkCreateImageView(handle(device), &create_info, nullptr, &image_view)};
    return image_view;
}

} // namespace internal

image_view::image_view() noexcept
    : image_view_ref{}
{
}

image_view::image_view(const device &device, const image &image, const image_view_type view_type, const VkFormat format,
                       const VkImageSubresourceRange subresource_range, const VkComponentMapping components)
    : image_view{device, vulkan::handle(image), view_type, format, subresource_range, components}
{
}

image_view::image_view(const device &device, const VkImage image, const image_view_type view_type,
                       const VkFormat format, const VkImageSubresourceRange subresource_range,
                       const VkComponentMapping components)
    : image_view_ref{device,
                     internal::create_image_view(device, image, view_type, format, components, subresource_range)}
{
}

image_view::image_view(const device &device, const image &image, const image_view_type view_type, const format format,
                       const VkImageSubresourceRange subresource_range, const VkComponentMapping components)
    : image_view{device, vulkan::handle(image), view_type, format, subresource_range, components}
{
}

image_view::image_view(const device &device, const VkImage image, const image_view_type view_type, const format format,
                       const VkImageSubresourceRange subresource_range, const VkComponentMapping components)
    : image_view{device, image, view_type, static_cast<VkFormat>(format), subresource_range, components}
{
}

image_view::~image_view()
{
    destroy();
}

image_view::image_view(image_view &&other) noexcept
    : image_view_ref{other}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto image_view::operator=(image_view &&other) noexcept -> image_view &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;
        other.handle_ = VK_NULL_HANDLE;
    }

    return *this;
}

} // namespace aeon::vulkan
