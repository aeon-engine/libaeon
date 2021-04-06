// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/format.h>
#include <aeon/vulkan/version.h>
#include <aeon/vulkan/config.h>
#include <aeon/common/flags.h>
#include <vulkan/vulkan_core.h>
#include <cstdint>
#include <string_view>
#include <vector>

namespace aeon::vulkan::initializers
{

[[nodiscard]] inline auto application_info(const char8_t *application_name,
                                           const common::version3<uint32_t> application_version,
                                           const char8_t *engine_name,
                                           const common::version3<uint32_t> engine_version) noexcept
{
    VkApplicationInfo info{};
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = reinterpret_cast<const char *>(application_name);
    info.applicationVersion = version::to_vulkan(application_version);
    info.pEngineName = reinterpret_cast<const char *>(engine_name);
    info.engineVersion = version::to_vulkan(engine_version);
    info.apiVersion = AEON_VULKAN_API_VERSION;
    return info;
}

[[nodiscard]] inline auto application_info(const std::u8string_view application_name,
                                           const common::version3<uint32_t> application_version,
                                           const std::u8string_view engine_name,
                                           const common::version3<uint32_t> engine_version) noexcept
{
    return application_info(std::data(application_name), application_version, std::data(engine_name), engine_version);
}

[[nodiscard]] inline auto instance_create_info(const VkApplicationInfo &application_info,
                                               const std::vector<const char *> &enabled_extensions,
                                               const std::vector<const char *> &enabled_layers) noexcept
{
    VkInstanceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &application_info;

    if (!std::empty(enabled_extensions))
    {
        info.enabledExtensionCount = static_cast<std::uint32_t>(std::size(enabled_extensions));
        info.ppEnabledExtensionNames = std::data(enabled_extensions);
    }

    if (!std::empty(enabled_layers))
    {
        info.enabledLayerCount = static_cast<std::uint32_t>(std::size(enabled_layers));
        info.ppEnabledLayerNames = std::data(enabled_layers);
    }

    return info;
}

[[nodiscard]] inline auto command_pool_create_info(const std::uint32_t queue_family_index,
                                                   const common::flags<command_pool_create_flag> flags = {}) noexcept
{
    VkCommandPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info.queueFamilyIndex = queue_family_index;
    info.flags = flags;
    return info;
}

[[nodiscard]] inline auto command_buffer_create_info(const VkCommandPool pool, const command_buffer_level level,
                                                     const std::uint32_t count = 1)
{
    VkCommandBufferAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info.commandPool = pool;
    info.level = static_cast<VkCommandBufferLevel>(level);
    info.commandBufferCount = count;
    return info;
}

[[nodiscard]] inline auto command_buffer_begin_info(const common::flags<command_buffer_usage_flag> flags)
{
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags = flags;
    return info;
}

[[nodiscard]] inline auto debug_utils_messenger_create_info(const common::flags<message_severity> message_severity,
                                                            const common::flags<message_type> message_type,
                                                            const PFN_vkDebugUtilsMessengerCallbackEXT callback,
                                                            void *user_data) noexcept
{
    VkDebugUtilsMessengerCreateInfoEXT info{};
    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.messageSeverity = static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(message_severity);
    info.messageType = static_cast<VkDebugUtilsMessageTypeFlagsEXT>(message_type);
    info.pfnUserCallback = callback;
    info.pUserData = user_data;
    return info;
}

[[nodiscard]] inline auto memory_allocate_info(const VkDeviceSize size, const std::uint32_t type_index) noexcept
{
    VkMemoryAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.pNext = nullptr;

    info.allocationSize = size;
    info.memoryTypeIndex = type_index;

    return info;
}

[[nodiscard]] inline auto device_create_info(const std::vector<const char *> &enabled_layers,
                                             const std::vector<const char *> &required_extensions,
                                             const std::vector<VkDeviceQueueCreateInfo> &queue_create_info_collection,
                                             const VkPhysicalDeviceFeatures &required_features) noexcept
{
    VkDeviceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;

    if (!std::empty(queue_create_info_collection))
    {
        info.queueCreateInfoCount = static_cast<std::uint32_t>(std::size(queue_create_info_collection));
        info.pQueueCreateInfos = std::data(queue_create_info_collection);
    }

    if (!std::empty(enabled_layers))
    {
        info.enabledLayerCount = static_cast<std::uint32_t>(std::size(enabled_layers));
        info.ppEnabledLayerNames = std::data(enabled_layers);
    }

    if (!std::empty(required_extensions))
    {
        info.enabledExtensionCount = static_cast<std::uint32_t>(std::size(required_extensions));
        info.ppEnabledExtensionNames = std::data(required_extensions);
    }

    info.pEnabledFeatures = &required_features;

    return info;
}

[[nodiscard]] inline auto device_queue_create_info(const std::uint32_t queue_family_index, float &priority) noexcept
{
    VkDeviceQueueCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;

    info.queueFamilyIndex = queue_family_index;
    info.queueCount = 1;
    info.pQueuePriorities = &priority;

    return info;
}

[[nodiscard]] inline auto fence_create_info(const fence_create_state state) noexcept
{
    VkFenceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = static_cast<VkFenceCreateFlags>(state);
    return info;
}

[[nodiscard]] inline auto semaphore_create_info() noexcept
{
    VkSemaphoreCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    return info;
}

[[nodiscard]] inline auto submit_info(const VkSemaphore *wait_semaphore_handle, const VkCommandBuffer *command_buffer,
                                      const VkSemaphore *signal_semaphore_handle,
                                      const VkPipelineStageFlags &stage_flags) noexcept
{
    VkSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.pNext = nullptr;

    if (wait_semaphore_handle)
    {
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = wait_semaphore_handle;
    }

    info.pWaitDstStageMask = &stage_flags;

    if (command_buffer)
    {
        info.commandBufferCount = 1;
        info.pCommandBuffers = command_buffer;
    }

    if (signal_semaphore_handle)
    {
        info.signalSemaphoreCount = 1;
        info.pSignalSemaphores = signal_semaphore_handle;
    }

    return info;
}

[[nodiscard]] inline auto submit_info(const VkCommandBuffer *command_buffer,
                                      const VkPipelineStageFlags &stage_flags) noexcept
{
    return submit_info(nullptr, command_buffer, nullptr, stage_flags);
}

[[nodiscard]] inline auto image_view_create_info(const VkImage image, const image_view_type view_type,
                                                 const VkFormat format, const VkComponentMapping components,
                                                 const VkImageSubresourceRange subresource_range) noexcept
{
    VkImageViewCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info.image = image;
    info.viewType = static_cast<VkImageViewType>(view_type);
    info.format = format;
    info.components = components;
    info.subresourceRange = subresource_range;
    return info;
}

[[nodiscard]] inline auto image_view_create_info(const VkImage image, const image_view_type view_type,
                                                 const format format, const VkComponentMapping components,
                                                 const VkImageSubresourceRange subresource_range) noexcept
{
    return image_view_create_info(image, view_type, static_cast<VkFormat>(format), components, subresource_range);
}

[[nodiscard]] inline auto image_create_info(const image_type type, const VkExtent3D extent, const VkFormat format,
                                            const std::uint32_t mip_levels, const std::uint32_t array_layers,
                                            const sample_count samples, const image_tiling tiling,
                                            const common::flags<image_usage_flag> usage,
                                            const common::flags<image_create_flag> flags)
{
    VkImageCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.flags = flags;
    info.imageType = static_cast<VkImageType>(type);
    info.format = static_cast<VkFormat>(format);
    info.extent = extent;
    info.mipLevels = mip_levels;
    info.arrayLayers = array_layers;
    info.samples = static_cast<VkSampleCountFlagBits>(samples);
    info.tiling = static_cast<VkImageTiling>(tiling);
    info.usage = usage;
    return info;
}

[[nodiscard]] inline auto present_info(const VkSwapchainKHR &swap_chain, const std::uint32_t &image_index,
                                       const VkSemaphore *wait_semaphore_handle)
{
    VkPresentInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.swapchainCount = 1;
    info.pSwapchains = &swap_chain;
    info.pImageIndices = &image_index;

    if (wait_semaphore_handle)
    {
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = wait_semaphore_handle;
    }
    return info;
}

[[nodiscard]] inline auto shader_module_create_info(const std::vector<std::byte> &data) noexcept
{
    VkShaderModuleCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info.codeSize = std::size(data);
    info.pCode = reinterpret_cast<const uint32_t *>(std::data(data));
    return info;
}

} // namespace aeon::vulkan::initializers
