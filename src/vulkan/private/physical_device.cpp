// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/common/container.h>
#include <aeon/common/assert.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto get_physical_device_properties(const VkPhysicalDevice handle) noexcept
{
    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(handle, &properties);
    return properties;
}

[[nodiscard]] auto get_physical_device_memory_properties(const VkPhysicalDevice handle) noexcept
{
    VkPhysicalDeviceMemoryProperties properties{};
    vkGetPhysicalDeviceMemoryProperties(handle, &properties);
    return properties;
}

[[nodiscard]] auto get_physical_device_features(const VkPhysicalDevice handle) noexcept
{
    VkPhysicalDeviceFeatures features{};
    vkGetPhysicalDeviceFeatures(handle, &features);
    return features;
}

[[nodiscard]] auto get_physical_device_features2(const VkPhysicalDevice handle) noexcept
{
    VkPhysicalDeviceFeatures2 features{};
    vkGetPhysicalDeviceFeatures2(handle, &features);
    return features;
}

[[nodiscard]] auto enumerate_device_extension_properties(const VkPhysicalDevice handle)
{
    std::uint32_t count = 0;
    checked_result{vkEnumerateDeviceExtensionProperties(handle, nullptr, &count, nullptr)};
    std::vector<VkExtensionProperties> extension_properties(count);
    checked_result{vkEnumerateDeviceExtensionProperties(handle, nullptr, &count, std::data(extension_properties))};
    return extension_properties;
}

[[nodiscard]] auto find_heap_index(const VkPhysicalDeviceMemoryProperties &properties) noexcept -> std::uint32_t
{
    for (auto i = 0u; i < properties.memoryHeapCount; ++i)
    {
        if (properties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
            return i;
    }

    aeon_assert_fail("Device has no heap?");
    return 0;
}

[[nodiscard]] auto get_physical_device_surface_formats(const VkPhysicalDevice device, const VkSurfaceKHR surface)
{
    std::uint32_t count;
    checked_result{vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, nullptr)};

    std::vector<VkSurfaceFormatKHR> formats(count);

    if (count > 0)
        checked_result{vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, std::data(formats))};

    return formats;
}

[[nodiscard]] auto get_physical_device_surface_present_modes(const VkPhysicalDevice device, const VkSurfaceKHR surface)
{
    std::uint32_t count;
    checked_result{vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, nullptr)};

    std::vector<VkPresentModeKHR> present_modes(count);

    if (count > 0)
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, std::data(present_modes));

    return present_modes;
}

} // namespace internal

physical_device::physical_device() noexcept
    : device_{nullptr}
    , instance_{nullptr}
{
}

physical_device::physical_device(const VkInstance instance, const VkPhysicalDevice handle)
    : device_{handle}
    , instance_{instance}
{
}

auto physical_device::handle() const noexcept -> VkPhysicalDevice
{
    return device_;
}

auto physical_device::instance_handle() const noexcept -> VkInstance
{
    return instance_;
}

auto physical_device::properties() const noexcept -> VkPhysicalDeviceProperties
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_properties(device_);
}

auto physical_device::memory_properties() const noexcept -> VkPhysicalDeviceMemoryProperties
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_memory_properties(device_);
}

auto physical_device::features() const noexcept -> VkPhysicalDeviceFeatures
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_features(device_);
}

auto physical_device::features2() const noexcept -> VkPhysicalDeviceFeatures2
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_features2(device_);
}

auto physical_device::extensions() const -> std::vector<extension>
{
    aeon_assert(device_, "Device is null.");
    return common::container::auto_transform<extension>(internal::enumerate_device_extension_properties(device_));
}

auto physical_device::surface_formats(const surface &surface) const -> std::vector<VkSurfaceFormatKHR>
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_surface_formats(device_, vulkan::handle(surface));
}

auto physical_device::present_modes(const surface &surface) const -> std::vector<VkPresentModeKHR>
{
    aeon_assert(device_, "Device is null.");
    return internal::get_physical_device_surface_present_modes(device_, vulkan::handle(surface));
}

auto physical_device::surface_capabilities(const surface &surface) const -> VkSurfaceCapabilitiesKHR
{
    aeon_assert(device_, "Device is null.");
    VkSurfaceCapabilitiesKHR capabilities;
    checked_result{vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device_, vulkan::handle(surface), &capabilities)};
    return capabilities;
}

auto physical_device::format_properties(const format format) const noexcept -> VkFormatProperties
{
    return format_properties(static_cast<VkFormat>(format));
}

auto physical_device::format_properties(const VkFormat format) const noexcept -> VkFormatProperties
{
    VkFormatProperties properties;
    vkGetPhysicalDeviceFormatProperties(device_, format, &properties);
    return properties;
}

} // namespace aeon::vulkan
