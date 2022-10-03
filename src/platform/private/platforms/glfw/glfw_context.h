// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include "base_context.h"

namespace aeon::platform
{

class glfw_context final : public base_context
{
public:
    glfw_context() noexcept;
    ~glfw_context() final;

    glfw_context(const glfw_context &) noexcept = delete;
    auto operator=(const glfw_context &) noexcept -> glfw_context & = delete;

    glfw_context(glfw_context &&) noexcept = delete;
    auto operator=(glfw_context &&) noexcept -> glfw_context & = delete;

    [[nodiscard]] auto create_window(const window_create_info &info) -> std::unique_ptr<window> final;
    void poll_events() noexcept final;

    void handle_key(const keyboard_key key, const std::uint32_t scan_code,
                    const keyboard_key_state state) const noexcept;

    void handle_mouse_move(const math::vector2<double> position) const noexcept;
    void handle_mouse_button(const mouse_button button, const mouse_button_state state) const noexcept;
    void handle_mouse_scroll(const double delta) const noexcept;
};

} // namespace aeon::platform
