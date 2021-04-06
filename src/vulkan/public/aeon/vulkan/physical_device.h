// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/extension.h>
#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/format.h>
#include <aeon/vulkan/exception.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <array>
#include <string_view>

namespace aeon::vulkan
{

class surface;

class physical_device final
{
public:
    physical_device() noexcept;
    explicit physical_device(const VkInstance instance, const VkPhysicalDevice handle);
    ~physical_device() = default;

    physical_device(const physical_device &) = default;
    auto operator=(const physical_device &) -> physical_device & = default;

    physical_device(physical_device &&) noexcept = default;
    auto operator=(physical_device &&) noexcept -> physical_device & = default;

    [[nodiscard]] auto handle() const noexcept -> VkPhysicalDevice;

    [[nodiscard]] auto instance_handle() const noexcept -> VkInstance;

    [[nodiscard]] auto properties() const noexcept -> VkPhysicalDeviceProperties;

    [[nodiscard]] auto memory_properties() const noexcept -> VkPhysicalDeviceMemoryProperties;

    [[nodiscard]] auto features() const noexcept -> VkPhysicalDeviceFeatures;

    [[nodiscard]] auto extensions() const -> std::vector<extension>;

    [[nodiscard]] auto surface_formats(const surface &surface) const -> std::vector<VkSurfaceFormatKHR>;
    [[nodiscard]] auto present_modes(const surface &surface) const -> std::vector<VkPresentModeKHR>;
    [[nodiscard]] auto surface_capabilities(const surface &surface) const -> VkSurfaceCapabilitiesKHR;

    [[nodiscard]] auto format_properties(const format format) const noexcept -> VkFormatProperties;
    [[nodiscard]] auto format_properties(const VkFormat format) const noexcept -> VkFormatProperties;

private:
    VkPhysicalDevice device_;
    VkInstance instance_;
};

[[nodiscard]] inline auto handle(const physical_device &device) noexcept
{
    return device.handle();
}

[[nodiscard]] inline auto type(const physical_device &device) noexcept
{
    return static_cast<physical_device_type>(device.properties().deviceType);
}

[[nodiscard]] inline auto name(const physical_device &device) -> std::string
{
    return device.properties().deviceName;
}

[[nodiscard]] inline auto is_integrated_gpu(const physical_device &device) noexcept -> bool
{
    return type(device) == physical_device_type::integrated_gpu;
}

[[nodiscard]] inline auto is_discrete_gpu(const physical_device &device) noexcept -> bool
{
    return type(device) == physical_device_type::discrete_gpu;
}

[[nodiscard]] inline auto is_virtual_gpu(const physical_device &device) noexcept -> bool
{
    return type(device) == physical_device_type::virtual_gpu;
}

[[nodiscard]] inline auto is_cpu(const physical_device &device) noexcept -> bool
{
    return type(device) == physical_device_type::cpu;
}

[[nodiscard]] inline auto extension_supported(const std::vector<extension> &extensions, const extension &ext) noexcept
    -> bool
{
    for (const auto &extension : extensions)
    {
        if (extension == ext)
            return true;
    }

    return false;
}

[[nodiscard]] inline auto extension_supported(const std::vector<extension> &extensions,
                                              const std::string &name) noexcept -> bool
{
    for (const auto &extension : extensions)
    {
        if (extension.name() == name)
            return true;
    }

    return false;
}

/*!
 * Find an appropriate heap for the given requirements. Modified from the Vulkan spec.
 * https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#memory-device
 */
[[nodiscard]] inline auto find_memory_type_index(const VkPhysicalDeviceMemoryProperties &properties,
                                                 const std::uint32_t required_memory_type_bits,
                                                 const common::flags<memory_flag> flags) noexcept -> std::int32_t
{
    const auto memory_count = properties.memoryTypeCount;

    for (auto i = 0u; i < memory_count; ++i)
    {
        const auto memory_type_bits = (1u << i);
        const auto is_required_memory_type = required_memory_type_bits & memory_type_bits;

        const auto property_flags = properties.memoryTypes[i].propertyFlags;
        const auto has_required_properties = (property_flags & flags) == flags;

        if (is_required_memory_type && has_required_properties)
            return static_cast<int32_t>(i);
    }

    return -1;
}

[[nodiscard]] inline auto find_memory_type_index(const VkPhysicalDeviceMemoryProperties &properties,
                                                 const VkMemoryRequirements &requirements,
                                                 const common::flags<memory_flag> flags) noexcept
{
    return find_memory_type_index(properties, requirements.memoryTypeBits, flags);
}

[[nodiscard]] inline auto find_optimal_memory_type_index(const VkPhysicalDeviceMemoryProperties &properties,
                                                         const std::uint32_t optimal_memory_type_bits,
                                                         const std::uint32_t required_memory_type_bits,
                                                         const common::flags<memory_flag> flags) noexcept
{
    const auto result = find_memory_type_index(properties, optimal_memory_type_bits, flags);

    if (result == -1)
        return find_memory_type_index(properties, required_memory_type_bits, flags);

    return result;
}

[[nodiscard]] inline auto find_optimal_memory_type_index(const VkPhysicalDeviceMemoryProperties &properties,
                                                         const VkMemoryRequirements &optimal_requirements,
                                                         const VkMemoryRequirements &requirements,
                                                         const common::flags<memory_flag> flags) noexcept
{
    return find_optimal_memory_type_index(properties, optimal_requirements.memoryTypeBits, requirements.memoryTypeBits,
                                          flags);
}

/*!
 * Attempt to score the physical device for graphics rendering to a surface. The physical device with the highest score
 * is considered most suitable for 3D rendering. If 0 is returned, the device is considered not suitable at all.
 */
[[nodiscard]] inline auto score_for_gfx(const physical_device &device, const surface &surface) -> std::uint32_t
{
    if (!device.features().geometryShader)
        return 0;

    const auto extensions = device.extensions();

    if (!extension_supported(extensions, VK_KHR_SWAPCHAIN_EXTENSION_NAME))
        return 0;

    const auto formats = device.surface_formats(surface);
    const auto modes = device.present_modes(surface);

    if (std::empty(formats) || std::empty(modes))
        return 0;

    auto score = 0u;

    if (is_discrete_gpu(device))
        score += 1000;

    score += device.properties().limits.maxImageDimension2D;

    const auto capabilities = device.surface_capabilities(surface);
    score += capabilities.maxImageCount;

    return score;
}

[[nodiscard]] inline auto find_depth_stencil_format(const physical_device &device)
{
    std::array depth_formats = {format::d32_sfloat_s8_uint, format::d32_sfloat, format::d24_unorm_s8_uint,
                                format::d16_unorm_s8_uint, format::d16_unorm};

    for (auto &format : depth_formats)
    {
        const auto properties = device.format_properties(format);

        if (properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
            return format;
    }

    throw vulkan_exception{"Physical device does not seem to have a suitable depth format"};
}

} // namespace aeon::vulkan
