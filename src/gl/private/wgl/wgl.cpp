// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <aeon/gl/aeon_opengl.h>
#include <aeon/gl/aeon_opengl_impl.h>
#include <aeon/gl/aeon_wgl.h>
#include <aeon/gl/aeon_wgl_impl.h>

#include "wgl.h"
#include "wgl_opengl_context.h"
#include "scoped_context.h"

#include <aeon/platform/window_create_info.h>
#include <aeon/platform/window.h>
#include <aeon/gl/opengl_context_create_info.h>

namespace aeon::gl
{

[[nodiscard]] auto create_opengl(platform::context &context) -> std::unique_ptr<opengl>
{
    return std::make_unique<wgl>(context);
}

wgl::wgl(platform::context &context)
    : platform_context_{context}
    , opengl_dll_handle_{"opengl32"}
    , gdi_dll_handle_{"gdi32"}
    , initialized_gl_procs_{false}
{
    initialize_wgl_procs();
    initialize_gl_procs();
}

wgl::~wgl() = default;

auto wgl::create_context(const platform::window &window, const opengl_context_create_info &create_info)
    -> std::unique_ptr<opengl_context>
{
    const auto native_handles = window.native_handles();
    auto *const window_dc = GetDC(native_handles.hwnd);

    int flags = 0;

    if (create_info.enable_debug)
        flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

    if (create_info.forward_compatible)
        flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

    int profile_mask = 0;

    if (create_info.core_profile)
        profile_mask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;

    if (create_info.compatibility_profile)
        profile_mask |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

    const int attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                           create_info.version.major,
                           WGL_CONTEXT_MINOR_VERSION_ARB,
                           create_info.version.minor,
                           WGL_CONTEXT_FLAGS_ARB,
                           flags,
                           WGL_CONTEXT_PROFILE_MASK_ARB,
                           profile_mask,
                           0};

    scoped_context temp_context{window, create_info};
    HGLRC context = nullptr;
    if (create_info.version.major >= 3)
    {
        context = wglCreateContextAttribsARB(window_dc, nullptr, attribs);
        temp_context.delete_context();

        wglMakeCurrent(window_dc, context);
    }
    else
    {
        context = temp_context.release();
    }

    return std::make_unique<wgl_opengl_context>(window, window_dc, context);
}

void wgl::initialize_wgl_procs()
{
    internal::initialize_wgl_impl([this](const char *name) {
        auto *const result = gdi_dll_handle_.get_proc_address(name);

        if (result)
            return result;

        return opengl_dll_handle_.get_proc_address(name);
    });
}

void wgl::initialize_gl_procs()
{
    platform::window_create_info info;
    info.visible = false;

    const auto temp_window = platform_context_.create_window(info);

    const opengl_context_create_info context_info;
    scoped_context context{*temp_window, context_info};

    auto get_proc_address = [this](const char *name) {
        auto *result = static_cast<void *>(wglGetProcAddress(name));

        if (result)
            return result;

        result = gdi_dll_handle_.get_proc_address(name);

        if (result)
            return result;

        return opengl_dll_handle_.get_proc_address(name);
    };

    internal::initialize_gl_impl(get_proc_address);
    internal::initialize_wgl_impl(get_proc_address);
}

} // namespace aeon::gl
