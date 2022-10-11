// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <aeon/common/string.h>
#include <vector>
#include <functional>

namespace aeon::vulkan
{

class instance;

class debug
{
public:
    using debug_callback_type = void(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
                                     const VkDebugUtilsMessengerCallbackDataEXT *);

    debug() noexcept;
    explicit debug(const instance &instance, std::function<debug_callback_type> callback,
                   const common::flags<message_severity> severity = message_severity::all,
                   const common::flags<message_type> type = message_type::all);
    ~debug();

    debug(const debug &) noexcept = delete;
    auto operator=(const debug &) noexcept -> debug & = delete;

    debug(debug &&) noexcept = delete;
    auto operator=(debug &&) noexcept -> debug & = delete;

    static void append_required_extensions(std::vector<common::string> &extensions);
    static void append_required_layers(std::vector<common::string> &layers);

private:
    void destroy() const noexcept;

    static VKAPI_ATTR auto VKAPI_CALL vk_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                        VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
                                                        void *user_data) -> VkBool32;
    auto debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                        VkDebugUtilsMessageTypeFlagsEXT message_type,
                        const VkDebugUtilsMessengerCallbackDataEXT *callback_data) const noexcept -> bool;

    VkInstance instance_;
    VkDebugUtilsMessengerEXT messenger_;
    std::function<debug_callback_type> callback_;
};

} // namespace aeon::vulkan
