// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/config.h>
#include <aeon/vulkan/exception.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

[[nodiscard]] inline auto result_to_string(const VkResult result) noexcept
{
    switch (result)
    {
        case VK_SUCCESS:
            return "Success";
        case VK_NOT_READY:
            return "Not ready";
        case VK_TIMEOUT:
            return "Timeout";
        case VK_EVENT_SET:
            return "Event set";
        case VK_EVENT_RESET:
            return "Event reset";
        case VK_INCOMPLETE:
            return "Incomplete";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "Error: Out of host memory";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "Error: Out of device memory";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "Error: Initialization failed";
        case VK_ERROR_DEVICE_LOST:
            return "Error: Device lost";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "Error: Memory map failed";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "Error: Layer not present";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "Error: Extension not present";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "Error: Feature not present";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "Error: Incompatible driver";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "Error: Too many objects";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "Error: Format not supported";
        case VK_ERROR_FRAGMENTED_POOL:
            return "Error: Fragmented pool";
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            return "Error: Out of pool memory";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            return "Error: Invalid external handle";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "Error: Surface lost";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "Error: Native window in use";
        case VK_SUBOPTIMAL_KHR:
            return "Suboptimal";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "Error: Out of date";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "Error: Incompatible display";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "Error: Validation failed";
        case VK_ERROR_INVALID_SHADER_NV:
            return "Error: Invalid shader";
        case VK_ERROR_NOT_PERMITTED_EXT:
            return "Error: Not permitted";
        default:
            return "Unknown";
    }
}

class checked_result final
{
public:
#if (defined(AEON_VULKAN_ENABLE_ERROR_CHECKING))
    static constexpr auto error_check_enabled = true;
#else
    static constexpr auto error_check_enabled = false;
#endif

    explicit checked_result(const VkResult result) noexcept(!error_check_enabled)
    {
#if (defined(AEON_VULKAN_ENABLE_ERROR_CHECKING))
        if (result != VK_SUCCESS)
            throw vulkan_exception{std::string{"Vulkan call failed: "} + result_to_string(result)};
#endif
    }

    ~checked_result() = default;

    checked_result(const checked_result &) noexcept = delete;
    auto operator=(const checked_result &) noexcept -> checked_result & = delete;

    checked_result(checked_result &&) noexcept = delete;
    auto operator=(checked_result &&) noexcept -> checked_result & = delete;
};

} // namespace aeon::vulkan
