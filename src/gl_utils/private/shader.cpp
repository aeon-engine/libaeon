// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/gl_utils/shader.h>
#include <aeon/gl_utils/check_error.h>
#include <aeon/gl/exception.h>
#include <string>

namespace aeon::gl_utils
{

[[nodiscard]] auto create_shader(const std::string_view &source, const shader_type type) -> GLuint
{
    // Create the shader object
    aeon_check_gl_error(const auto shader = glCreateShader(static_cast<GLenum>(type)));

    if (shader == 0)
        throw gl::gl_exception{u8"Failed to create shader."};

    const auto *const shader_src = std::data(source);
    aeon_check_gl_error(glShaderSource(shader, 1, &shader_src, nullptr));

    aeon_check_gl_error(glCompileShader(shader));

    // Check the compile status
    GLint status;
    aeon_check_gl_error(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

    if (status == GL_TRUE)
        return shader;

    GLint info_len = 0;
    aeon_check_gl_error(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len));

    std::u8string error;

    if (info_len > 1)
    {
        error.resize(info_len);
        aeon_check_gl_error(glGetShaderInfoLog(shader, info_len, nullptr, reinterpret_cast<char *>(std::data(error))));
    }

    aeon_check_gl_error(glDeleteShader(shader));

    if (std::empty(error))
        error = u8"Unknown";

    throw gl::gl_exception{u8"Failed to create shader: " + error};
}

auto create_program() -> GLuint
{
    aeon_check_gl_error(const auto program = glCreateProgram());

    if (program == 0)
        throw gl::gl_exception{u8"Failed to create program."};

    return program;
}

void attach_shader(GLuint program, GLuint shader)
{
    aeon_check_gl_error(glAttachShader(program, shader));
}

void link_program(GLuint program)
{
    aeon_check_gl_error(glLinkProgram(program));

    // Check the link status
    GLint status;
    aeon_check_gl_error(glGetProgramiv(program, GL_LINK_STATUS, &status));

    if (status == GL_TRUE)
        return;

    GLint info_len = 0;
    aeon_check_gl_error(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len));

    std::u8string error;

    if (info_len > 1)
    {
        error.resize(info_len);
        aeon_check_gl_error(
            glGetProgramInfoLog(program, info_len, nullptr, reinterpret_cast<char *>(std::data(error))));
    }

    aeon_check_gl_error(glDeleteProgram(program));

    if (std::empty(error))
        error = u8"Unknown";

    throw gl::gl_exception{u8"Failed to link program: " + error};
}

} // namespace aeon::gl_utils
