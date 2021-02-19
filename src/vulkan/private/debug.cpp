// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/debug.h>
#include <aeon/vulkan/instance.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/initializers.h>
#include <iostream>

namespace aeon::vulkan
{

namespace internal
{

static auto create_debug_utils_messenger(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *create_info,
                                         const VkAllocationCallbacks *allocator, VkDebugUtilsMessengerEXT *messenger)
    -> VkResult
{
    const auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));

    if (func == nullptr)
        throw std::runtime_error("Could not find vkCreateDebugUtilsMessengerEXT. Extension not available.");

    return func(instance, create_info, allocator, messenger);
}

void destroy_debug_utils_messenger(VkInstance instance, VkDebugUtilsMessengerEXT callback,
                                   const VkAllocationCallbacks *allocator) noexcept
{
    const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

    if (func != nullptr)
        func(instance, callback, allocator);
}

} // namespace internal

debug::debug() noexcept
    : instance_{nullptr}
    , messenger_{nullptr}
{
}

debug::debug(const instance &instance, std::function<debug_callback_type> callback,
             const common::flags<message_severity> severity, const common::flags<message_type> type)
    : instance_{instance.handle()}
    , messenger_{nullptr}
    , callback_{std::move(callback)}
{
    const auto debug_messenger_info =
        initializers::debug_utils_messenger_create_info(severity, type, debug::vk_debug_callback, this);
    checked_result{internal::create_debug_utils_messenger(instance_, &debug_messenger_info, nullptr, &messenger_)};
}

debug::~debug()
{
    destroy();
}

void debug::append_required_extensions(std::vector<std::string> &extensions)
{
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}

void debug::append_required_layers(std::vector<std::string> &layers)
{
    layers.emplace_back("VK_LAYER_KHRONOS_validation");
    // layers.emplace_back("VK_LAYER_LUNARG_api_dump");
}

void debug::destroy() const noexcept
{
    if (instance_ && messenger_)
        internal::destroy_debug_utils_messenger(instance_, messenger_, nullptr);
}

auto debug::debug_callback([[maybe_unused]] VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                           [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT message_type,
                           const VkDebugUtilsMessengerCallbackDataEXT *callback_data) const noexcept -> bool
{
    callback_(message_severity, message_type, callback_data);
    return false;
}

VKAPI_ATTR auto VKAPI_CALL debug::vk_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                    VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                    const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
                                                    void *user_data) -> VkBool32
{
    const auto instance = static_cast<debug *>(user_data);
    return instance->debug_callback(message_severity, message_type, callback_data) ? VK_TRUE : VK_FALSE;
}

} // namespace aeon::vulkan
