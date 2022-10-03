// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include "glfw_context.h"
#include "glfw_window.h"

namespace aeon::platform
{

[[nodiscard]] AEON_PLATFORM_EXPORT auto create_context() -> std::unique_ptr<context>
{
    return std::make_unique<glfw_context>();
}

glfw_context::glfw_context() noexcept
    : base_context{}
{
}

glfw_context::~glfw_context() = default;

auto glfw_context::create_window(const window_create_info &info) -> std::unique_ptr<window>
{
    return std::make_unique<glfw_window>(info, *this);
}

void glfw_context::poll_events() noexcept
{
    glfwPollEvents();
}

void glfw_context::handle_key(const keyboard_key key, const std::uint32_t scan_code,
                              const keyboard_key_state state) const noexcept
{
    input_listeners().invoke_each(&input_events::on_key, *this, key, scan_code, state);
}

void glfw_context::handle_mouse_move(const math::vector2<double> position) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_move, *this, position);
}

void glfw_context::handle_mouse_button(const mouse_button button, const mouse_button_state state) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_button, *this, button, state);
}

void glfw_context::handle_mouse_scroll(const double delta) const noexcept
{
    input_listeners().invoke_each(&input_events::on_mouse_scroll, *this, delta);
}

} // namespace aeon::platform
