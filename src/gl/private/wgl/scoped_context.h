// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <aeon/gl/aeon_wgl.h>

#include <aeon/gl/opengl_context_create_info.h>
#include <aeon/gl/exception.h>
#include <aeon/platform/window.h>
#include <aeon/platform/native_handles.h>

namespace aeon::gl
{

class scoped_context final
{
public:
    explicit scoped_context(const platform::window &window, const opengl_context_create_info &create_info)
        : window_dc_{nullptr}
        , context_{nullptr}
    {
        DWORD flags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

        if (create_info.double_buffer)
            flags |= PFD_DOUBLEBUFFER;

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = flags;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = static_cast<BYTE>(create_info.color_bits);
        pfd.cDepthBits = static_cast<BYTE>(create_info.depth_bits);
        pfd.cStencilBits = static_cast<BYTE>(create_info.stencil_bits);
        pfd.iLayerType = PFD_MAIN_PLANE;

        const auto native_handles = window.native_handles();
        auto *const window_dc = GetDC(native_handles.hwnd);

        const auto pixel_format = ChoosePixelFormat(window_dc, &pfd);

        if (pixel_format == 0)
            throw gl_exception{u8"Could not choose pixel format."};

        if (!SetPixelFormat(window_dc, pixel_format, &pfd))
            throw gl_exception{u8"Could not set pixel format."};

        context_ = wglCreateContext(window_dc);

        if (!wglMakeCurrent(window_dc, context_))
            throw gl_exception{u8"Could not make current."};
    }

    ~scoped_context()
    {
        if (context_)
            delete_context();
    }

    scoped_context(const scoped_context &) noexcept = delete;
    auto operator=(const scoped_context &) noexcept -> scoped_context & = delete;

    scoped_context(scoped_context &&) noexcept = delete;
    auto operator=(scoped_context &&) noexcept -> scoped_context & = delete;

    [[nodiscard]] auto release() noexcept
    {
        auto *const context = context_;
        context_ = nullptr;
        return context;
    }

    void delete_context() noexcept
    {
        wglMakeCurrent(window_dc_, nullptr);
        wglDeleteContext(context_);
        context_ = nullptr;
    }

private:
    HDC window_dc_;
    HGLRC context_;
};

} // namespace aeon::gl
