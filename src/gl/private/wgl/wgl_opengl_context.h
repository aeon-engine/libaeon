// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/platform/window.h>
#include <aeon/gl/opengl_context.h>

#include <winnt.h>
//#include <aeon/gl/aeon_wgl.h>

namespace aeon::gl
{

class wgl_opengl_context final : public opengl_context
{
public:
    explicit wgl_opengl_context(const platform::window &window, const HDC window_dc, const HGLRC context)
        : window_{window}
        , window_dc_{window_dc}
        , context_{context}
    {
    }

    ~wgl_opengl_context() final
    {
        wglMakeCurrent(window_dc_, nullptr);
        wglDeleteContext(context_);
    }

    wgl_opengl_context(const wgl_opengl_context &) noexcept = delete;
    auto operator=(const wgl_opengl_context &) noexcept -> wgl_opengl_context & = delete;

    wgl_opengl_context(wgl_opengl_context &&) noexcept = delete;
    auto operator=(wgl_opengl_context &&) noexcept -> wgl_opengl_context & = delete;

    void make_current() const final
    {
        wglMakeCurrent(window_dc_, context_);
    }

    void swap_buffers() const final
    {
        SwapBuffers(window_dc_);
    }

    [[nodiscard]] auto version() const -> common::version2<int> final
    {
        common::version2<int> version;
        glGetIntegerv(GL_MAJOR_VERSION, &version.major);
        glGetIntegerv(GL_MINOR_VERSION, &version.minor);
        return version;
    }

private:
    const platform::window &window_;
    HDC window_dc_;
    HGLRC context_;
};

} // namespace aeon::gl
