// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include "glfw_exception.h"
#include <GLFW/glfw3.h>

namespace aeon::platform
{

class glfw final
{
public:
    glfw(const glfw &) noexcept = delete;
    auto operator=(const glfw &) noexcept -> glfw & = delete;

    glfw(glfw &&) noexcept = delete;
    auto operator=(glfw &&) noexcept -> glfw & = delete;

    static void initialize()
    {
        static const glfw init;
    }

private:
    explicit glfw()
    {
        if (glfwInit() == GLFW_FALSE)
            throw glfw_platform_exception{u8"Could not initialize GLFW"};
    }

    ~glfw()
    {
        glfwTerminate();
    }
};

} // namespace aeon::platform
