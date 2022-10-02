// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/gl/opengl.h>
#include <aeon/common/dll_loader.h>

namespace aeon::gl
{

class wgl final : public opengl
{
public:
    explicit wgl(platform::context &context);
    ~wgl() final;

    wgl(const wgl &) noexcept = delete;
    auto operator=(const wgl &) noexcept -> wgl & = delete;

    wgl(wgl &&) noexcept = delete;
    auto operator=(wgl &&) noexcept -> wgl & = delete;

    [[nodiscard]] auto create_context(const platform::window &window, const opengl_context_create_info &create_info)
        -> std::unique_ptr<opengl_context> final;

private:
    void initialize_wgl_procs();
    void initialize_gl_procs();

    platform::context &platform_context_;
    common::dll_loader::scoped_dll_handle opengl_dll_handle_;
    common::dll_loader::scoped_dll_handle gdi_dll_handle_;
    bool initialized_gl_procs_;
};

} // namespace aeon::gl
