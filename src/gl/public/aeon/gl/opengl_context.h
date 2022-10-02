// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/version.h>

namespace aeon::gl
{

class opengl_context
{
public:
    opengl_context() noexcept = default;
    virtual ~opengl_context() = default;

    opengl_context(const opengl_context &) noexcept = delete;
    auto operator=(const opengl_context &) noexcept -> opengl_context & = delete;

    opengl_context(opengl_context &&) noexcept = delete;
    auto operator=(opengl_context &&) noexcept -> opengl_context & = delete;

    virtual void make_current() const = 0;
    virtual void swap_buffers() const = 0;

    [[nodiscard]] virtual auto version() const -> common::version2<int> = 0;
};

} // namespace aeon::gl
