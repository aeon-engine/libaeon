// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/instance.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include <libloaderapi.h>
#elif (AEON_PLATFORM_OS_LINUX)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <vulkan/vulkan_xlib.h>
#endif

#include <aeon/platform/native_handles.h>

namespace aeon::vulkan
{

namespace internal
{

#if (AEON_PLATFORM_OS_WINDOWS)
[[nodiscard]] auto create_surface_for_window(const instance &instance, const platform::window &window)
{
    const auto handles = window.native_handles();

    VkWin32SurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.hwnd = handles.hwnd;
    info.hinstance = GetModuleHandle(nullptr);

    VkSurfaceKHR surface = VK_NULL_HANDLE;
    checked_result{vkCreateWin32SurfaceKHR(handle(instance), &info, nullptr, &surface)};
    return surface;
}
#elif (AEON_PLATFORM_OS_LINUX)
[[nodiscard]] auto create_surface_for_window([[maybe_unused]] const instance &instance,
                                             [[maybe_unused]] const platform::window &window) -> VkSurfaceKHR
{
    const auto handles = window.native_handles();

    VkXlibSurfaceCreateInfoKHR info{};
    info.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    info.window = handles.window;
    info.dpy = handles.display;

    VkSurfaceKHR surface = VK_NULL_HANDLE;
    checked_result{vkCreateXlibSurfaceKHR(handle(instance), &info, nullptr, &surface)};
    return surface;
}
#else
[[nodiscard]] auto create_surface_for_window([[maybe_unused]] const instance &instance,
                                             [[maybe_unused]] const platform::window &window) -> VkSurfaceKHR
{
    throw vulkan_exception{"Surface creation on a window is not yet supported on this platform."};
}
#endif

} // namespace internal

surface::surface() noexcept
    : instance_{nullptr}
    , surface_{VK_NULL_HANDLE}
{
}

surface::surface(const instance &instance, const platform::window &window)
    : surface{instance, internal::create_surface_for_window(instance, window)}
{
}

surface::surface(const instance &instance, VkSurfaceKHR surface)
    : instance_{&instance}
    , surface_{surface}
{
}

surface::~surface()
{
    destroy();
}

surface::surface(surface &&other) noexcept
    : instance_{other.instance_}
    , surface_{other.surface_}
{
}

auto surface::operator=(surface &&other) noexcept -> surface &
{
    if (this != &other) [[likely]]
    {
        destroy();

        instance_ = other.instance_;
        surface_ = other.surface_;
        other.instance_ = nullptr;
        other.surface_ = VK_NULL_HANDLE;
    }

    return *this;
}

auto surface::handle() const noexcept -> VkSurfaceKHR
{
    return surface_;
}

void surface::destroy() const noexcept
{
    if (instance_ && surface_)
        vkDestroySurfaceKHR(vulkan::handle(instance_), surface_, nullptr);
}

} // namespace aeon::vulkan
