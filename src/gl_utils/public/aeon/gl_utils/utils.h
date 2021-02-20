// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/gl/aeon_opengl.h>
#include <aeon/gl_utils/check_error.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector4.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector2.h>
#include <aeon/math/size2d.h>
#include <aeon/common/color.h>

namespace aeon::gl_utils
{

inline void clear_color(const common::color3f color)
{
    aeon_check_gl_error(glClearColor(color.r, color.g, color.b, 1.0f));
}

inline void clear_color(const common::color4f color)
{
    aeon_check_gl_error(glClearColor(color.r, color.g, color.b, color.a));
}

inline void clear_color(const math::vector3<float> color)
{
    aeon_check_gl_error(glClearColor(color.x, color.y, color.z, 1.0f));
}

inline void clear_color(const math::vector4<float> color)
{
    aeon_check_gl_error(glClearColor(color.x, color.y, color.z, color.w));
}

inline void scissor(const math::rectangle<int> rect)
{
    aeon_check_gl_error(glScissor(rect.left, rect.top, math::width(rect), math::height(rect)));
}

inline void scissor(const math::vector2<int> position, const math::size2d<int> size)
{
    aeon_check_gl_error(glScissor(position.x, position.y, math::width(size), math::height(size)));
}

inline void scissor(const math::size2d<int> size)
{
    aeon_check_gl_error(glScissor(0, 0, math::width(size), math::height(size)));
}

inline void viewport(const math::rectangle<int> rect)
{
    aeon_check_gl_error(glViewport(rect.left, rect.top, math::width(rect), math::height(rect)));
}

inline void viewport(const math::vector2<int> position, const math::size2d<int> size)
{
    aeon_check_gl_error(glViewport(position.x, position.y, math::width(size), math::height(size)));
}

inline void viewport(const math::size2d<int> size)
{
    aeon_check_gl_error(glViewport(0, 0, math::width(size), math::height(size)));
}

} // namespace aeon::gl_utils
