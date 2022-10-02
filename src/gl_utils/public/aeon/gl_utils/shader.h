// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/gl/aeon_opengl.h>
#include <string_view>

namespace aeon::gl_utils
{

enum class shader_type : GLenum
{
    compute = GL_COMPUTE_SHADER,
    vertex = GL_VERTEX_SHADER,
    tesselation_control = GL_TESS_CONTROL_SHADER,
    tesselation_evaluation = GL_TESS_EVALUATION_SHADER,
    geometry = GL_GEOMETRY_SHADER,
    fragment = GL_FRAGMENT_SHADER
};

[[nodiscard]] auto create_shader(const std::string_view &source, const shader_type type) -> GLuint;

[[nodiscard]] auto create_program() -> GLuint;
void attach_shader(GLuint program, GLuint shader);
void link_program(GLuint program);

} // namespace aeon::gl_utils
