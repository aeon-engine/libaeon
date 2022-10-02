// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/gl/opengl.h>
#include <aeon/gl/opengl_context_create_info.h>
#include <aeon/platform/context.h>
#include <aeon/platform/window.h>
#include <aeon/platform/window_create_info.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_gl, DISABLED_test_basic_context_creation)
{
    auto platform = platform::create_context();
    auto ogl = gl::create_opengl(*platform);

    platform::window_create_info info;
    info.title = u8"OpenGL Test";

    const auto window = platform->create_window(info);

    gl::opengl_context_create_info gl_info;
    gl_info.version = common::version2{3, 3};
    gl_info.forward_compatible = false;

    const auto context = ogl->create_context(*window, gl_info);

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    while (!window->closed())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        platform->poll_events();
        context->swap_buffers();
    }
}
