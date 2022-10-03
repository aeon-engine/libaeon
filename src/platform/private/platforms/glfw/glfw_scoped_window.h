// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <GLFW/glfw3.h>

namespace aeon::platform
{

class scoped_glfw_window final
{
public:
    scoped_glfw_window() noexcept
        : handle_{nullptr}
    {
    }

    explicit scoped_glfw_window(GLFWwindow *handle) noexcept
        : handle_{handle}
    {
    }

    ~scoped_glfw_window()
    {
        destroy();
    }

    scoped_glfw_window(const scoped_glfw_window &) noexcept = delete;
    auto operator=(const scoped_glfw_window &) noexcept -> scoped_glfw_window & = delete;

    scoped_glfw_window(scoped_glfw_window &&) noexcept = delete;
    auto operator=(scoped_glfw_window &&) noexcept -> scoped_glfw_window & = delete;

    auto operator=(GLFWwindow *handle) noexcept -> scoped_glfw_window &
    {
        destroy();
        handle_ = handle;
        return *this;
    }

    operator GLFWwindow *() const noexcept
    {
        return handle_;
    }

    void destroy() noexcept
    {
        if (handle_)
            glfwDestroyWindow(handle_);

        handle_ = nullptr;
    }

    [[nodiscard]] auto is_closed() const noexcept
    {
        if (!handle_)
            return true;

        return glfwWindowShouldClose(handle_) == GLFW_TRUE;
    }

private:
    GLFWwindow *handle_;
};

} // namespace aeon::platform
