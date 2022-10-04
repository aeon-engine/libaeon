// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/window_create_info.h>
#include <aeon/platform/context.h>
#include "base_window.h"
#include "glfw_scoped_window.h"
#include "glfw_context.h"
#include <GLFW/glfw3.h>

namespace aeon::platform
{

class glfw_window final : public base_window
{
public:
    explicit glfw_window(const window_create_info &info, glfw_context &context);
    ~glfw_window() final;

    glfw_window(const glfw_window &) noexcept = delete;
    auto operator=(const glfw_window &) noexcept -> glfw_window & = delete;

    glfw_window(glfw_window &&) noexcept = delete;
    auto operator=(glfw_window &&) noexcept -> glfw_window & = delete;

    [[nodiscard]] auto position() const noexcept -> math::vector2<std::int32_t> final;
    void position(const math::vector2<std::int32_t> &pos) final;

    void title(const std::u8string &str) final;

    [[nodiscard]] auto dimensions() const noexcept -> math::size2d<std::int32_t> final;
    void dimensions(const math::size2d<std::int32_t> &size) final;

    [[nodiscard]] auto iconification_state() const noexcept -> window_iconification_state final;

    void set_visible(const bool visible) const noexcept final;
    [[nodiscard]] auto is_visible() const noexcept -> bool final;

    void close() final;

    [[nodiscard]] auto closed() const noexcept -> bool final;

    [[nodiscard]] auto native_handles() const noexcept -> platform::native_handles final;

    [[nodiscard]] auto context() const noexcept -> const platform::context & final;

private:
    glfw_context &context_;
    scoped_glfw_window window_;
};

} // namespace aeon::platform
