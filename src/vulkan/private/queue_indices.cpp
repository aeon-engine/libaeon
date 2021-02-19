// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/queue_indices.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/exception.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto get_physical_device_queue_family_properties(const physical_device &device)
{
    std::uint32_t count = 0;
    std::vector<VkQueueFamilyProperties> queue_family_properties;
    vkGetPhysicalDeviceQueueFamilyProperties(handle(device), &count, nullptr);

    if (count == 0)
        throw vulkan_exception{"Selected physical device has no queue families."};

    queue_family_properties.resize(count);
    vkGetPhysicalDeviceQueueFamilyProperties(handle(device), &count, std::data(queue_family_properties));
    return queue_family_properties;
}

[[nodiscard]] auto get_physical_device_surface_support(const physical_device &device, const surface &surface,
                                                       const uint32_t queue_index) -> bool
{
    VkBool32 present_support = false;
    checked_result{
        vkGetPhysicalDeviceSurfaceSupportKHR(handle(device), queue_index, handle(surface), &present_support)};
    return present_support;
}

[[nodiscard]] auto get_queue_family_present_support(const physical_device &device, const surface &surface,
                                                    const std::vector<VkQueueFamilyProperties> &families)
{
    const auto family_count = std::size(families);
    std::vector<VkBool32> present_support(family_count);

    for (auto i = 0u; i < family_count; ++i)
    {
        present_support[i] = get_physical_device_surface_support(device, surface, i);
    }

    return present_support;
}

} // namespace internal

queue_indices::queue_indices(const physical_device &device, const surface &surface)
    : queue_indices{}
{
    const auto queue_families = internal::get_physical_device_queue_family_properties(device);
    const auto present_support = internal::get_queue_family_present_support(device, surface, queue_families);

    // Find a queue that supports both graphics and present.
    for (auto i = 0u; i < std::size(queue_families); ++i)
    {
        if ((queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
        {
            if (!has_graphics_queue_index())
                set_graphics_queue_index(i);

            if (present_support[i] == VK_TRUE)
            {
                set_graphics_queue_index(i);
                set_present_queue_index(i);
                break;
            }
        }

        // Try to find a dedicated transfer queue
        if (((queue_families[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) &&
            ((queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) &&
            ((queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0))
        {
            set_transfer_queue_index(i);
        }
    }

    // If there isn't a queue that supports both, use a seperate present queue
    if (!has_present_queue_index())
    {
        // If didn't find a queue that supports both graphics and present, then
        // find a separate present queue.
        for (auto i = 0u; i < std::size(queue_families); ++i)
        {
            if (present_support[i] == VK_TRUE)
            {
                set_present_queue_index(i);
                break;
            }
        }
    }

    if (!has_graphics_queue_index() || !has_present_queue_index())
        throw vulkan_exception{"Selected physical device has no usable queue families."};
}

auto queue_indices::get_queue_create_info_collection(float &priority) const -> std::vector<VkDeviceQueueCreateInfo>
{
    std::vector<VkDeviceQueueCreateInfo> infos;

    if (!has_dedicated_present_queue_index())
    {
        if (has_graphics_queue_index())
            infos.push_back(initializers::device_queue_create_info(graphics_queue_index(), priority));
    }
    else
    {
        if (has_graphics_queue_index())
            infos.push_back(initializers::device_queue_create_info(graphics_queue_index(), priority));

        if (has_present_queue_index())
            infos.push_back(initializers::device_queue_create_info(present_queue_index(), priority));
    }

    if (has_dedicated_transfer_queue_index())
        infos.push_back(initializers::device_queue_create_info(transfer_queue_index(), priority));

    return infos;
}

auto queue_indices::get_swap_chain_queue_indices() const -> std::vector<std::uint32_t>
{
    std::vector<std::uint32_t> indices;

    indices.push_back(graphics_queue_index());

    if (has_dedicated_present_queue_index())
        indices.push_back(present_queue_index());

    return indices;
}

} // namespace aeon::vulkan
