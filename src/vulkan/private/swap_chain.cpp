// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/swap_chain.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/semaphore_ref.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/framebuffer.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/math/size3d.h>
#include <algorithm>
#include <limits>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto choose_swap_chain_surface_format(const std::vector<VkSurfaceFormatKHR> &surface_formats,
                                                    const VkSurfaceFormatKHR preferred_surface_format) noexcept
{
    for (const auto &surface_format : surface_formats)
    {
        if (surface_format.format == preferred_surface_format.format &&
            surface_format.colorSpace == preferred_surface_format.colorSpace)
        {
            return surface_format;
        }
    }

    return surface_formats[0];
}

[[nodiscard]] auto choose_swap_chain_present_mode(const std::vector<VkPresentModeKHR> &present_modes) noexcept
{
    // TODO: Allow for requesting a preferred present mode
    for (const auto &mode : present_modes)
    {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return mode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

[[nodiscard]] auto choose_swap_chain_present_mode(const physical_device &physical_device,
                                                  const surface &surface) noexcept
{
    const auto present_modes = physical_device.present_modes(surface);
    return choose_swap_chain_present_mode(present_modes);
}

[[nodiscard]] auto choose_swap_chain_extent(const VkSurfaceCapabilitiesKHR &capabilities,
                                            const math::size2d<std::uint32_t> preferred_extent)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
        return math::size2d<std::uint32_t>{capabilities.currentExtent.width, capabilities.currentExtent.height};

    auto actual_extent = preferred_extent;
    actual_extent.width =
        std::clamp(actual_extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actual_extent.height =
        std::clamp(actual_extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    return actual_extent;
}

[[nodiscard]] auto choose_swap_chain_extent(const physical_device &physical_device, const surface &surface,
                                            const math::size2d<std::uint32_t> preferred_extent)
{
    const auto capabilities = physical_device.surface_capabilities(surface);
    return choose_swap_chain_extent(capabilities, preferred_extent);
}

[[nodiscard]] auto create_swap_chain(const physical_device &physical_device, const device &device,
                                     const surface &surface, const VkSurfaceFormatKHR surface_format,
                                     const VkPresentModeKHR present_mode, const math::size2d<std::uint32_t> extent,
                                     const VkSwapchainKHR previous_swap_chain)
{
    const auto capabilities = physical_device.surface_capabilities(surface);

    auto image_count = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && image_count > capabilities.maxImageCount)
        image_count = capabilities.maxImageCount;

    VkSwapchainCreateInfoKHR create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = handle(surface);

    create_info.minImageCount = image_count;
    create_info.imageFormat = surface_format.format;
    create_info.imageColorSpace = surface_format.colorSpace;
    create_info.imageExtent.width = extent.width;
    create_info.imageExtent.height = extent.height;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage =
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

    const auto queue_indices = device.get_queue_indices();
    const auto queue_family_indices = queue_indices.get_swap_chain_queue_indices();

    if (queue_indices.has_dedicated_present_queue_index())
    {
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = static_cast<std::uint32_t>(std::size(queue_family_indices));
        create_info.pQueueFamilyIndices = std::data(queue_family_indices);
    }
    else
    {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    create_info.preTransform = capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;

    create_info.oldSwapchain = previous_swap_chain;

    VkSwapchainKHR swapchain;
    checked_result{vkCreateSwapchainKHR(handle(device), &create_info, nullptr, &swapchain)};
    return swapchain;
}

[[nodiscard]] auto get_swap_chain_images(const device &device, const VkSwapchainKHR swap_chain)
{
    std::uint32_t count = 0;
    std::vector<VkImage> swap_chain_images;
    vkGetSwapchainImagesKHR(handle(device), swap_chain, &count, nullptr);

    if (count == 0)
        throw vulkan_exception{"Swap chain has no images."};

    swap_chain_images.resize(count);
    vkGetSwapchainImagesKHR(handle(device), swap_chain, &count, std::data(swap_chain_images));

    return swap_chain_images;
}

[[nodiscard]] auto create_image_views(const std::vector<VkImage> &images, const device &device,
                                      const VkSurfaceFormatKHR &surface_format)
{
    std::vector<image_view> image_views;
    image_views.reserve(std::size(images));

    VkImageSubresourceRange layout{};
    layout.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    layout.baseMipLevel = 0;
    layout.levelCount = 1;
    layout.baseArrayLayer = 0;
    layout.layerCount = 1;

    for (const auto &image : images)
    {
        image_views.emplace_back(device, image, image_view_type::image_view_2d, surface_format.format, layout);
    }

    return image_views;
}

} // namespace internal

swap_chain::swap_chain() noexcept
    : device_{nullptr}
    , surface_{nullptr}
    , present_mode_{}
    , extent_{}
    , surface_format_{}
    , swapchain_{nullptr}
    , images_{}
    , image_views_{}
    , current_index_{0}
{
}

swap_chain::swap_chain(const vulkan::device &device, const surface &surface,
                       const VkSurfaceFormatKHR preferred_surface_format,
                       const math::size2d<std::uint32_t> preferred_extent)
    : device_{&device}
    , surface_{&surface}
    , present_mode_{internal::choose_swap_chain_present_mode(device.physical_device(), surface)}
    , extent_{internal::choose_swap_chain_extent(device.physical_device(), surface, preferred_extent)}
    , surface_format_{internal::choose_swap_chain_surface_format(device.physical_device().surface_formats(surface),
                                                                 preferred_surface_format)}
    , swapchain_{internal::create_swap_chain(device.physical_device(), device, surface, surface_format_, present_mode_,
                                             extent_, nullptr)}
    , images_{internal::get_swap_chain_images(device, swapchain_)}
    , image_views_{internal::create_image_views(images_, *device_, surface_format_)}
    , current_index_{0}
{
}

swap_chain::~swap_chain()
{
    destroy();
}

swap_chain::swap_chain(swap_chain &&other) noexcept
    : device_{other.device_}
    , surface_{other.surface_}
    , present_mode_{other.present_mode_}
    , extent_{other.extent_}
    , surface_format_{other.surface_format_}
    , swapchain_{other.swapchain_}
    , images_{std::move(other.images_)}
    , image_views_{std::move(other.image_views_)}
    , current_index_{other.current_index_}
{
    other.swapchain_ = nullptr;
}

auto swap_chain::operator=(swap_chain &&other) noexcept -> swap_chain &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        surface_ = other.surface_;
        present_mode_ = other.present_mode_;
        extent_ = other.extent_;
        surface_format_ = other.surface_format_;
        swapchain_ = other.swapchain_;
        images_ = std::move(other.images_);
        image_views_ = std::move(other.image_views_);
        current_index_ = other.current_index_;
        other.swapchain_ = nullptr;
    }

    return *this;
}

auto swap_chain::handle() const noexcept -> VkSwapchainKHR
{
    return swapchain_;
}

auto swap_chain::handle_ptr() const noexcept -> const VkSwapchainKHR *
{
    return &swapchain_;
}

auto swap_chain::format() const noexcept -> VkFormat
{
    return surface_format().format;
}

auto swap_chain::surface_format() const noexcept -> VkSurfaceFormatKHR
{
    return surface_format_;
}

auto swap_chain::image_count() const noexcept -> std::uint32_t
{
    return static_cast<std::uint32_t>(std::size(images_));
}

auto swap_chain::images() const noexcept -> const std::vector<VkImage> &
{
    return images_;
}

auto swap_chain::image_views() const -> const std::vector<image_view> &
{
    return image_views_;
}

auto swap_chain::extent() const noexcept -> math::size2d<std::uint32_t>
{
    return extent_;
}

auto swap_chain::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto swap_chain::acquire_next_image(const semaphore_ref &present_complete_semaphore) -> std::uint32_t
{
    return acquire_next_image(present_complete_semaphore, std::numeric_limits<std::uint64_t>::max());
}

auto swap_chain::acquire_next_image(const semaphore_ref &present_complete_semaphore,
                                    const std::chrono::nanoseconds timeout) -> std::uint32_t
{
    return acquire_next_image(present_complete_semaphore, static_cast<std::uint64_t>(timeout.count()));
}

auto swap_chain::acquire_next_image(const semaphore_ref &present_complete_semaphore, const std::uint64_t timeout)
    -> std::uint32_t
{
    checked_result{vkAcquireNextImageKHR(vulkan::handle(device_), swapchain_, timeout,
                                         vulkan::handle(present_complete_semaphore), nullptr, &current_index_)};
    return current_index_;
}

auto swap_chain::current_index() const noexcept -> std::uint32_t
{
    return current_index_;
}

void swap_chain::queue_present(const queue &queue, const semaphore_ref &render_complete_semaphore) const
{
    const auto info =
        initializers::present_info(swapchain_, current_index_, vulkan::handle_ptr(render_complete_semaphore));
    const auto result = vkQueuePresentKHR(vulkan::handle(queue), &info);

    if (!((result == VK_SUCCESS) || (result == VK_SUBOPTIMAL_KHR)))
        checked_result{result};
}

void swap_chain::destroy() const noexcept
{
    if (swapchain_)
        vkDestroySwapchainKHR(vulkan::handle(device_), swapchain_, nullptr);
}

auto create_swap_chain_framebuffers(const swap_chain &swap_chain, const render_pass &render_pass)
    -> std::vector<framebuffer>
{
    std::vector<framebuffer> framebuffers;
    framebuffers.reserve(swap_chain.image_count());

    const auto size = math::size3d<std::uint32_t>{swap_chain.extent(), 1};

    std::vector<image_view_ref> image_views(1);

    for (const auto &image_view : swap_chain.image_views())
    {
        image_views[0] = image_view;
        framebuffers.emplace_back(swap_chain.device(), image_views, render_pass, size);
    }

    return framebuffers;
}

auto create_swap_chain_framebuffers(const swap_chain &swap_chain, const render_pass &render_pass,
                                    const image_view_ref &depth_stencil) -> std::vector<framebuffer>
{
    std::vector<framebuffer> framebuffers;
    framebuffers.reserve(swap_chain.image_count());

    const auto size = math::size3d<std::uint32_t>{swap_chain.extent(), 1};

    std::vector<image_view_ref> image_views(2);
    image_views[1] = depth_stencil;

    for (const auto &image_view : swap_chain.image_views())
    {
        image_views[0] = image_view;
        framebuffers.emplace_back(swap_chain.device(), image_views, render_pass, size);
    }

    return framebuffers;
}

} // namespace aeon::vulkan
