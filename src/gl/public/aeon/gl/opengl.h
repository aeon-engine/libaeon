// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/platform/context.h>
#include <aeon/gl/opengl_context.h>
#include <aeon/gl/aeon_opengl.h>
#include <aeon/gl/gl_export.h>
#include <memory>

namespace aeon::gl
{

struct opengl_context_create_info;

class opengl
{
public:
    opengl() noexcept = default;
    virtual ~opengl() = default;

    opengl(const opengl &) noexcept = delete;
    auto operator=(const opengl &) noexcept -> opengl & = delete;

    opengl(opengl &&) noexcept = delete;
    auto operator=(opengl &&) noexcept -> opengl & = delete;

    [[nodiscard]] virtual auto create_context(const platform::window &window,
                                              const opengl_context_create_info &create_info)
        -> std::unique_ptr<opengl_context> = 0;
};

[[nodiscard]] AEON_GL_EXPORT auto create_opengl(platform::context &context) -> std::unique_ptr<opengl>;

} // namespace aeon::gl
